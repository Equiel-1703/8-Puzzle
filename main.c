//-----------------------------------------------------------------------//
// 8-Puzzle em linguagem C                                               //
//                                                                       //
// Por: Daniel Lisboa, Elisa Lopes, Henrique Rodrigues & Rafael Ferrão   //
//                                                                       //
// Programação de Computadores - 2022                                    //
//-----------------------------------------------------------------------//

// Bibliotecas personalizadas externas
#include "stdpuzzle.h"

int main()
{
    // Configura a página de código de saída do console para UTF-8
    if (!SetConsoleOutputCP(65001))
    {
        system("COLOR 04");
        printf("Erro na configuracao da pagina de saida!\n\n");
        system("PAUSE");
        exit(EXIT_FAILURE);
    }

    // Limpa a tela e coloca as cores
    SetConsoleTitle("8-Puzzle");
    system("cls");
    system("COLOR 70");

    // Salva o handle de saída e entrada do console
    HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
    // Salva o handle da JANELA do console
    HWND wConsole = GetConsoleWindow();

    /*
        De acordo com a documentação da Microsoft, HANDLE e HWND são definidos como:

        - HANDLE é um handle para um objeto.
        - HWND é um handle especificamente para uma janela.

        Portanto, um HWND é um HANDLE, mas nem todo HANDLE é um HWND.

        Na definição de código:

        typedef PVOID HANDLE;
        typedef HANDLE HWND;

        - Rique
    */

    // Impossibilita o usuário de redimensionar a janela do jogo
    SetWindowLongPtr(wConsole, GWL_STYLE, GetWindowLong(wConsole, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

    /*
        LONG_PTR SetWindowLongPtrA(HWND hWnd, int nIndex, LONG_PTR dwNewLong);

            Essa função modifica os atributos da janela apontada por hWnd.

            hWnd: é o handle da janela que se deseja modificar.

            nIndex: segundo a documentação da Microsoft, é "o deslocamento baseado em zero para o valor a ser definido".
            Basicamente, esse valor especifica qual atributo deseja se alterar na janela.

            dwNewLong: o novo valor do atributo que será alterado.

        LONG GetWindowLongA(HWND hWnd, int  nIndex);

            Essa função retorna uma determinada informação sobre a janela apontada por hWnd.

            hWnd: é o handle da janela que se deseja a informação.

            nIndex: segundo a documentação da Microsoft, é "o deslocamento baseado em zero para o valor a ser obtido".
            Basicamente, esse parâmetro especifica qual atributo se deseja obter da janela.

        O que é feito na linha de código acima para desabilitar o redimensionamento da janela é um truque bem esperto.
        Primeiro, na função SetWindowLongPtr, é passado o handle da janela do console e depois a constante GWL_STYLE
        (para definir um novo estilo de janela). No terceiro parâmetro dessa função, é passado o novo valor que se quer
        alterar, que nesse caso é o estilo da janela.

        Para isso, é usada a função GetWindowLong. Com ela, pegamos o estilo atual da janela do console e retiramos a
        propriedade de poder ser redimensionada e maximizada. Isso é feito através de um AND binário (&) com as con
    */

    // Configura a formatação do jogo quando ele é aberto pela primeira vez
    setMainOutputSettings(hConsoleOut);

    while (true)
    {
        // Coloca o cursor em 0,0
        setCmdCursor(0, 0, hConsoleOut);

        // Esconde o cursor
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = false;
        SetConsoleCursorInfo(hConsoleOut, &info);

        // Menu principal-
        char choice;
        bool i = true;
        while (i)
        {
            // Exibe o menu
            showSPR("spr/menu.txt", 0, 42, 154);

            choice = getch();
            switch (choice)
            {
            case '1': // Play
                i = false;
                break;

            case '2': // Credits
                system("cls");

                // Formata a saída para os sprites
                setFontAndWindowSize(hConsoleOut, SPRS_FONT, SPRS_W, SPRS_H, true);

                // Mostra os creditos
                creditos(hConsoleIn);

                // Limpa a tela
                system("cls");
                // Formata para o menu
                setFontAndWindowSize(hConsoleOut, MENU_FONT, MENU_W, MENU_H, false);
                // Posiciona o cursor
                setCmdCursor(0, 0, hConsoleOut);
                break;

            case '3': // Score
                system("cls");
                // Formata a saída para a tela de score
                setFontAndWindowSize(hConsoleOut, SCORE_FONT, SCORE_W, SCORE_H, false);

                // Posiciona o cursor e chama a função que exibe a pontuação
                setCmdCursor(0, 0, hConsoleOut);
                showScore(hConsoleOut, hConsoleOut);

                // Limpa a tela
                system("cls");
                // Formata para o menu
                setFontAndWindowSize(hConsoleOut, MENU_FONT, MENU_W, MENU_H, true);
                // Posiciona o cursor
                setCmdCursor(0, 0, hConsoleOut);
                break;

            case '4': // Exit
                exit(EXIT_SUCCESS);
                break;

            default: // Se não for um comando válido, só manda o cursor de volta pro 0,0
                setCmdCursor(0, 0, hConsoleOut);
                break;
            }
        }

        // ======================================= PLAY =======================================

        // Limpa a tela
        system("cls");

        // Redimensiona o console para pedir o nome do usuario
        setCmdCursor(0, 0, hConsoleOut);
        setFontAndWindowSize(hConsoleOut, 40, 40, 3, false);

        // Deixa o cursor visivel
        info.dwSize = 100;
        info.bVisible = true;
        SetConsoleCursorInfo(hConsoleOut, &info);

        // Cria a lista encadeada
        pontuacao *score;
        score = (pontuacao *)malloc(sizeof(pontuacao));
        score->proximo = NULL;
        // Salva o nome do usuario num novo elemento da lista
        createScoreElement(score, hConsoleOut);

        // Esconde o cursor
        info.dwSize = 100;
        info.bVisible = false;
        SetConsoleCursorInfo(hConsoleOut, &info);

        // Formata a saída para os sprites
        setFontAndWindowSize(hConsoleOut, SPRS_FONT, SPRS_W, SPRS_H, true);
        // Coloca o cursor em 0,0 e limpa a tela
        setCmdCursor(0, 0, hConsoleOut);

        // INTERAÇÃO COM A RAINHA 1
        INTERACAO1(hConsoleOut, hConsoleIn);
        system("cls");

        // INICIO DA FASE 1 - EASY ----------------------------------

        // Formata a saída para o tabuleiro
        setFontAndWindowSize(hConsoleOut, FASES_FONT, FS1_W, FS1_H, false);
        // Chama a Fase 1
        FS1(hConsoleOut, &score->proximo->pontos);
        congratulations();
        system("cls");

        // FINAL DA FASE 1 - EASY ------------------------------------

        // INTERAÇÃO 2
        INTERACAO2(hConsoleOut, hConsoleIn);
        system("cls");

        // INICIO DA FASE 2 - MEDIUM --------------------------------

        // Formata a saída para o tabuleiro
        setFontAndWindowSize(hConsoleOut, FASES_FONT, FS2_W, FS2_H, false);

        // Chama a Fase 2
        if (!FS2(hConsoleOut, &score->proximo->pontos))
        {
            // Se ele perde
            youLose();
            perdeu(hConsoleOut, hConsoleIn);
            system("cls");
            setFontAndWindowSize(hConsoleOut, MENU_FONT, MENU_W, MENU_H, false);
            continue;
        }
        // Se ele ganha
        congratulations();
        system("cls");

        // FINAL FASE 2 - MEDIUM -------------------------------------

        // INTERAÇÃO 3
        INTERACAO3(hConsoleOut, hConsoleIn);
        system("cls");

        // INICIO DA FASE FINAL - HARD
        // Formata a saída para o tabuleiro
        setFontAndWindowSize(hConsoleOut, FASES_FONT, FSF_W, FSF_H, false);

        // Chama a Fase Final
        FSF(hConsoleOut, &score->proximo->pontos);
        congratulations();
        system("cls");
        // FINAL FASE FINAL - HARD

        // INTERAÇÃO FINAL
        INTERACAOFINAL(hConsoleOut, hConsoleIn);
        system("cls");
        setFontAndWindowSize(hConsoleOut, MENU_FONT, MENU_W, MENU_H, false);

        // Salva o score do player
        FILE *saveFile;

        // Verifica se o arquivo existe
        saveFile = fopen("save/score.bin", "r+b");

        if (saveFile == NULL) // Se o arquivo não existir
        {
            // Caso ainda não exista, cria-se o score.bin na pasta "save"
            saveFile = fopen("save/score.bin", "wb");
            fseek(saveFile, 0, SEEK_END);

            // Escreve no arquivo o nome e a pontuação do jogador
            fwrite(score->proximo->nome, sizeof(char), 11, saveFile);
            fwrite(&score->proximo->pontos, sizeof(int), 1, saveFile);

            // Fecha o arquivo e desaloca a lista encadeada
            fclose(saveFile);
            deleteEntireList(score);
        }
        else // Se o arquivo existir
        {
            // Posiciona o leitor do arquivo no começo dele
            fseek(saveFile, 0, SEEK_SET);

            while (true)
            {
                // Cria um novo elemento (pontuação)
                createNewElement(score);

                // Vai lendo os dados do save e salvando no novo elemento criado na lista encadeada
                if (fread(score->proximo->nome, sizeof(char), 11, saveFile) != 11 || fread(&score->proximo->pontos, sizeof(int), 1, saveFile) != 1)
                {
                    // Se não tem mais dados, ele deleta o elemento que sobrou na lista
                    deleteFirstElement(score);
                    break;
                }
            }

            // Cria um ponteiro para o menor score e reposiciona o cursor de leitura do arquivo no começo
            pontuacao *smallestElement;
            fseek(saveFile, 0, SEEK_SET);

            // Escreve em ordem crescente os 10 menores scores
            for (int i = 0; i < 10; i++)
            {
                // Sai do laço se já tiver esvaziado a lista
                if (score->proximo == NULL)
                    break;

                // Encontra o menor elemento da lista
                smallestElement = findSmallestScore(score);
                // Escreve no arquivo o nome e a pontuação desse menor elemento
                fwrite(smallestElement->nome, sizeof(char), 11, saveFile);
                fwrite(&smallestElement->pontos, sizeof(int), 1, saveFile);

                // Deleta o menor elemento encontrado para procurar o menor nos que restaram
                deleteThisElement(smallestElement, score);
            }

            // Fecha o arquivo e desaloca a lista
            fclose(saveFile);
            deleteEntireList(score);
        }
    }
    return 0;
}
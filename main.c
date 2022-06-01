//-----------------------------------------------------------------------//
// 8-Puzzle em linguagem C                                               //
//                                                                       //
// Por: Daniel Lisboa, Elisa Lopes, Henrique Rodrigues & Rafael Ferrão   //
//                                                                       //
// Programação de Computadores - 2022                                    //
//-----------------------------------------------------------------------//

// Bibliotecas personalizadas externas
#include "stdpuzzle.h"

// TEST STUFF
#define TAM 3

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

    //----------PLAYGROUND DO FERRÃO----------//
    //                                        //
    // while(board1 != gabarito){             //
    //     showBoard(board1, TAM);            //
    //     showComandos();                    //
    //     getChar()!=(possibleMoves);        //
    // }                                      //
    //                                        //
    //----------------------------------------//

    // Limpa a tela e coloca as cores
    SetConsoleTitle("8-Puzzle");
    system("cls");
    system("COLOR 70");

    // Salva o handle do console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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
    setMainOutputSettings(hConsole);

    // Coloca o cursor em 0,0
    setCmdCursor(0, 0, hConsole);

    // Esconde o cursor
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = false;
    SetConsoleCursorInfo(hConsole, &info);

    // Menu principal
    char choice;
    bool i = true;
    while (i)
    {
        // Exibe o menu
        showSPR("spr/menu.txt", 0, 34, 154);

        choice = getch();
        switch (choice)
        {
        case '1': // Play
            i = false;
            break;

        case '2': // Credits
            system("cls");

            // Formata a saída para os sprites
            setFontAndWindowSize(hConsole, 8, 201, 90, true);

            // Mostra os creditos
            creditos();

            // Formata para o menu
            setFontAndWindowSize(hConsole, 12, 154, 40, false);

            // Limpa a tela e posiciona o cursor
            system("cls");
            setCmdCursor(0, 0, hConsole);
            break;

        case '3': // Exit
            exit(EXIT_SUCCESS);
            break;

        default: // Se não for um comando válido, só manda o cursor de volta pro 0,0
            setCmdCursor(0, 0, hConsole);
            break;
        }
    }

    // ======================================= PLAY =======================================

    // Formata a saída para os sprites
    setFontAndWindowSize(hConsole, 8, 201, 90, true);

    // Coloca o cursor em 0,0 e limpa a tela
    setCmdCursor(0, 0, hConsole);
    system("cls");

    // INTERAÇÃO 1
    INTERACAO1(hConsole);

    system("cls");

    // FASE 1
    // Formata a saída para o tabuleiro
    setFontAndWindowSize(hConsole, 36, 22, 11, false);

    // Cria e embaralha a matriz do tabuleiro
    int *board1 = createBoard(TAM);
    const int *gabarito = createBoard(TAM);
    embaralharBoard(board1, TAM, 1);
    usrSelecBoard usrSelection = createUsrSelectionBoard(TAM, board1);
    // Exibe o tabuleiro na tela
    showBoard(board1, usrSelection.usrSelecBoard, TAM, hConsole);

    printf("\n");

    // Input do usuário
    char usrInput;
    while (true)
    {
        setCmdCursor(0, 0, hConsole);
        showBoard(board1, usrSelection.usrSelecBoard, TAM, hConsole);

        usrInput = getch();
        switch (usrInput)
        {
        case ' ':
            doMove(board1, TAM, &usrSelection);
            break;

        default:
            readSelectPosition(usrInput, board1, &usrSelection, TAM);
            break;
        }

        // Verifica se o
        if (comparaArray(board1, gabarito, TAM))
            break;
    }
    free(board1);
    system("cls");

    // INTERAÇÃO 2
    INTERACAO2(hConsole);

    return 0;
}

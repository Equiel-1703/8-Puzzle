#include "stdpuzzle.h"

// ======================================= FUNÇÕES DO GAME =======================================

// Créditos
void creditos(void)
{
    showSPR("Credits/Ferrao.txt", 0, 89, 201);
    getch();
    showSPR("Credits/Lisa.txt", 0, 89, 201);
    getch();
    showSPR("Credits/Daniel.txt", 0, 89, 201);
    getch();
    showSPR("Credits/Henrique.txt", 0, 89, 201);
    getch();
}

// ======================================= FUNÇÕES DO TABULEIRO =======================================

// Exibe a matriz na tela
void showBoard(int *board, BYTE *selecBoard, size_t tamanho, HANDLE hConsole)
{

    //------------------------------Parte superior------------------------------
    if (selecBoard[0])
        printf("╔════╗");
    else
    {
        printf("┌────");
        if (selecBoard[1])
            printf("╔");
        else
            printf("┬");
    }

    for (int j = 1; j < tamanho - 1; j++)
    {
        if (selecBoard[j])
            printf("════╗");
        else
        {
            printf("────");
            if (selecBoard[j + 1])
                printf("╔");
            else
                printf("┬");
        }
    }

    if (selecBoard[tamanho - 1])
        printf("════╗");
    else
        printf("────┐");

    printf("\n");

    //------------------------------Parte do meio------------------------------
    for (int i = 0; i < tamanho; i++) // i = linhas
    {
        // Coloca a primeira barra lateral
        if (selecBoard[i * tamanho])
            printf("║");
        else
            printf("│");

        // Agora vai trabalhar com o restante dos elementos na linha
        for (int j = 0; j < tamanho; j++) // j = colunas
        {
            if (selecBoard[i * tamanho + j])
                printColored(hConsole, board, i, j, tamanho, FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
            else
            {
                if (board[i * tamanho + j] != 0)
                    printf(" %2d ", board[i * tamanho + j]);
                else
                    printf("    ");
            }

            if (j == tamanho - 1)
                break;

            if (selecBoard[i * tamanho + j] || selecBoard[i * tamanho + (j + 1)])
                printf("║");
            else
                printf("│");
        }

        if (selecBoard[i * tamanho + (tamanho - 1)])
            printf("║");
        else
            printf("│");

        printf("\n");

        // Pai nosso, que estás nos céus!
        // Santificado seja o teu nome. Venha o teu Reino;
        // seja feita a tua vontade,
        // assim na terra como no céu. Dá-nos hoje o nosso
        // pão de cada dia. Perdoa as nossas dívidas,
        // assim como perdoamos
        // aos nossos devedores. E não nos deixes cair
        // em tentação,
        // mas livra-nos do mal,
        // porque teu é o Reino, o poder e a glória para sempre.
        // Amém.
        //
        //------------------------------Divisa intermediária------------------------------

        if (i != tamanho - 1) // Verifica se não chegou na linha de baixo
        {
            if (!selecBoard[i * tamanho] && !selecBoard[(i + 1) * tamanho])
                printf("├");

            for (int j = 0; j < tamanho; j++)
            {
                if (selecBoard[i * tamanho + j])
                    printf("╚");
                else if (selecBoard[(i + 1) * tamanho + j])
                    printf("╔");

                if (selecBoard[i * tamanho + j] || selecBoard[(i + 1) * tamanho + j])
                    printf("════");
                else
                {
                    printf("────");
                    if (j < tamanho - 1 && !selecBoard[i * tamanho + (j + 1)] && !selecBoard[(i + 1) * tamanho + (j + 1)])
                        printf("┼");
                }

                if (selecBoard[i * tamanho + j])
                    printf("╝");
                else if (selecBoard[(i + 1) * tamanho + j])
                    printf("╗");
            }
            if (!selecBoard[i * tamanho + (tamanho - 1)] && !selecBoard[(i + 1) * tamanho + (tamanho - 1)])
                printf("┤");

            printf("\n");
        }
    }

    //------------------------------Parte inferior------------------------------
    if (selecBoard[(tamanho - 1) * tamanho])
        printf("╚════╝");
    else
    {
        printf("└────");
        if (selecBoard[(tamanho - 1) * tamanho + 1])
            printf("╚");
        else
            printf("┴");
    }

    for (int j = 1; j < tamanho - 1; j++)
    {
        if (selecBoard[(tamanho - 1) * tamanho + j])
            printf("════╝");
        else
        {
            printf("────");
            if (selecBoard[(tamanho - 1) * tamanho + (j + 1)])
                printf("╚");
            else
                printf("┴");
        }
    }

    if (selecBoard[(tamanho - 1) * tamanho + (tamanho - 1)])
        printf("════╝");
    else
        printf("────┘");
}

// Cria o tabuleiro no tamanho desejado (ele é inicializado com números de 0 a "tamanho")
int *createBoard(size_t tamanho)
{
    // Aloca o tabuleiro na memória
    int *board = (int *)malloc(tamanho * tamanho * sizeof(int)); // Aloca o tamanho do tabuleiro

    if (board == NULL)
        return NULL; // Se der ruim ele retorna NULL

    // Preenche o tabuleiro com números a partir do 1
    int k = 1;
    for (int i = 0; i < tamanho; i++) // Linha
    {
        for (int j = 0; j < tamanho; j++) // Coluna
        {
            if (k == tamanho * tamanho)
                board[i * tamanho + j] = 0; // O offset é calculado através de: lin x COLS X col
            else
                board[i * tamanho + j] = k;
            k++;
        }
    }

    return board;
}

// Compara dois arrays de mesmo tamanho
bool comparaArray(int *arr1, const int *arr2, size_t tamanho)
{
    bool isEqual = true;
    for (int i = 0; i < tamanho * tamanho; i++)
    {
        if (arr1[i] != arr2[i] && isEqual == true)
        {
            isEqual = false;
            break;
        }
    }
    return isEqual;
}

// Cria uma matriz contendo a seleção de peça do usuario
usrSelecBoard createUsrSelectionBoard(size_t tamanho, int *board)
{
    BYTE *selecBoard = (BYTE *)malloc(tamanho * tamanho * sizeof(BYTE)); // Aloca o tamanho da matriz

    if (selecBoard == NULL)
    {
        system("COLOR 04");
        printf("\nErro de alocação de memória!\n");
        exit(EXIT_FAILURE);
    }

    COORD coord0 = get0position(board, tamanho);

    // Preenche a matriz de seleção com 1 na posição do '0' no tabuleiro e com '0' no restante
    for (int i = 0; i < tamanho; i++) // Linha
    {
        for (int j = 0; j < tamanho; j++) // Coluna
        {
            if (i == coord0.Y && j == coord0.X)
                selecBoard[i * tamanho + j] = 1;
            else
                selecBoard[i * tamanho + j] = 0;
        }
    }

    usrSelecBoard selBrd = {selecBoard, coord0};

    return selBrd;
}

// Embaralha o tabuleiro
void embaralharBoard(int *board, size_t tamanho, int num)
{
    srand(time(0));

    do
    {
        for (int i = 0; i < tamanho * num; i++)
        {
            int lin1, col1, lin2, col2, temp;

            lin1 = rand() % tamanho;
            col1 = rand() % tamanho;

            temp = board[lin1 * tamanho + col1];

            lin2 = rand() % tamanho;
            col2 = rand() % tamanho;

            board[lin1 * tamanho + col1] = board[lin2 * tamanho + col2];
            board[lin2 * tamanho + col2] = temp;
        }
    } while (!isSolvable(board, tamanho));
}

// Conta o numero de inversões do "arr"
int getInvCount(int *arr, int tam)
{
    int inv_count = 0;
    for (int i = 0; i < (tam * tam) - 1; i++)
        for (int j = i + 1; j < (tam * tam); j++)
            // 0 é usado para o espaço vazio
            if (arr[j] && arr[i] && arr[i] > arr[j])
                inv_count++;
    return inv_count;
}

// Essa função determina se o tabuleiro tem solução
bool isSolvable(int *puzzle, int tam)
{
    // Conta as inversões
    int invCount = getInvCount(puzzle, tam);

    // Retorna true se for par (possível) e false se não for
    return (invCount % 2 == 0);
}

// Lê os comandos do usuário para selecionar uma posição no tabuleiro
void readSelectPosition(char usrInput, int *board, usrSelecBoard *selecBoard, size_t tamanho)
{
    // Movimentação
    switch (usrInput)
    {
    case 'w': // Cima
        if (selecBoard->selecPos.Y - 1 >= 0)
        {
            selecBoard->usrSelecBoard[selecBoard->selecPos.Y * tamanho + selecBoard->selecPos.X] = 0;
            selecBoard->usrSelecBoard[(selecBoard->selecPos.Y - 1) * tamanho + selecBoard->selecPos.X] = 1;
            selecBoard->selecPos.Y--;
        }
        break;

    case 's': // Baixo
        if (selecBoard->selecPos.Y + 1 < tamanho)
        {
            selecBoard->usrSelecBoard[selecBoard->selecPos.Y * tamanho + selecBoard->selecPos.X] = 0;
            selecBoard->usrSelecBoard[(selecBoard->selecPos.Y + 1) * tamanho + selecBoard->selecPos.X] = 1;
            selecBoard->selecPos.Y++;
        }
        break;

    case 'a': // Esquerda
        if (selecBoard->selecPos.X - 1 >= 0)
        {
            selecBoard->usrSelecBoard[selecBoard->selecPos.Y * tamanho + selecBoard->selecPos.X] = 0;
            selecBoard->usrSelecBoard[selecBoard->selecPos.Y * tamanho + (selecBoard->selecPos.X - 1)] = 1;
            selecBoard->selecPos.X--;
        }
        break;

    case 'd': // Direita
        if (selecBoard->selecPos.X + 1 < tamanho)
        {
            selecBoard->usrSelecBoard[selecBoard->selecPos.Y * tamanho + selecBoard->selecPos.X] = 0;
            selecBoard->usrSelecBoard[selecBoard->selecPos.Y * tamanho + (selecBoard->selecPos.X + 1)] = 1;
            selecBoard->selecPos.X++;
        }
        break;

    default:
        break;
    }
}

// Verifica quais são os movimentos possíveis no tabuleiro
movimentosPossiveis possibleMoves(BYTE *selecBoard, size_t tam)
{
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if (selecBoard[i * tam + j] == 2)
            {
                int posX = j;
                int posY = i;
            }
        }
    }

    movimentosPossiveis mov = {false, false, false, false};

    // if(coord0.Y+1 < tam)
    //     mov.down = true;
    // if(coord0.Y-1 >= 0)
    //     mov.up = true;
    // if(coord0.X-1 >= 0)
    //     mov.left = true;
    // if(coord0.X+1 < tam)
    //     mov.right = true;

    return mov;
}

// Realiza o movimento, se for possível, atualizando o tabuleiro
void doMove(int *board, size_t tam, usrSelecBoard *boardSel)
{
    COORD coord0 = get0position(board, tam);
    int aux;
    int selX = boardSel->selecPos.X;
    int selY = boardSel->selecPos.Y;
    if (selY + 1 == coord0.Y && selX == coord0.X || selY - 1 == coord0.Y && selX == coord0.X || selX + 1 == coord0.X && selY == coord0.Y || selX - 1 == coord0.X && selY == coord0.Y)
    {
        aux = board[selY * tam + selX];
        board[selY * tam + selX] = board[coord0.Y * tam + coord0.X];
        board[coord0.Y * tam + coord0.X] = aux;
    }
}

// Retorna coordenada do 0 na matriz
COORD get0position(int *board, size_t tam)
{
    COORD coord;

    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if (board[i * tam + j] == 0)
            {
                coord.X = j;
                coord.Y = i;
            }
        }
    }

    return coord;
}

// ======================================= FUNÇÕES AUXILIARES =======================================

// Função que imprime o texto colorido na tela e depois restaura para a cor padrão
void printColored(HANDLE hConsole, int *board, int linha, int coluna, size_t tamanho, WORD atributo)
{
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    // Salva os atributos atuais do console
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    // Modifica os atributos do console
    SetConsoleTextAttribute(hConsole, atributo);

    if (board[linha * tamanho + coluna] != 0)
        printf(" %2d ", board[linha * tamanho + coluna]);
    else
        printf("    ");

    // Restaura o console para os atributos originais
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

// Essa função cria um delay de "tempo" milissegundos
void timer(int tempo)
{
    // A variável "start" salva o número de clocks até o momento de execução
    clock_t start = clock();
    // A variável "diff" salvará a diferença de clocks
    clock_t diff;
    // "msec" salvará os milissegundos que passaram
    int msec;

    /*
    Aqui foi usado o método do-while para garantir o bom funcionamento
    até em casos em que o tempo de delay é bem pequeno.
    */
    do
    {
        // Esse for é só para ocupar o processador com alguma coisa
        for (int i = 0; i < 99999; i++)
        {
            continue;
        }

        // Calcula a diferença do número de clocks atuais com os iniciais
        diff = clock() - start;
        // Converte essa diferença para milissegundos
        msec = (diff * 1000) / CLOCKS_PER_SEC;

        /*
        Se a diferença em milissegundos for menor que o tempo solicitado para delay,
        o código no "do" continuará a ser executado repetidamente. Quando a diferença
        for igual ou superior que o tempo solicitado, o laço quebra e a função acaba
        */
    } while (msec < tempo);
}

// Coloca o cursor do console em uma coordenada específica
void setCmdCursor(int x, int y, HANDLE hConsole)
{
    if ((hConsole != NULL) && (hConsole != INVALID_HANDLE_VALUE))
    {
        COORD coord;

        coord.X = x;
        coord.Y = y;

        SetConsoleCursorPosition(hConsole, coord);
    }
}

// Exibe um sprite de texto na tela
void showSPR(const char *arquivo, int startLine, int endLine, int lineSize)
{
    FILE *fp;

    if ((fp = fopen(arquivo, "r")) == NULL)
    {
        system("COLOR 04");
        printf("\nErro na leitura dos sprites!\n\n");
        system("PAUSE");
        exit(EXIT_FAILURE);
    }

    // Ajusta o cursor de leitura para a linha de começo
    fseek(fp, startLine * (lineSize * sizeof(char)), SEEK_SET);
    // fseek(fp, lineSize * sizeof(char), SEEK_SET); // Usado para testes

    short i = startLine;

    // Aloca um byte a mais no buffer para o caractere nulo '\0'
    size_t tam = (lineSize * sizeof(char)) + sizeof(char);
    char *buffer = (char *)malloc(tam);

    while (i < endLine)
    {
        if (fgets(buffer, tam, fp) != NULL)
        {
            printf("%s", buffer);
            i++;
        }
        else
        {
            free(buffer);
            fclose(fp);
            return;
        }
    }
    // Lê a última linha
    if (fgets(buffer, tam, fp) != NULL)
    {
        // Retira o '\n' da última linha (se houver)
        if (buffer[tam - 2] == '\n')
            buffer[tam - 2] = '\0';
        printf("%s", buffer);
    }

    free(buffer);
    fclose(fp);
}

void eraser(int lines, int colums, char eraserChar)
{
    // Aloca um byte a mais no buffer para o caractere nulo '\0'
    size_t tam = (colums * sizeof(char)) + sizeof(char);
    char *buffer = (char *)malloc(tam);
    memset(buffer, eraserChar, tam);
    buffer[tam - 1] = '\0';

    for (int i = 0; i < lines; i++)
    {
        printf("%s", buffer);
        if (i + 1 != lines)
            printf("\n");
    }

    free(buffer);
}

void showFala(char falaNum)
{
    const char *falaFile = "spr/falas/falas.txt";

    FILE *fp = fopen(falaFile, "r");
    if (fp == NULL)
    {
        system("COLOR 04");
        printf("\nErro de leitura no arquivo de falas!\n");
        system("PAUSE");
        exit(EXIT_FAILURE);
    }

    char *buffer = NULL;
    size_t len = 0;

    while (getline(&buffer, &len, fp) != -1)
    {
        if ((buffer[0] == falaNum) && (getline(&buffer, &len, fp) != -1))
        {
            while (true)
            {
                buffer[strlen(buffer) - 1] = '\0';
                printf("%s", buffer);
                if (getline(&buffer, &len, fp) > 2)
                    printf("\n");
                else
                    break;
            }

            fclose(fp);
            return;
        }
    }

    printf("\nFala não encontrada!\n");
    fclose(fp);
}

// Configura fonte, janela e buffer do console na primeira vez que o jogo é aberto
void setMainOutputSettings(HANDLE hConsole)
{
    // Configura a fonte do console
    CONSOLE_FONT_INFOEX conFont;
    conFont.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    conFont.nFont = 0;
    conFont.dwFontSize.X = 0;
    conFont.dwFontSize.Y = 12;
    conFont.FontFamily = FF_DONTCARE;
    conFont.FontWeight = FW_NORMAL;
    wcscpy(conFont.FaceName, L"Consolas");

    SetCurrentConsoleFontEx(hConsole, FALSE, &conFont);

    // Configura o tamanho da janela para o menu
    COORD buffer_size;
    SMALL_RECT screen_size;

    buffer_size.X = 154;
    buffer_size.Y = 40;

    CONSOLE_SCREEN_BUFFER_INFO buffInfo;
    GetConsoleScreenBufferInfo(hConsole, &buffInfo);
    if (buffInfo.dwSize.X <= buffer_size.X || buffInfo.dwSize.Y <= buffer_size.Y)
    {
        COORD tempBuffer_size;

        tempBuffer_size.X = buffer_size.X + 5;
        tempBuffer_size.Y = buffer_size.Y + 5;

        SetConsoleScreenBufferSize(hConsole, tempBuffer_size);
    }

    /*
    NOTA SOBRE REDIMENSIONAR A JANELA 1:

    O condicional acima serve para detectar se (por algum motivo) a janela do CMD está com o
    buffer de tela menor do que o tamanho que se deseja redimensionar a janela.

    Se sim, ele aumenta com cinco unidades a mais para que não ocorra erros.

    - Rique
    */

    screen_size.Left = 0;
    screen_size.Top = 0;
    screen_size.Right = buffer_size.X - 1;
    screen_size.Bottom = buffer_size.Y - 1;

    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &screen_size);
    SetConsoleScreenBufferSize(hConsole, buffer_size);
}

// Configura fonte e tamanho da janela de forma prática
void setFontAndWindowSize(HANDLE hConsole, int fontSize, int BufferX, int BufferY, bool Aumenta)
{
    // Ajusta o tamanho da fonte
    CONSOLE_FONT_INFOEX conFont;
    conFont.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    conFont.nFont = 0;
    conFont.dwFontSize.X = 0;
    conFont.dwFontSize.Y = fontSize;
    conFont.FontFamily = FF_DONTCARE;
    conFont.FontWeight = FW_NORMAL;
    wcscpy(conFont.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(hConsole, FALSE, &conFont);

    // Configura o tamanho da janela
    COORD buffer_size;
    SMALL_RECT screen_size;

    buffer_size.X = BufferX;
    buffer_size.Y = BufferY;

    screen_size.Left = 0;
    screen_size.Top = 0;
    screen_size.Right = buffer_size.X - 1;
    screen_size.Bottom = buffer_size.Y - 1;

    if (Aumenta)
    {
        SetConsoleScreenBufferSize(hConsole, buffer_size);
        SetConsoleWindowInfo(hConsole, true, &screen_size);
    }
    else
    {
        SetConsoleWindowInfo(hConsole, true, &screen_size);
        SetConsoleScreenBufferSize(hConsole, buffer_size);
    }

    /*
    NOTA SOBRE REDIMENSIONAR A JANELA 2:

    É interessante observar que quando se deseja AUMENTAR a janela, é preciso primeiro
    redimensionar o buffer do console e então redimensionar a janela.

    De forma contrária, quando se quer DIMINUIR a janela, precisa-se primeiro redimensionar
    a janela e depois o buffer do console.

    Isso se dá pois quando se aumenta a janela, o buffer precisa ser suficientemente grande
    para o novo tamanho dela. E quando se diminui, a janela precisa se redimensionar primeiro
    para que então "sobre" buffer e seja possível enconlhê-lo para o novo tamanho da janela.

    - Rique
    */
}
// Aqui está a implementação das funções de "gráficos" do game

#include "stdpuzzle.h"

// Exibe o tabuleiro na tela
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
                printColored(hConsole, board, i, j, tamanho, FOREGROUND_BLUE | BACKGROUND_WHITE);
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

// Mostra alguma fala da rainha
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
    conFont.dwFontSize.Y = MENU_FONT;
    conFont.FontFamily = FF_DONTCARE;
    conFont.FontWeight = FW_NORMAL;
    wcscpy(conFont.FaceName, L"Consolas");

    SetCurrentConsoleFontEx(hConsole, FALSE, &conFont);

    // Configura o tamanho da janela para o menu
    COORD buffer_size;
    SMALL_RECT screen_size;

    buffer_size.X = MENU_W;
    buffer_size.Y = MENU_H;

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

// Função de comemoração
void congratulations(void)
{
    for (int i = 0; i < 5; i++)
    {
        system("COLOR 07");
        timer(100);
        system("COLOR 70");
        timer(100);
    }
}

// Função de derrota
void youLose(void)
{
    for (int i = 0; i < 4; i++)
    {
        system("COLOR 04");
        timer(200);
        system("COLOR 74");
        timer(200);
    }
    system("COLOR 70"); // Volta para a cor original
}

// ======================================= FUNÇÕES AUXILIARES =======================================

// Função que imprime colorido a coordenada da board na tela e depois restaura para a cor padrão
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

// Função que imprime um texto e um numero na tela e depois restaura para a cor padrão
void printColorTextNum(HANDLE hConsoleOut, WORD atributo, const char *text, int num)
{
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    // Salva os atributos atuais do console
    GetConsoleScreenBufferInfo(hConsoleOut, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    // Modifica os atributos do console
    SetConsoleTextAttribute(hConsoleOut, atributo);

    printf(text, num);

    // Restaura o console para os atributos originais
    SetConsoleTextAttribute(hConsoleOut, saved_attributes);
}

// Coloca o cursor do console em uma coordenada específica
void setCmdCursor(int x, int y, HANDLE hConsoleOut)
{
    if ((hConsoleOut != NULL) && (hConsoleOut != INVALID_HANDLE_VALUE))
    {
        COORD coord;

        coord.X = x;
        coord.Y = y;

        SetConsoleCursorPosition(hConsoleOut, coord);
    }
}

// Apaga um determinada quantidade de linhas e colunas, substituindo por "eraserChar"
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

// Essa função cria um delay de "tempo" milissegundos
void timer(int tempoMS)
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
    } while (msec < tempoMS);
}
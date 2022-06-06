#include "stdpuzzle.h"

void FS1(HANDLE hConsoleOut, int *movimentos)
{
    // FASE 1
    bool temp = true;
    const int SIZE = 3;

    // Cria e embaralha a matriz do tabuleiro
    int *board1 = createBoard(SIZE);
    int *gabarito = createBoard(SIZE);
    embaralharBoard(board1, SIZE, 1);
    usrSelecBoard usrSelection = createUsrSelectionBoard(SIZE, board1);

    // Input do usuário
    char usrInput;
    // Quantidade de movimentos do usuário (temporário)
    int tempMov = 0;

    while (temp)
    {
        setCmdCursor(0, 0, hConsoleOut);
        showBoard(board1, usrSelection.usrSelecBoard, SIZE, hConsoleOut);
        // Mostra a quantidade de movimentos realizados
        printf("\n\nMovimentos: %d\n", tempMov);

        usrInput = getch();
        switch (usrInput)
        {
        case ' ':
            doMove(board1, SIZE, &usrSelection, &tempMov);
            break;

        case 'k':
            temp = false;
            break;

        default:
            readSelectPosition(usrInput, board1, &usrSelection, SIZE);
            break;
        }

        // Verifica se o tabuleiro foi resolvido
        if (comparaArray(board1, gabarito, SIZE))
        {
            // Se foi resolvido, mostra a última jogada e sai do laço
            setCmdCursor(0, 0, hConsoleOut);
            showBoard(board1, usrSelection.usrSelecBoard, SIZE, hConsoleOut);
            printf("\n\nMovimentos: %d\n", tempMov);
            break;
        }
    }
    // Atualiza na lista encadeada a pontuação do usuário
    *movimentos += tempMov;
    // Desaloca os tabuleiros
    free(board1);
    free(gabarito);
    free(usrSelection.usrSelecBoard);
}

bool FS2(HANDLE hConsoleOut, int *movimentos)
{
    // FASE 2
    bool temp = true;
    const int SIZE = 3;
    const int LIMITMOVS = 250;

    // Cria e embaralha a matriz do tabuleiro
    int *board1 = createBoard(SIZE);
    int *gabarito = createBoard(SIZE);
    embaralharBoard(board1, SIZE, 1);
    usrSelecBoard usrSelection = createUsrSelectionBoard(SIZE, board1);

    // Input do usuário
    char usrInput;
    // Quantidade de movimentos do usuário (temporário)
    int tempMov = 0;

    while (temp)
    {
        setCmdCursor(0, 0, hConsoleOut);
        showBoard(board1, usrSelection.usrSelecBoard, SIZE, hConsoleOut);

        // Mostra a quantidade de movimentos realizados
        printf("\n\nMovimentos: %d\n", tempMov);

        // Limpa a linha
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(hConsoleOut, &info);
        eraser(1, 22, ' ');
        setCmdCursor(info.dwCursorPosition.X, info.dwCursorPosition.Y, hConsoleOut);

        // Mostra os movimentos restantes
        if ((LIMITMOVS - tempMov) <= 10)
            printColorTextNum(hConsoleOut, FOREGROUND_RED | BACKGROUND_WHITE, "Restantes: %d", LIMITMOVS - tempMov);
        else
            printf("Restantes: %d", LIMITMOVS - tempMov);

        // Aguarda input do usuario1
        usrInput = getch();
        switch (usrInput)
        {
        case ' ':
            doMove(board1, SIZE, &usrSelection, &tempMov);
            break;

        case 'k':
            temp = false;
            break;

        default:
            readSelectPosition(usrInput, board1, &usrSelection, SIZE);
            break;
        }

        // Mostra o tabuleiro após a jogada
        setCmdCursor(0, 0, hConsoleOut);
        showBoard(board1, usrSelection.usrSelecBoard, SIZE, hConsoleOut);
        printf("\n\nMovimentos: %d\n", tempMov);

        GetConsoleScreenBufferInfo(hConsoleOut, &info);
        eraser(1, 22, ' ');
        setCmdCursor(info.dwCursorPosition.X, info.dwCursorPosition.Y, hConsoleOut);

        if ((LIMITMOVS - tempMov) <= 10)
            printColorTextNum(hConsoleOut, FOREGROUND_RED | BACKGROUND_WHITE, "Restantes: %d", LIMITMOVS - tempMov);
        else
            printf("Restantes: %d", LIMITMOVS - tempMov);

        // Verifica se o tabuleiro foi resolvido
        if (comparaArray(board1, gabarito, SIZE))
        {
            // Se sim, sai do jogo
            break;
        }
        else if ((LIMITMOVS - tempMov) == 0) // Verifica se o jogador perdeu
        {
            // Se sim, desaloca os tabuleiros e sai
            free(board1);
            free(gabarito);
            free(usrSelection.usrSelecBoard);
            // O jogador perdeu
            return false;
        }
    }
    // Atualiza na lista encadeada a pontuação do usuário
    *movimentos += tempMov;
    // Desaloca os tabuleiros
    free(board1);
    free(gabarito);
    free(usrSelection.usrSelecBoard);
    // O jogador venceu
    return true;
}

void FSF(HANDLE hConsoleOut, int *movimentos)
{
    // FASE 3
    bool temp = true;
    const int SIZE = 4;

    // Cria e embaralha a matriz do tabuleiro
    int *board1 = createBoard(SIZE);
    int *gabarito = createBoard(SIZE);
    embaralharBoard(board1, SIZE, 1);
    usrSelecBoard usrSelection = createUsrSelectionBoard(SIZE, board1);

    // Input do usuário
    char usrInput;
    // Quantidade de movimentos do usuário (temporário)
    int tempMov = 0;

    while (temp)
    {
        setCmdCursor(0, 0, hConsoleOut);
        showBoard(board1, usrSelection.usrSelecBoard, SIZE, hConsoleOut);
        // Mostra a quantidade de movimentos realizados
        printf("\n\nMovimentos: %d", tempMov);

        usrInput = getch();
        switch (usrInput)
        {
        case ' ':
            doMove(board1, SIZE, &usrSelection, &tempMov);
            break;

        case 'k':
            temp = false;
            break;

        default:
            readSelectPosition(usrInput, board1, &usrSelection, SIZE);
            break;
        }

        // Verifica se o tabuleiro foi resolvido
        if (comparaArray(board1, gabarito, SIZE))
        {
            // Se foi resolvido, mostra a última jogada e sai do laço
            setCmdCursor(0, 0, hConsoleOut);
            showBoard(board1, usrSelection.usrSelecBoard, SIZE, hConsoleOut);
            printf("\n\nMovimentos: %d", tempMov);
            break;
        }
    }
    // Atualiza na lista encadeada a pontuação do usuário
    *movimentos += tempMov;
    // Desaloca os tabuleiros
    free(board1);
    free(gabarito);
    free(usrSelection.usrSelecBoard);
}
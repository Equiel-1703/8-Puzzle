#include "stdpuzzle.h"

void FS1(HANDLE hConsole)

{
    // FASE 1

    const int OTAM = 3;

    // Cria e embaralha a matriz do tabuleiro
    int *board1 = createBoard(OTAM);
    int *gabarito = createBoard(OTAM);
    embaralharBoard(board1, OTAM, 1);
    usrSelecBoard usrSelection = createUsrSelectionBoard(OTAM, board1);

    printf("\n");

    // Input do usuário
    char usrInput;
    // Quantidade de movimentos do usuário
    int quantMov = 0;
    while (true)
    {
        setCmdCursor(0, 0, hConsole);
        showBoard(board1, usrSelection.usrSelecBoard, OTAM, hConsole);
        // Mostra a quantidade de movimentos realizados
        printf("\n%d\n", quantMov);

        usrInput = getch();
        switch (usrInput)
        {
        case ' ':
            doMove(board1, OTAM, &usrSelection, &quantMov);
            break;

        default:
            readSelectPosition(usrInput, board1, &usrSelection, OTAM);
            break;
        }

        // Verifica se o tabuleiro foi resolvido
        if (comparaArray(board1, gabarito, OTAM))
            break;
    }
    free(board1);
    free(gabarito);
    free(usrSelection.usrSelecBoard);
}

void FS2(HANDLE hConsole)
{
    // FASE 2

    const int OTAM = 3;

    // Cria e embaralha a matriz do tabuleiro
    int *board2 = createBoard(OTAM);
    int *gabarito = createBoard(OTAM);
    embaralharBoard(board2, OTAM, 1);
    usrSelecBoard usrSelection = createUsrSelectionBoard(OTAM, board2);

    printf("\n");

    // Input do usuário
    char usrInput;
    // Quantidade de movimentos do usuário
    int quantMov = 0;
    while (true)
    {
        setCmdCursor(0, 0, hConsole);
        showBoard(board2, usrSelection.usrSelecBoard, OTAM, hConsole);
        // Mostra a quantidade de movimentos realizados
        printf("\n%d\n", quantMov);

        usrInput = getch();
        switch (usrInput)
        {
        case ' ':
            doMove(board2, OTAM, &usrSelection, &quantMov);
            break;

        default:
            readSelectPosition(usrInput, board2, &usrSelection, OTAM);
            break;
        }

        // Verifica se o tabuleiro foi resolvido
        if (comparaArray(board2, gabarito, OTAM))
            break;
    }
    free(board2);
    free(gabarito);
    free(usrSelection.usrSelecBoard);
}

void FSF(HANDLE hConsole)
{
    // FASE 3

    const int OTAM = 4;

    // Cria e embaralha a matriz do tabuleiro
    int *board3 = createBoard(OTAM);
    int *gabarito = createBoard(OTAM);
    embaralharBoard(board3, OTAM, 1);
    usrSelecBoard usrSelection = createUsrSelectionBoard(OTAM, board3);

    printf("\n");

    // Input do usuário
    char usrInput;
    // Quantidade de movimentos do usuário
    int quantMov = 0;
    while (true)
    {
        setCmdCursor(0, 0, hConsole);
        showBoard(board3, usrSelection.usrSelecBoard, OTAM, hConsole);
        // Mostra a quantidade de movimentos realizados
        printf("\n%d\n", quantMov);

        usrInput = getch();
        switch (usrInput)
        {
        case ' ':
            doMove(board3, OTAM, &usrSelection, &quantMov);
            break;

        default:
            readSelectPosition(usrInput, board3, &usrSelection, OTAM);
            break;
        }

        // Verifica se o tabuleiro foi resolvido
        if (comparaArray(board3, gabarito, OTAM))
            break;
    }
    free(board3);
    free(gabarito);
    free(usrSelection.usrSelecBoard);
}
#include "stdpuzzle.h"

void FS1(HANDLE hConsole)

{
    // FASE 1

    const int SIZE = 3;

    // Cria e embaralha a matriz do tabuleiro
    int *board1 = createBoard(SIZE);
    int *gabarito = createBoard(SIZE);
    embaralharBoard(board1, SIZE, 1);
    usrSelecBoard usrSelection = createUsrSelectionBoard(SIZE, board1);

    printf("\n");

    // Input do usuário
    char usrInput;
    // Quantidade de movimentos do usuário
    int quantMov = 0;
    while (true)
    {
        setCmdCursor(0, 0, hConsole);
        showBoard(board1, usrSelection.usrSelecBoard, SIZE, hConsole);
        // Mostra a quantidade de movimentos realizados
        printf("\n%d\n", quantMov);

        usrInput = getch();
        switch (usrInput)
        {
        case ' ':
            doMove(board1, SIZE, &usrSelection, &quantMov);
            break;

        default:
            readSelectPosition(usrInput, board1, &usrSelection, SIZE);
            break;
        }

        // Verifica se o tabuleiro foi resolvido
        if (comparaArray(board1, gabarito, SIZE))
            break;
    }
    free(board1);
    free(gabarito);
    free(usrSelection.usrSelecBoard);
}

void FS2(HANDLE hConsole)
{
    // FASE 2

    const int SIZE = 3;

    // Cria e embaralha a matriz do tabuleiro
    int *board2 = createBoard(SIZE);
    int *gabarito = createBoard(SIZE);
    embaralharBoard(board2, SIZE, 1);
    usrSelecBoard usrSelection = createUsrSelectionBoard(SIZE, board2);

    printf("\n");

    // Input do usuário
    char usrInput;
    // Quantidade de movimentos do usuário
    int quantMov = 0;
    while (true)
    {
        setCmdCursor(0, 0, hConsole);
        showBoard(board2, usrSelection.usrSelecBoard, SIZE, hConsole);
        // Mostra a quantidade de movimentos realizados
        printf("\n%d\n", quantMov);

        usrInput = getch();
        switch (usrInput)
        {
        case ' ':
            doMove(board2, SIZE, &usrSelection, &quantMov);
            break;

        default:
            readSelectPosition(usrInput, board2, &usrSelection, SIZE);
            break;
        }

        // Verifica se o tabuleiro foi resolvido
        if (comparaArray(board2, gabarito, SIZE))
            break;
    }
    free(board2);
    free(gabarito);
    free(usrSelection.usrSelecBoard);
}

void FSF(HANDLE hConsole)
{
    // FASE 3

    const int SIZE = 4;

    // Cria e embaralha a matriz do tabuleiro
    int *board3 = createBoard(SIZE);
    int *gabarito = createBoard(SIZE);
    embaralharBoard(board3, SIZE, 1);
    usrSelecBoard usrSelection = createUsrSelectionBoard(SIZE, board3);

    printf("\n");

    // Input do usuário
    char usrInput;
    // Quantidade de movimentos do usuário
    int quantMov = 0;
    while (true)
    {
        setCmdCursor(0, 0, hConsole);
        showBoard(board3, usrSelection.usrSelecBoard, SIZE, hConsole);
        // Mostra a quantidade de movimentos realizados
        printf("\n%d\n", quantMov);

        usrInput = getch();
        switch (usrInput)
        {
        case ' ':
            doMove(board3, SIZE, &usrSelection, &quantMov);
            break;

        default:
            readSelectPosition(usrInput, board3, &usrSelection, SIZE);
            break;
        }

        // Verifica se o tabuleiro foi resolvido
        if (comparaArray(board3, gabarito, SIZE))
            break;
    }
    free(board3);
    free(gabarito);
    free(usrSelection.usrSelecBoard);
}
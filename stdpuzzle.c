#include "stdpuzzle.h"
#include <ctype.h>

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

// Realiza o movimento, se for possível
void doMove(int *board, size_t tam, usrSelecBoard *boardSel, int *quantMov)
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
        (*quantMov)++;
    }
}

// ======================================= FUNÇÕES DE RANKING =======================================

// insira aqui DANIEL

// ======================================= FUNÇÕES AUXILIARES =======================================

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

// Compara dois arrays de mesmo tamanho
bool comparaArray(int *arr1, int *arr2, size_t tamanho)
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

void toUpper(char *string)
{
    int i = 0;
    while (string[i])
    {
        string[i] = toupper(string[i]);
        i++;
    }
}
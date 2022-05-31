#ifndef STDPUZZLE_H_INCLUDED
#define STDPUZZLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //Usada para funções de manipulação do console
#include <stdbool.h> //Permite utilizar o tipo bool
#include <conio.h>   //Usada para obter a função getch()
#include <string.h>  //Funções de manipulação de strings
#include <time.h>

// Structs
typedef struct posMovs
{
    bool up;
    bool down;
    bool left;
    bool right;
} movimentosPossiveis;

typedef struct selecBoard
{
    BYTE *usrSelecBoard;
    COORD selecPos;
} usrSelecBoard;

typedef struct _CONSOLE_FONT_INFOEX
{
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT FontFamily;
    UINT FontWeight;
    WCHAR FaceName[LF_FACESIZE];
} CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;

// Funções
int *createBoard(size_t tamanho);
usrSelecBoard createUsrSelectionBoard(size_t tamanho, int *board);
void showBoard(int *board, BYTE *selecBoard, size_t tamanho, HANDLE hConsole);
void printColored(HANDLE hConsole, int *board, int linha, int coluna, size_t tamanho, WORD atributo);
void embaralharBoard(int *board, size_t tamanho, int num);
void readSelectPosition(char usrInput, int *board, usrSelecBoard *selecBoard, size_t tamanho);
void setCmdCursor(int x, int y, HANDLE hConsole);
movimentosPossiveis possibleMoves(BYTE *selecBoard, size_t tam);
COORD get0position(int *board, size_t tam);
void setMainOutputSettings(HANDLE hConsole);
void showSPR(const char *arquivo, int startLine, int endLine, int lineSize);
void showFala(char falaNum);
void eraser(int lines, int colums, char eraserChar);
void setFontAndWindowSize(HANDLE hConsole, int fontSize, int BufferX, int BufferY, bool Aumenta);
void creditos(void);
void timer(int tempo);

BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx);

#endif // STDPUZZLE_H_INCLUDED

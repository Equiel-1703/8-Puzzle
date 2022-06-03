#ifndef STDPUZZLE_H_INCLUDED
#define STDPUZZLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //Usada para funções de manipulação do console
#include <stdbool.h> //Permite utilizar o tipo bool
#include <conio.h>   //Usada para obter a função getch()
#include <string.h>  //Funções de manipulação de strings
#include <time.h>    //Usada para o timer e para o srand()

// Structs
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

// Funções de menu do jogo

void creditos(void);

// Funções do tabuleiro

int *createBoard(size_t tamanho);
usrSelecBoard createUsrSelectionBoard(size_t tamanho, int *board);
void doMove(int *board, size_t tam, usrSelecBoard *boardSel, int *quantMov);
void readSelectPosition(char usrInput, int *board, usrSelecBoard *selecBoard, size_t tamanho);
void congratulations(void);

// Funções de ranking

// aq Dani

// Funções de embaralhamento

void embaralharBoard(int *board, size_t tamanho, int num);
int getInvCount(int *arr, int tam);
bool isSolvable(int *puzzle, int tam);

// Funções auxiliares do tabuleiro

COORD get0position(int *board, size_t tam);
void clearKeyboardBuffer(void);

// Funções de gráficos

void showBoard(int *board, BYTE *selecBoard, size_t tamanho, HANDLE hConsole);
void showSPR(const char *arquivo, int startLine, int endLine, int lineSize);
void showFala(char falaNum);
void setMainOutputSettings(HANDLE hConsole);
void setFontAndWindowSize(HANDLE hConsole, int fontSize, int BufferX, int BufferY, bool Aumenta);

// Funções auxiliares de gráficos

void printColored(HANDLE hConsole, int *board, int linha, int coluna, size_t tamanho, WORD atributo);
void setCmdCursor(int x, int y, HANDLE hConsole);
void eraser(int lines, int colums, char eraserChar);
void timer(int tempoMS);
bool comparaArray(int *arr1, int *arr2, size_t tamanho);

// Interações com a rainha

void INTERACAO1(HANDLE hConsoleOut, HANDLE hConsoleIn);
void INTERACAO2(HANDLE hConsoleOut, HANDLE hConsoleIn);

// Funções da API do Windows

BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx);

#endif // STDPUZZLE_H_INCLUDED

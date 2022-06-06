#ifndef STDPUZZLE_H_INCLUDED
#define STDPUZZLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //Usada para funções de manipulação do console
#include <stdbool.h> //Permite utilizar o tipo bool
#include <conio.h>   //Usada para obter a função getch()
#include <string.h>  //Funções de manipulação de strings
#include <time.h>    //Usada para o timer e para o srand()

// Funções de menu do jogo

void creditos(HANDLE hConsoleIn);
void showScore(HANDLE hConsoleIn, HANDLE hConsoleOut);

// Funções do tabuleiro

typedef struct selecBoard
{
    BYTE *usrSelecBoard;
    COORD selecPos;
} usrSelecBoard;

int *createBoard(size_t tamanho);
usrSelecBoard createUsrSelectionBoard(size_t tamanho, int *board);
void doMove(int *board, size_t tam, usrSelecBoard *boardSel, int *quantMov);
void readSelectPosition(char usrInput, int *board, usrSelecBoard *selecBoard, size_t tamanho);

// Funções de ranking

typedef struct pontuacao
{
    char nome[11];
    int pontos;
    struct pontuacao *proximo;
} pontuacao;

void createScoreElement(pontuacao *lista, HANDLE hConsoleOut);
void createNewElement(pontuacao *score);
void deleteFirstElement(pontuacao *score);
pontuacao *findSmallestScore(pontuacao *lista);
void deleteThisElement(pontuacao *element, pontuacao *lista);
void deleteEntireList(pontuacao *lista);

// Funções dos Levels

void FS1(HANDLE hConsole, int *movimentos);
bool FS2(HANDLE hConsole, int *movimentos);
void FSF(HANDLE hConsole, int *movimentos);

// Funções de embaralhamento

void embaralharBoard(int *board, size_t tamanho, int num);
int getInvCount(int *arr, int tam);
bool isSolvable(int *puzzle, int tam);

// Funções auxiliares

COORD get0position(int *board, size_t tam);
void toUpper(char *string);

// Funções de gráficos

#define BACKGROUND_WHITE BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED
#define MENU_H 45
#define MENU_W 154
#define MENU_FONT 12
#define SPRS_H 91
#define SPRS_W 201
#define SPRS_FONT 8
#define CREDITS_H 90
#define CREDITS_W 201
#define CREDITS_FONT 8
#define SCORE_H 15
#define SCORE_W 30
#define SCORE_FONT 32
#define FASES_FONT 36
#define FS1_H 10
#define FS1_W 17
#define FS2_H 11
#define FS2_W 17
#define FSF_H 12
#define FSF_W 22

void showBoard(int *board, BYTE *selecBoard, size_t tamanho, HANDLE hConsole);
void showSPR(const char *arquivo, int startLine, int endLine, int lineSize);
void showFala(char falaNum);
void congratulations(void);
void youLose(void);
void setMainOutputSettings(HANDLE hConsole);
void setFontAndWindowSize(HANDLE hConsole, int fontSize, int BufferX, int BufferY, bool Aumenta);
void printColorTextNum(HANDLE hConsoleOut, WORD atributo, const char *text, int num);

// Funções auxiliares de gráficos

void printColored(HANDLE hConsole, int *board, int linha, int coluna, size_t tamanho, WORD atributo);
void setCmdCursor(int x, int y, HANDLE hConsoleOut);
void eraser(int lines, int colums, char eraserChar);
void timer(int tempoMS);
bool comparaArray(int *arr1, int *arr2, size_t tamanho);

// Interações com a rainha

void INTERACAO1(HANDLE hConsoleOut, HANDLE hConsoleIn);
void INTERACAO2(HANDLE hConsoleOut, HANDLE hConsoleIn);
void INTERACAO3(HANDLE hConsoleOut, HANDLE hConsoleIn);
void INTERACAOFINAL(HANDLE hConsoleOut, HANDLE hConsoleIn);
void perdeu(HANDLE hConsoleOut, HANDLE hConsoleIn);

// Funções da API do Windows

typedef struct _CONSOLE_FONT_INFOEX
{
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT FontFamily;
    UINT FontWeight;
    WCHAR FaceName[LF_FACESIZE];
} CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;

BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx);

#endif // STDPUZZLE_H_INCLUDED
// Interções com a rainha dentro do jogo

#include "stdpuzzle.h"

// DIÁLOGO COM A RAINHA 1
void INTERACAO1(HANDLE hConsoleOut, HANDLE hConsoleIn)
{
    // Mostra o primeiro sprite
    showSPR("spr/q_happy.txt", 0, 78, 0xC9);
    setCmdCursor(0, 79, hConsoleOut);
    // Rainha se apresenta
    showFala('1');

    // Animação da boca
    int repet = 0;
    while (repet < 5)
    {
        timer(150);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_happy_closed.txt", 55, 59, 0xC9);

        timer(150);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_happy.txt", 55, 59, 0xC9);

        repet++;
    }

    // Limpa o buffer do console e espera o usuário pressionar uma tecla
    FlushConsoleInputBuffer(hConsoleIn);
    getch();

    // Apaga o texto da fala anterior
    setCmdCursor(0, 79, hConsoleOut);
    eraser(11, 200, ' ');
    setCmdCursor(0, 79, hConsoleOut);
    // Explica que deve derrotá-la para ser o novo rei/rainha
    showFala('2');

    // Animação da boca
    repet = 0;
    while (repet < 10)
    {
        timer(150);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_happy.txt", 55, 59, 0xC9);

        timer(150);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_happy_closed.txt", 55, 59, 0xC9);

        repet++;
    }

    // Limpa o buffer do console e espera o usuário pressionar uma tecla
    FlushConsoleInputBuffer(hConsoleIn);
    getch();

    // Mostra o segundo sprite
    setCmdCursor(0, 0, hConsoleOut);
    showSPR("spr/q_challenging.txt", 0, 78, 0xC9);
    // Apaga a fala anterior
    setCmdCursor(0, 79, hConsoleOut);
    eraser(11, 200, ' ');
    setCmdCursor(0, 79, hConsoleOut);
    // Será que consegue??
    showFala('3');

    // Animação da boca
    repet = 0;
    while (repet < 4)
    {
        timer(150);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_challenging.txt", 55, 59, 0xC9);

        timer(150);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_happy_closed.txt", 55, 59, 0xC9);

        repet++;
    }

    // Limpa o buffer do console e espera o usuário pressionar uma tecla
    FlushConsoleInputBuffer(hConsoleIn);
    getch();
}

// DIÁLOGO COM A RAINHA 2 (DEPOIS DE GANHAR A PRIMEIRA FASE)
void INTERACAO2(HANDLE hConsoleOut, HANDLE hConsoleIn)
{
    // Formata a saída para os sprites
    setFontAndWindowSize(hConsoleOut, 8, 201, 90, true);

    // Posiciona o cursor
    setCmdCursor(0, 0, hConsoleOut);

    showSPR("spr/q_angry.txt", 0, 78, 0xC9);
    setCmdCursor(0, 79, hConsoleOut);
    showFala('4'); // Não acredita que conseguiu

    // Animação da boca
    int repet = 0;
    while (repet < 7)
    {
        timer(150);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_angry.txt", 55, 59, 0xC9);

        timer(150);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_angry_closed.txt", 55, 59, 0xC9);

        repet++;
    }
    clearKeyboardBuffer();
    getch();
}
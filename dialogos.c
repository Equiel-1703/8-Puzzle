// Interções com a rainha dentro do jogo

#include "stdpuzzle.h"

void INTERACAO1(HANDLE hConsole)
{
    showSPR("spr/q_happy.txt", 0, 78, 0xC9);
    setCmdCursor(0, 79, hConsole);
    showFala('1'); // Rainha se apresenta

    int repet = 0;
    while (repet < 5)
    {
        timer(150);

        setCmdCursor(0, 55, hConsole);
        showSPR("spr/q_happy_closed.txt", 55, 59, 0xC9);

        timer(150);

        setCmdCursor(0, 55, hConsole);
        showSPR("spr/q_happy.txt", 55, 59, 0xC9);

        repet++;
    }
    getch();

    setCmdCursor(0, 79, hConsole);
    eraser(11, 200, ' ');
    setCmdCursor(0, 79, hConsole);
    showFala('2'); // Explica que deve derrotá-la para ser o novo rei/rainha

    repet = 0;
    while (repet < 10)
    {
        timer(150);

        setCmdCursor(0, 55, hConsole);
        showSPR("spr/q_happy.txt", 55, 59, 0xC9);

        timer(150);

        setCmdCursor(0, 55, hConsole);
        showSPR("spr/q_happy_closed.txt", 55, 59, 0xC9);

        repet++;
    }
    getch();

    setCmdCursor(0, 0, hConsole);
    showSPR("spr/q_challenging.txt", 0, 78, 0xC9); // Muda de sprite
    setCmdCursor(0, 79, hConsole);
    eraser(11, 200, ' ');
    setCmdCursor(0, 79, hConsole);
    showFala('3'); // Será que consegue??

    repet = 0;
    while (repet < 4)
    {
        timer(150);

        setCmdCursor(0, 55, hConsole);
        showSPR("spr/q_challenging.txt", 55, 59, 0xC9);

        timer(150);

        setCmdCursor(0, 55, hConsole);
        showSPR("spr/q_happy_closed.txt", 55, 59, 0xC9);

        repet++;
    }
    getch();
}

void INTERACAO2(HANDLE hConsole)
{
    // Formata a saída para os sprites
    setFontAndWindowSize(hConsole, 8, 201, 90, true);

    // Posiciona o cursor
    setCmdCursor(0, 0, hConsole);

    showSPR("spr/q_angry.txt", 0, 78, 0xC9);
    setCmdCursor(0, 79, hConsole);
    showFala('5'); // Não acredita que conseguiu

    int repet = 0;
    while (repet < 5)
    {
        timer(150);

        setCmdCursor(0, 55, hConsole);
        showSPR("spr/q_angry.txt", 55, 59, 0xC9);

        timer(150);

        setCmdCursor(0, 55, hConsole);
        showSPR("spr/q_angry_closed.txt", 55, 59, 0xC9);

        repet++;
    }
    getch();
}
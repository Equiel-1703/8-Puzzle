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
    setFontAndWindowSize(hConsoleOut, SPRS_FONT, SPRS_W, SPRS_H, true);

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
    FlushConsoleInputBuffer(hConsoleIn);
    getch();

    // Mostra o segundo sprite
    setCmdCursor(0, 0, hConsoleOut);
    showSPR("spr/q_angry.txt", 0, 78, 0xC9);
    setCmdCursor(0, 79, hConsoleOut);
    showFala('5'); // Vamos ver se vai ser fácil agora

    // Animação da boca
    repet = 0;
    while (repet < 5)
    {
        timer(150);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_angry.txt", 55, 59, 0xC9);

        timer(150);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_happy_closed.txt", 55, 59, 0xC9);

        repet++;
    }
    // Hahaha
    repet = 0;
    while (repet < 3)
    {
        timer(200);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_challenging.txt", 55, 59, 0xC9);

        timer(200);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_happy_closed.txt", 55, 59, 0xC9);

        repet++;
    }

    FlushConsoleInputBuffer(hConsoleIn);
    getch();
}

// DIÁLOGO COM A RAINHA 3 (DEPOIS DE GANHAR A SEGUNDA FASE)
void INTERACAO3(HANDLE hConsoleOut, HANDLE hConsoleIn)
{
    // Formata a saída para os sprites
    setFontAndWindowSize(hConsoleOut, SPRS_FONT, SPRS_W, SPRS_H, true);

    // Posiciona o cursor
    setCmdCursor(0, 0, hConsoleOut);

    showSPR("spr/q_angry.txt", 0, 78, 0xC9);
    setCmdCursor(0, 79, hConsoleOut);
    showFala('7'); // Sorte de principiante

    // Animação da boca
    int repet = 0;
    while (repet < 6)
    {
        timer(150);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_angry.txt", 55, 59, 0xC9);

        timer(150);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_angry_closed.txt", 55, 59, 0xC9);

        repet++;
    }
    FlushConsoleInputBuffer(hConsoleIn);
    getch();

    // Mostra o segundo sprite
    setCmdCursor(0, 0, hConsoleOut);
    showSPR("spr/q_challenging.txt", 0, 78, 0xC9);
    setCmdCursor(0, 79, hConsoleOut);
    eraser(11, 200, ' ');
    setCmdCursor(0, 79, hConsoleOut);
    showFala('8'); // Será que encara um 4x4?

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
    FlushConsoleInputBuffer(hConsoleIn);
    getch();
}

// DIÁLOGO FINAL COM A RAINHA (DEPOIS DA FASE 3)
void INTERACAOFINAL(HANDLE hConsoleOut, HANDLE hConsoleIn)
{
    // Formata a saída para os sprites
    setFontAndWindowSize(hConsoleOut, SPRS_FONT, SPRS_W, SPRS_H, true);

    // Posiciona o cursor
    setCmdCursor(0, 0, hConsoleOut);

    showSPR("spr/q_surprised.txt", 0, 78, 0xC9);
    setCmdCursor(0, 79, hConsoleOut);
    showFala('9'); // Você é bom mesmo

    // Animação da boca
    int repet = 0;
    while (repet < 6)
    {
        timer(150);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_surprised.txt", 55, 59, 0xC9);

        timer(150);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_angry_closed.txt", 55, 59, 0xC9);

        repet++;
    }
    FlushConsoleInputBuffer(hConsoleIn);
    getch();

    // Mostra o segundo sprite
    setCmdCursor(0, 0, hConsoleOut);
    showSPR("spr/q_happy.txt", 0, 78, 0xC9);
    setCmdCursor(0, 79, hConsoleOut);
    eraser(11, 200, ' ');
    setCmdCursor(0, 79, hConsoleOut);
    showFala('A'); // Promessa é promessa

    // Animação da boca
    repet = 0;
    while (repet < 4)
    {
        timer(150);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_happy.txt", 55, 59, 0xC9);

        timer(150);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_happy_closed.txt", 55, 59, 0xC9);

        repet++;
    }
    FlushConsoleInputBuffer(hConsoleIn);
    getch();

    setCmdCursor(0, 0, hConsoleOut);
    showSPR("spr/q_gives_crown.txt", 9, 99, 0xC9);
    FlushConsoleInputBuffer(hConsoleIn);
    getch();

    congratulations();

    setCmdCursor(0, 0, hConsoleOut);
    showSPR("spr/crown.txt", 0, 89, 0xC9);
    FlushConsoleInputBuffer(hConsoleIn);
    getch();
}

// Fala da rainha quando o jogador perde
void perdeu(HANDLE hConsoleOut, HANDLE hConsoleIn)
{
    // Formata a saída para os sprites
    setFontAndWindowSize(hConsoleOut, SPRS_FONT, SPRS_W, SPRS_H, true);

    // Posiciona o cursor
    setCmdCursor(0, 0, hConsoleOut);

    showSPR("spr/q_challenging.txt", 0, 78, 0xC9);
    setCmdCursor(0, 79, hConsoleOut);
    showFala('6'); // You lose

    // Animação da boca
    int repet = 0;
    while (repet < 6)
    {
        timer(150);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_challenging.txt", 55, 59, 0xC9);

        timer(150);

        setCmdCursor(0, 55, hConsoleOut);
        showSPR("spr/q_happy_closed.txt", 55, 59, 0xC9);

        repet++;
    }
    FlushConsoleInputBuffer(hConsoleIn);
    getch();
}
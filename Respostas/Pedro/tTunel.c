#include "tTunel.h"

tTunel *CriaTunel(int linhaAcesso1, int colunaAcesso1, int linhaAcesso2, int colunaAcesso2)
{
    tTunel *Tunel = (tTunel *)calloc(1, sizeof(tTunel));
    Tunel->acesso1 = CriaPosicao(linhaAcesso1, colunaAcesso1);
    Tunel->acesso2 = CriaPosicao(linhaAcesso2, colunaAcesso2);
    return Tunel;
}

bool EntrouTunel(tTunel *tunel, tPosicao *posicao)
{
    if ((SaoIguaisPosicao(tunel->acesso1, posicao) == true) || (SaoIguaisPosicao(tunel->acesso2, posicao) == true))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void LevaFinalTunel(tTunel *tunel, tPosicao *posicao)
{
    if ((SaoIguaisPosicao(tunel->acesso1, posicao) == true))
    {
        AtualizaPosicao(posicao, tunel->acesso2);
    }
    else if ((SaoIguaisPosicao(tunel->acesso2, posicao) == true))
    {
        AtualizaPosicao(posicao, tunel->acesso1);
    }
}

void DesalocaTunel(tTunel *tunel)
{
    if (tunel != NULL)
    {
        DesalocaPosicao(tunel->acesso1);
        DesalocaPosicao(tunel->acesso2);
        free(tunel);
    }
}
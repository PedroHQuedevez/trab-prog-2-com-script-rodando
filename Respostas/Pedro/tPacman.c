#include "tPacman.h"
#include <string.h>

tPacman *CriaPacman(tPosicao *posicao)
{
    tPacman *pacman = (tPacman *)calloc(1, sizeof(tPacman));
    pacman->posicaoAtual = posicao;

    pacman->historicoDeMovimentosSignificativos = (tMovimento **)calloc(1, sizeof(tMovimento *));

    return pacman;
}

tPacman *ClonaPacman(tPacman *pacman)
{
    tPacman *pacmanClone = CriaPacman(ObtemPosicaoPacman(pacman));
    return pacmanClone;
}

tMovimento **ClonaHistoricoDeMovimentosSignificativosPacman(tPacman *pacman)
{
    tMovimento **historicoClonado = (tMovimento **)calloc(pacman->nMovimentosSignificativos, sizeof(tMovimento *));

    for (int i = 0; i < pacman->nMovimentosSignificativos; i++)
    {
        historicoClonado[i] = CriaMovimento(pacman->historicoDeMovimentosSignificativos[i]->numeroDoMovimento,
                                            pacman->historicoDeMovimentosSignificativos[i]->comando, pacman->historicoDeMovimentosSignificativos[i]->acao);
    }

    return historicoClonado;
}

tPosicao *ObtemPosicaoPacman(tPacman *pacman)
{
    return pacman->posicaoAtual;
}

int EstaVivoPacman(tPacman *pacman)
{
    return pacman->estaVivo;
}
void MovePacman(tPacman *pacman, tMapa *mapa, COMANDO comando)
{
    if (comando == 0)
    {

        if ((ObtemColunaPosicao(pacman->posicaoAtual) - 1) >= 0)
        {
            tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual), ObtemColunaPosicao(pacman->posicaoAtual) - 1);
            if (EncontrouParedeMapa(mapa, novaPosicao) == false)
            {
                AtualizaPosicao(ObtemPosicaoPacman(pacman), novaPosicao);
                if (EntrouTunel(ObtemTunelMapa(mapa), ObtemPosicaoPacman(pacman)))
                {
                    EntraTunelMapa(mapa, ObtemPosicaoPacman(pacman));
                }
            }
            DesalocaPosicao(novaPosicao);
        }
    }
    else if (comando == 1)
    {
        if ((ObtemLinhaPosicao(pacman->posicaoAtual) - 1) >= 0)
        {
            tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual) - 1, ObtemColunaPosicao(pacman->posicaoAtual));
            if (EncontrouParedeMapa(mapa, novaPosicao) == false)
            {
                AtualizaPosicao(ObtemPosicaoPacman(pacman), novaPosicao);
                if (EntrouTunel(ObtemTunelMapa(mapa), ObtemPosicaoPacman(pacman)))
                {
                    EntraTunelMapa(mapa, ObtemPosicaoPacman(pacman));
                }
            }
            DesalocaPosicao(novaPosicao);
        }
    }
    else if (comando == 2)
    {
        if ((ObtemLinhaPosicao(pacman->posicaoAtual) + 1) < ObtemNumeroLinhasMapa(mapa))
        {
            tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual) + 1, ObtemColunaPosicao(pacman->posicaoAtual));
            if (EncontrouParedeMapa(mapa, novaPosicao) == false)
            {
                AtualizaPosicao(ObtemPosicaoPacman(pacman), novaPosicao);
                if (EntrouTunel(ObtemTunelMapa(mapa), ObtemPosicaoPacman(pacman)))
                {
                    EntraTunelMapa(mapa, ObtemPosicaoPacman(pacman));
                }
            }
            DesalocaPosicao(novaPosicao);
        }
    }
    else if (comando == 3)
    {
        if ((ObtemColunaPosicao(pacman->posicaoAtual) + 1) < ObtemNumeroColunasMapa(mapa))
        {
            tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual), ObtemColunaPosicao(pacman->posicaoAtual) + 1);
            if (EncontrouParedeMapa(mapa, novaPosicao) == false)
            {
                AtualizaPosicao(ObtemPosicaoPacman(pacman), novaPosicao);
                if (EntrouTunel(ObtemTunelMapa(mapa), ObtemPosicaoPacman(pacman)))
                {
                    EntraTunelMapa(mapa, ObtemPosicaoPacman(pacman));
                }
            }
            DesalocaPosicao(novaPosicao);
        }
    }
}

void CriaTrilhaPacman(tPacman *pacman, int nLinhas, int nColunas)
{
    pacman->nLinhasTrilha = nLinhas;
    pacman->nColunasTrilha = nColunas;

    pacman->trilha = (int **)calloc(nLinhas * nColunas, sizeof(int *));
}

void AtualizaTrilhaPacman(tPacman *pacman)
{
    int nMovimentosTotais = pacman->nMovimentosBaixo + pacman->nMovimentosDireita + pacman->nMovimentosEsquerda + pacman->nMovimentosCima;
    *pacman->trilha[((ObtemLinhaPosicao(pacman->posicaoAtual)) * ObtemColunaPosicao(pacman->posicaoAtual)) - 1] = nMovimentosTotais;
}

void SalvaTrilhaPacman(tPacman *pacman)
{
    char path[1001];

    FILE *arq;

    sprintf(path, "saida/trilha.txt");

    arq = fopen(path, "w");

    for (int i = 0; i < (pacman->nLinhasTrilha * pacman->nColunasTrilha); i++)
    {
        fprintf(arq, "%d", *pacman->trilha[i]);
        if (((i % pacman->nColunasTrilha) == 0) && (i != 0))
        {
            fprintf(arq, "\n");
        }
        if ((i % pacman->nColunasTrilha) != 0)
        {
            fprintf(arq, " ");
        }
    }

    fclose(arq);
}

void InsereNovoMovimentoSignificativoPacman(tPacman *pacman, COMANDO comando, const char *acao)
{
    int nMovimentosTotais = pacman->nMovimentosBaixo + pacman->nMovimentosDireita + pacman->nMovimentosEsquerda + pacman->nMovimentosCima;

    tMovimento *novoMovimento = CriaMovimento(nMovimentosTotais, comando, acao);

    pacman->historicoDeMovimentosSignificativos[pacman->nMovimentosSignificativos] = novoMovimento;
}

int ObtemPontuacaoAtualPacman(tPacman *pacman)
{
    int n = (pacman->nFrutasComidasBaixo) + (pacman->nFrutasComidasCima) + (pacman->nFrutasComidasDireita) + (pacman->nFrutasComidasEsquerda);
    return n;
}

void MataPacman(tPacman *pacman)
{
    pacman->estaVivo = 0;
}

void DesalocaPacman(tPacman *pacman)
{
    if (pacman->historicoDeMovimentosSignificativos != NULL)
    {
        for (int i = 0; i < pacman->nMovimentosSignificativos; i++)
        {
            DesalocaMovimento(pacman->historicoDeMovimentosSignificativos[i]);
        }
        free(pacman->historicoDeMovimentosSignificativos);
    }

    if (pacman->trilha != NULL)
    {
        for (int i = 0; i < ((pacman->nLinhasTrilha * pacman->nColunasTrilha)); i++)
        {
            free(pacman->trilha[i]);
        }
        free(pacman->trilha);
    }

    free(pacman);
}

int ObtemNumeroAtualMovimentosPacman(tPacman *pacman)
{
    int numerosMovimentosTotais = pacman->nMovimentosBaixo + pacman->nMovimentosCima + pacman->nMovimentosDireita + pacman->nMovimentosEsquerda;
    return numerosMovimentosTotais;
}

int ObtemNumeroMovimentosSemPontuarPacman(tPacman *pacman)
{
    int numerosMovimentosTotais = pacman->nMovimentosBaixo + pacman->nMovimentosCima + pacman->nMovimentosDireita + pacman->nMovimentosEsquerda;
    int numeroFrutasComidasTotal = pacman->nFrutasComidasBaixo + pacman->nFrutasComidasCima + pacman->nFrutasComidasDireita + pacman->nFrutasComidasEsquerda;
    return numerosMovimentosTotais - numeroFrutasComidasTotal;
}

int ObtemNumeroColisoesParedePacman(tPacman *pacman)
{
    int numeroTotalColisoesParede = pacman->nColisoesParedeBaixo + pacman->nColisoesParedeCima + pacman->nColisoesParedeDireita + pacman->nColisoesParedeEsquerda;
    return numeroTotalColisoesParede;
}

int ObtemNumeroMovimentosBaixoPacman(tPacman *pacman)
{
    return pacman->nMovimentosBaixo;
}

int ObtemNumeroFrutasComidasBaixoPacman(tPacman *pacman)
{
    return pacman->nFrutasComidasBaixo;
}

int ObtemNumeroColisoesParedeBaixoPacman(tPacman *pacman)
{
    return pacman->nColisoesParedeBaixo;
}

int ObtemNumeroMovimentosCimaPacman(tPacman *pacman)
{
    return pacman->nMovimentosCima;
}

int ObtemNumeroFrutasComidasCimaPacman(tPacman *pacman)
{
    return pacman->nFrutasComidasCima;
}

int ObtemNumeroColisoesParedeCimaPacman(tPacman *pacman)
{
    return pacman->nColisoesParedeCima;
}

int ObtemNumeroMovimentosEsquerdaPacman(tPacman *pacman)
{
    return pacman->nMovimentosEsquerda;
}

int ObtemNumeroFrutasComidasEsquerdaPacman(tPacman *pacman)
{
    return pacman->nFrutasComidasEsquerda;
}

int ObtemNumeroColisoesParedeEsquerdaPacman(tPacman *pacman)
{
    return pacman->nColisoesParedeEsquerda;
}

int ObtemNumeroMovimentosDireitaPacman(tPacman *pacman)
{
    return pacman->nMovimentosDireita;
}

int ObtemNumeroFrutasComidasDireitaPacman(tPacman *pacman)
{
    return pacman->nFrutasComidasDireita;
}

int ObtemNumeroColisoesParedeDireitaPacman(tPacman *pacman)
{
    return pacman->nColisoesParedeDireita;
}

int ObtemNumeroMovimentosSignificativosPacman(tPacman *pacman)
{
    return pacman->nMovimentosSignificativos;
}

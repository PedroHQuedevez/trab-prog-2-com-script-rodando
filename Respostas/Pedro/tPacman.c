#include "tPacman.h"
#include <string.h>

tPacman *CriaPacman(tPosicao *posicao)
{
    tPacman *pacman = (tPacman *)calloc(1, sizeof(tPacman));
    pacman->posicaoAtual = posicao;
    pacman->estaVivo = 1;
    pacman->historicoDeMovimentosSignificativos = (tMovimento **)calloc(1, sizeof(tMovimento *));

    return pacman;
}

tPacman *ClonaPacman(tPacman *pacman)
{
    tPosicao *posicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual), ObtemColunaPosicao(pacman->posicaoAtual));
    tPacman *pacmanClone = CriaPacman(posicao);
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

        tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual), ObtemColunaPosicao(pacman->posicaoAtual) - 1);

        AtualizaPosicao(ObtemPosicaoPacman(pacman), novaPosicao);

        DesalocaPosicao(novaPosicao);
    }
    else if (comando == 1)
    {

        tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual) - 1, ObtemColunaPosicao(pacman->posicaoAtual));

        AtualizaPosicao(ObtemPosicaoPacman(pacman), novaPosicao);

        DesalocaPosicao(novaPosicao);
    }
    else if (comando == 2)
    {

        tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual) + 1, ObtemColunaPosicao(pacman->posicaoAtual));

        AtualizaPosicao(ObtemPosicaoPacman(pacman), novaPosicao);

        DesalocaPosicao(novaPosicao);
    }
    else if (comando == 3)
    {

        tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual), ObtemColunaPosicao(pacman->posicaoAtual) + 1);

        AtualizaPosicao(ObtemPosicaoPacman(pacman), novaPosicao);

        DesalocaPosicao(novaPosicao);
    }
}

void CriaTrilhaPacman(tPacman *pacman, int nLinhas, int nColunas)
{
    pacman->nLinhasTrilha = nLinhas;
    pacman->nColunasTrilha = nColunas;

    if (pacman->trilha != NULL)
    {
        free(pacman->trilha);
    }

    pacman->trilha = (int **)malloc(nLinhas * sizeof(int *) * nColunas);

    for (int i = 0; i < nLinhas; i++)
    {
        pacman->trilha[i] = (int *)malloc(nColunas * sizeof(int));
    }

    for (int i = 0; i < pacman->nLinhasTrilha; i++)
    {
        for (int j = 0; j < pacman->nColunasTrilha; j++)
        {
            pacman->trilha[i][j] = -1; // aqui eu queria iniciar com -1 mas o scrip não deixa.. facilitaria fazer a trilha;
        }
    }
}

void AtualizaTrilhaPacman(tPacman *pacman)
{
    if (ObtemNumeroAtualMovimentosPacman(pacman) == 0)
    {
        pacman->trilha[ObtemLinhaPosicao(pacman->posicaoAtual)][ObtemColunaPosicao(pacman->posicaoAtual)] = ObtemNumeroAtualMovimentosPacman(pacman);
    }
    else
    {
        pacman->trilha[ObtemLinhaPosicao(pacman->posicaoAtual)][ObtemColunaPosicao(pacman->posicaoAtual)] = ObtemNumeroAtualMovimentosPacman(pacman);
    }
}

void SalvaTrilhaPacman(tPacman *pacman)
{
    char path[1001];

    FILE *arq;

    sprintf(path, "trilha.txt");

    arq = fopen(path, "w");

    for (int i = 0; i < (pacman->nLinhasTrilha); i++)
    {
        for (int j = 0; j < pacman->nColunasTrilha; j++)
        {
            if (pacman->trilha[i][j] == -1)
            {
                fprintf(arq, "#");
                if (j != (pacman->nColunasTrilha - 1))
                {
                    fprintf(arq, " ");
                }
            }
            else
            {
                fprintf(arq, "%i", pacman->trilha[i][j]);
                if (j != (pacman->nColunasTrilha - 1))
                {
                    fprintf(arq, " ");
                }
            }
        }
        fprintf(arq, "\n");
    }

    fclose(arq);
}

void InsereNovoMovimentoSignificativoPacman(tPacman *pacman, COMANDO comando, const char *acao)
{

    pacman->historicoDeMovimentosSignificativos = (tMovimento **)realloc(pacman->historicoDeMovimentosSignificativos, (sizeof(tMovimento *)) * ((pacman->nMovimentosSignificativos) + 1));

    tMovimento *novoMovimento = CriaMovimento(ObtemNumeroAtualMovimentosPacman(pacman), comando, acao);

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
    DesalocaPosicao(pacman->posicaoAtual);

    for (int i = 0; i < pacman->nMovimentosSignificativos; i++) // usar o < funciona no teste completo mas não no tpacman, e <= no tpacman mas não no completo;
    {                                                           // entre outros momentos que dependendo de onde coloco o contador de mov.significativo aparecem outros erros em lugares diferentes e resolvendo outros;
        DesalocaMovimento(pacman->historicoDeMovimentosSignificativos[i]);
    }
    free(pacman->historicoDeMovimentosSignificativos);

    for (int i = 0; i < (pacman->nLinhasTrilha); i++)
    {
        free(pacman->trilha[i]);
    }
    free(pacman->trilha);

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

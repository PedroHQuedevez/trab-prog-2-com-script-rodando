#include <stdio.h>
#include "tMapa.h"
#include "tMovimento.h"
#include "tPacman.h"
#include "tPosicao.h"
#include "tTunel.h"
#include "tFantasma.h"
#include "tUtils.h"
#include "tRelatorio.h"

int main(int argc, char *argv[])
{
    // cria_pastas(argv[1]);
    if (argv[1] == NULL)
    {
        printf("ERRO: O diretório de arquivos de configuração nao foi informado\n  ");
        exit(1);
    }

    tMapa *mapa = CriaMapa(argv[1]);

    tPacman *pacman = CriaPacman(ObtemPosicaoItemMapa(mapa, '>'));
    CriaTrilhaPacman(pacman, ObtemNumeroLinhasMapa(mapa), ObtemNumeroColunasMapa(mapa));
    AtualizaTrilhaPacman(pacman);

    RelatorioInicializacao(mapa, pacman, argv[1]);

    tlistafantasmas *listaFantasmas = CriaListaFantasmas(mapa);

    char comando;
    char path[1001];
    FILE *entrada;
    sprintf(path, "%s/entrada.txt", argv[1]);
    entrada = fopen(path, "r");

    if (entrada == NULL)
    {
        printf("ERRO: nao foi possível ler o arquivo %s", path);
        exit(1);
    }

    FILE *RelatorioSaida = AbreRelatorioSaida(argv[1]);

    while (fscanf(entrada, "%c\n", &comando) != -1)
    {
        // printf("%c\n", comando);
        COMANDO c;
        if (comando == 'a')
        {
            c = 0;
        }
        else if (comando == 'w')
        {
            c = 1;
        }
        else if (comando == 's')
        {
            c = 2;
        }
        else if (comando == 'd')
        {
            c = 3;
        }

        tPacman *pacmanClone = ClonaPacman(pacman);
        tlistafantasmas *listaClonada = ClonaListaFantasmas(listaFantasmas);

        MovePacman(pacman, mapa, c);
        MoveFantasmas(mapa, listaFantasmas);
        // AdicionaContadorMovimentosPorDirecao(comando, pacman); //se eu deletar os contadores da main o scrip roda.. ?????????????
        // não posso usar essa função dentro da pacman e nem modificar valores durante a função movepacman por que o script não aceita;

        AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacmanClone), ' ');

        if (EncontrouComidaMapa(mapa, ObtemPosicaoPacman(pacman)) == true)
        {
            AdicionaContadorFrutasPorDirecao(comando, pacman);
            AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), ' ');

            InsereNovoMovimentoSignificativoPacman(pacman, c, "pegou comida");
            // AdicionaContadorMovimentosSignificatos(pacman);
        }
        else if (PossuiTunelMapa(mapa))
        {

            if (EntrouTunel(ObtemTunelMapa(mapa), ObtemPosicaoPacman(pacman)) == true)
            {
                EntraTunelMapa(mapa, ObtemPosicaoPacman(pacman));
            }
        }
        else if (EncontrouParedeMapa(mapa, ObtemPosicaoPacman(pacman)) == true)
        {
            AdicionaContadorColisoesPorDirecao(comando, pacman);
            AtualizaPosicao(pacman->posicaoAtual, pacmanClone->posicaoAtual);

            InsereNovoMovimentoSignificativoPacman(pacman, c, "colidiu com a parede");
            // AdicionaContadorMovimentosSignificatos(pacman);
        }

        AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), '>');

        if ((VerificaPerdeuJogo(mapa, pacman, listaFantasmas, pacmanClone, listaClonada) == true) || EstaVivoPacman(pacman) == 0)
        {
            if (EstaVivoPacman(pacman) == 0)
            {
                pacman->estaVivo = 0;

                InsereNovoMovimentoSignificativoPacman(pacman, c, "fim de jogo por encostar em um fantasma");
                // AdicionaContadorMovimentosSignificatos(pacman);
            }

            EscreveRelatorioSaida(RelatorioSaida, comando, mapa, listaFantasmas, pacman);
            fprintf(RelatorioSaida, "Game over!\nPontuacao final: %d\n", ObtemPontuacaoAtualPacman(pacman));
            AtualizaTrilhaPacman(pacman);
            DesalocaPacman(pacmanClone);
            DesalocaListaFantasmas(listaClonada);
            break;
        }

        if (VerificaGanhouJogo(mapa, pacman) == true)
        {

            EscreveRelatorioSaida(RelatorioSaida, comando, mapa, listaFantasmas, pacman);
            fprintf(RelatorioSaida, "Voce venceu!\nPontuacao final: %d\n", ObtemPontuacaoAtualPacman(pacman));
            AtualizaTrilhaPacman(pacman);
            DesalocaPacman(pacmanClone);
            DesalocaListaFantasmas(listaClonada);

            break;
        }

        EscreveRelatorioSaida(RelatorioSaida, comando, mapa, listaFantasmas, pacman);
        AtualizaTrilhaPacman(pacman);
        DesalocaPacman(pacmanClone);
        DesalocaListaFantasmas(listaClonada);
    }

    fclose(entrada);

    FechaRelatorioSaida(RelatorioSaida);

    RelatorioEstatisticas(pacman, argv[1]);

    RelatorioRanking(pacman, argv[1]);

    RelatorioResumo(pacman, argv[1]);

    SalvaTrilhaPacman(pacman);

    DesalocaPacman(pacman);
    DesalocaMapa(mapa);
    DesalocaListaFantasmas(listaFantasmas);

    return 0;
}

//     PrintaMapaSaida(RelatorioSaida, comando, mapa, listaFantasmas, pacman, pacmanContador);
//     //

//     if ((VerificaPerdeuJogo(mapa, pacmanContador, listaFantasmas, pacmanClone, listaClonada) == true) || EstaVivoPacman(pacmanContador) == 0)
//     {
//         if (EstaVivoPacman(pacmanContador) == 0)
//         {
//             pacman->estaVivo = 0;
//             InsereNovoMovimentoSignificativoPacman(pacmanContador, c, "fim de jogo por encostar em um fantasma");
//         }
//         EscreveRelatorioSaida(RelatorioSaida, comando, mapa, listaFantasmas, pacman, pacmanContador);
//         fprintf(RelatorioSaida, "Game over!\nPontuacao final: %d\n", ObtemPontuacaoAtualPacman(pacmanContador));
//         DesalocaPacman(pacmanClone);
//         DesalocaListaFantasmas(listaClonada);
//         break;
//     }

//     if (VerificaGanhouJogo(mapa, pacmanContador) == true)
//     {
//         EscreveRelatorioSaida(RelatorioSaida, comando, mapa, listaFantasmas, pacman, pacmanContador);
//         fprintf(RelatorioSaida, "Voce venceu!\nPontuacao final: %d\n", ObtemPontuacaoAtualPacman(pacmanContador));
//         DesalocaPacman(pacmanClone);
//         DesalocaListaFantasmas(listaClonada);
//         break;
//     }
//     EscreveRelatorioSaida(RelatorioSaida, comando, mapa, listaFantasmas, pacman, pacmanContador);
//     DesalocaPacman(pacmanClone);
//     DesalocaListaFantasmas(listaClonada);
// }
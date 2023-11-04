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
    cria_pastas(argv[1]);
    if (argv[1] == NULL)
    {
        printf("ERRO: O diretório de arquivos de configuração nao foi informado\n  ");
        exit(1);
    }

    tMapa *mapa = CriaMapa(argv[1]);

    tPacman *pacman = CriaPacman(ObtemPosicaoItemMapa(mapa, '>'));
    tPacman *pacmanContador = CriaPacman(ObtemPosicaoItemMapa(mapa, '>'));
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
    }
    fclose(entrada);

    FechaRelatorioSaida(RelatorioSaida);

    RelatorioEstatisticas(pacmanContador, argv[1]);

    RelatorioRanking(pacmanContador, argv[1]);

    RelatorioResumo(pacmanContador, argv[1]);

    SalvaTrilhaPacman(pacmanContador);

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
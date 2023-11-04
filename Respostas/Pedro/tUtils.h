#ifndef _UTILS_H
#define _UTILS_H

bool VerificaPerdeuJogo(tMapa *mapa, tPacman *pacman, tlistafantasmas *listaFantasmas, tPacman *pacmanClonado, tlistafantasmas *listaClonada);
bool VerificaGanhouJogo(tMapa *mapa, tPacman *pacman);
void cria_pastas(char *path);
void AdicionaContadorMovimentosPorDirecao(char direcao, tPacman *Pacman);
void AdicionaContadorFrutasPorDirecao(char direcao, tPacman *pacman);
void AdicionaContadorColisoesPorDirecao(char direcao, tPacman *pacman);
void AdicionaContadorMovimentosSignificatos(tPacman *pacman);

#endif
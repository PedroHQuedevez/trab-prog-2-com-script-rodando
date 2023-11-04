all:
	gcc -g -Wall *.c -o main

valgrind:
	valgrind ./main 01/

diff:
	diff 01/saida/saida.txt saida.txt
	diff 01/saida/inicializacao.txt inicializacao.txt
	diff 01/saida/estatisticas.txt estatisticas.txt
	diff 01/saida/ranking.txt ranking.txt
	diff 01/saida/resumo.txt resumo.txt
	diff 01/saida/trilha.txt trilha.txt
	
all:
	gcc -g -Wall *.c -o main

valgrind:
	valgrind ./main 01/

diff:
	diff 01/saida/saida.txt saida/saida.txt
	diff 01/saida/inicializacao.txt saida/inicializacao.txt
	diff 01/saida/estatisticas.txt saida/estatisticas.txt
	diff 01/saida/ranking.txt saida/ranking.txt
	diff 01/saida/resumo.txt saida/resumo.txt
	diff 01/saida/trilha.txt saida/trilha.txt
	
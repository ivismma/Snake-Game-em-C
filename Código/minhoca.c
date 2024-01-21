// Funções que gerenciam a minhoca.

#include <ncurses/ncurses.h>
#include "header.h"


void inicializarMinhoca(Minhoca *minhoca){
	// Inicializa a minhoca com uma cabeça dois segmentos.
	minhoca->x = WIDTH/2;
    minhoca->y = 1+HEIGHT/2;
	minhoca[1].x = minhoca->x; 
	minhoca[1].y = minhoca->y-1;
	minhoca[2].x = minhoca->x; 
	minhoca[2].y = minhoca->y-2;
}

void desenharMinhoca(Minhoca *minhoca, int tam){
	// Desenhar cabeça e em seguida, os segmentos da minhoca no vetor dinâmico.
	mvprintw(minhoca->y, minhoca->x, "0");
	for(int i = 1; i < tam; ++i)
		mvprintw((minhoca+i)->y, (minhoca+i)->x, "O");
}

void atualizarMinhoca(Minhoca *minhoca, int tam){
	// Computar trajetória da minhoca.
	for (int i = tam-1; i > 0; minhoca[i--] = minhoca[i]);
}

bool checaSeComeu(Minhoca* minhoca, Consumivel pos){
	// Se cabeça tocou a maçã...
	if(minhoca->x == pos.x && minhoca->y == pos.y)
		return true;
	return false; 
}

void crescerMinhoca(Minhoca *minhoca, int *tam, int x, int y){
	// Novo segmento da minhoca recebe pos. do anterior rabo da minhoca.
	minhoca[*tam].x = x;
    minhoca[*tam].y = y;
    ++(*tam);
}

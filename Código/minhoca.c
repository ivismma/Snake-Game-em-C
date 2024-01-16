#include "header.h"
#include <ncurses/ncurses.h>

void inicializarMinhoca(Minhoca *minhoca){
	// Inicializa a minhoca com uma cabeça e uma parte.
	minhoca->x = WIDTH/2;
    minhoca->y = HEIGHT/2;
	minhoca[1].x = minhoca->x; 
	minhoca[1].y = minhoca->y-1;
}

void desenharMinhoca(Minhoca *minhoca, int tam){
	mvprintw(minhoca->y, minhoca->x, "0");
	for(int i = 1; i < tam; ++i)
		mvprintw((minhoca+i)->y, (minhoca+i)->x, "O");
}

// x, y correspondem à posição atual que se encontrava a cabeça da minhoca.
void atualizarMinhoca(Minhoca *minhoca, int *tam){
	for (int i = *tam - 1; i > 0; --i)
        minhoca[i] = minhoca[i-1];
	// Atualizando a cabeça da minhoca
    // Verificar se a minhoca comeu a maçã, se sim, aumentar seu tamanho.
    refresh();
}

bool checaSeComeu(Minhoca* minhoca, Consumivel pos){
	if(minhoca->x == pos.x && minhoca->y == pos.y)
		return true;
	return false; 
}

void crescerMinhoca(Minhoca *minhoca, int *tam){
	++(*tam);
	minhoca[*tam-1].x = minhoca[*tam-2].x;
    minhoca[*tam-1].y = minhoca[*tam-2].y;
}

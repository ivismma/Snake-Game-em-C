// Funções que gerenciam o jogo.

#include <ncurses/ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

void desenharParedes(){
	// Paredes verticais
	for(int i = 1; i < HEIGHT+1;++i) mvprintw(i, 0, "#");
	for(int i = 1; i < HEIGHT+1;++i) mvprintw(i, WIDTH+1, "#");
	// Paredes horizontais
	for(int i = 0; i < WIDTH+2;++i) mvprintw(0, i, "#");
	for(int i = 0; i < WIDTH+2;++i) mvprintw(HEIGHT+1, i, "#");
}

bool checaColisao(Minhoca *minhoca, int x, int y){
	// Colisão com parede vertical
	if(y == 0 || y >= HEIGHT+1) return true;
	// Colisão com parede horizontal
	else if(x == 0 || x >= WIDTH+1) return true;

	else return false; // Não haverá colisão.
}

bool checaMorte(Minhoca *minhoca, int tam){
	// Pega pos. da cabeça e verifica se atingiu o resto da minhoca.
	for(int i = 1; i < tam;++i){
		if(minhoca->x == minhoca[i].x && minhoca->y == minhoca[i].y)
			return true; // Colisão
	}
	// A cabeça da minhoca não colidiu com si mesma.
	return false;
}

Consumivel gerarConsumivel(Minhoca *minhoca, int tam){
	srand(time(NULL));
	bool disponivel; 
	// Tenta criar uma maçã em um lugar disponível (não ocupado pela minhoca)
	do{ 
		disponivel = true;
		pos.x = rand()%WIDTH + 1;     // Gerar coordenada dentro do mapa (+1 para evitar paredes).
		pos.y = rand()%HEIGHT + 1;
		for(int i = 0; i < tam; ++i){
			if(pos.x == minhoca[i].x && pos.y == minhoca[i].y){
				disponivel = false; // Coordenada gerada está ocupada pela minhoca.
				break;
			}
		}
	} while(!disponivel);
	// Retornar nova posição da maçã gerada.
	return pos;
}

void desenharConsumivel(Consumivel pos){
	mvprintw(pos.y,pos.x, "-");
}

void reiniciaJogo(Minhoca *minhoca, int *tamanho, int *cont, int *ant){
	inicializarMinhoca(minhoca);
	*ant = KEY_DOWN; // Resetar dir. inicial para impedir de ir contra si mesma após reinício.
	*tamanho = 3;
	*cont = 0;
	pos = gerarConsumivel(minhoca, *tamanho);
}

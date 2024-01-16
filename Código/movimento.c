// Funções que gerenciam o input do jogo e diretivas de movimentação da minhoca.


#include <stdbool.h>
#include <ncurses/ncurses.h>

#include "header.h"

bool preComputarMovimento(int tecla, Minhoca *minhoca, int tamanho, int *direcao){
	switch (tecla){
            case KEY_UP:
                if(checaColisao(minhoca, minhoca->x, minhoca->y-1)){
                	atualizarMinhoca(minhoca, tamanho);
					minhoca->y += HEIGHT-1;
					return true;
				}
				else *direcao = KEY_UP;
				break;
            case KEY_DOWN:
            	if(checaColisao(minhoca, minhoca->x, minhoca->y+1)){
            		atualizarMinhoca(minhoca, tamanho);
					minhoca->y -= HEIGHT-1;
					return true;
				}
				else *direcao = KEY_DOWN;
				break;
            case KEY_LEFT:
            	if(checaColisao(minhoca, minhoca->x-1, minhoca->y)){
            		atualizarMinhoca(minhoca, tamanho);
					minhoca->x += WIDTH-1;
					return true;
				}
				else *direcao = KEY_LEFT;
				break;
            case KEY_RIGHT:
            	if(checaColisao(minhoca, minhoca->x+1, minhoca->y)){
            		atualizarMinhoca(minhoca, tamanho);
					minhoca->x -= WIDTH-1;
					return true;
				}
				else *direcao = KEY_RIGHT;
				break;
        }
        return false;
}

void movimentoNormal(int direcao, Minhoca *minhoca, int tamanho){
	switch (direcao){
	    case KEY_UP:
			atualizarMinhoca(minhoca, tamanho);
			--(minhoca->y);
	        break;
	    case KEY_DOWN:
	    	atualizarMinhoca(minhoca, tamanho);
	    	++(minhoca->y);
	    	break;
	    case KEY_LEFT:
	    	atualizarMinhoca(minhoca, tamanho);
	    	--(minhoca->x);
	        break;
	    case KEY_RIGHT:
	    	atualizarMinhoca(minhoca, tamanho);
	    	++(minhoca->x);
	        break;
	}
	return;
}

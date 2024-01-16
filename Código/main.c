#include <ncurses/ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <time.h>

#include "header.h"

Consumivel pos; // Variável global - Posição atual da maçã

int main(){
	setlocale(LC_ALL, "pt_BR.UTF-8");
	// Funções biblioteca ncurses
    initscr();
    clear();
    noecho();
    curs_set(0); 
    keypad(stdscr, TRUE); // leitura teclas especiais
    
	int direcao = KEY_DOWN;
	int anterior = KEY_DOWN;
	int tamanho = 3; // Tamanho da minhoca, inicia como 3.
	int cont = 0; // Movimentos
	// Alocação de memória da minhoca.
	Minhoca *minhoca = (Minhoca*) calloc(WIDTH*HEIGHT, sizeof(Minhoca));
	if(minhoca == NULL){
		endwin();
		fprintf(stderr, "Falha na alocação de memória.\n");
		return -1;
	}
	
	inicializarMinhoca(minhoca);
	Consumivel pos = gerarConsumivel(minhoca, tamanho);
    
    // Loop do jogo.
	while(1) {
		clear();
		desenharParedes();
		desenharConsumivel(pos);
		desenharMinhoca(minhoca, tamanho); // Segmentos
		
		mostrarInfo();
		mostrarInfoStats(minhoca, tamanho, cont);
        
		
        // Capturar movimento
		int tecla = getch();
		if(!checaMovimento(anterior, tecla)) continue; // Evitar minhoca de ir contra si mesmo.
		anterior = tecla;
		++cont; // Movs.
		usleep(10000);  // microsegundos
		
		// Posição do rabo (tail) da minhoca:
		int tailX = minhoca[tamanho-1].x;
		int tailY = minhoca[tamanho-1].y;
		
		// Computar tecla e verificar se próximo movimento ocorreu colisão com parede.
		bool colidiu = false;
		colidiu = preComputarMovimento(tecla, minhoca, tamanho, &direcao);
		
		if(!colidiu) movimentoNormal(direcao, minhoca, tamanho);
	    
		
		// Checar se a minhoca morreu após o movimento efetuado.
	    if(checaMorte(minhoca, tamanho)) {
	        free(minhoca);
	        endwin();
	        printf("Minhoca morreu :(\n");
	        getch();
	        return 0;
    	}
    	
		// Checar se a minhoca comeu a maçã com o movimento efetuado.
    	if(checaSeComeu(minhoca, pos)){
        	crescerMinhoca(minhoca, &tamanho, tailX, tailY);
        	pos = gerarConsumivel(minhoca, tamanho);
        }
        refresh(); // Atualizar tela.
        
	}
    
    return 0;
}

#include <ncurses/ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <time.h>

#include "header.h"

// Variáveis globais
Consumivel pos; //Posição atual da maçã
int WIDTH = 14; // Comprimento
int HEIGHT = 5; // Largura

int main(){
	setlocale(LC_ALL, "pt_BR.UTF-8");
	// Acentos e cedilhas funcionarão a depender do S.O e fatores externos envolvidos.
	
	// Funções biblioteca ncurses
    initscr();
    clear();
    noecho(); 
    curs_set(0);
    keypad(stdscr, TRUE); // leitura das teclas
    
	int direcao = KEY_DOWN;
	int anterior = KEY_DOWN;
	int tamanho = 3; // Tamanho da minhoca, inicia como 3.
	int tamanhoM = 3; // Tamanho máximo atingido.
	int cont = 0; // Movimentos
	bool jogar = true;
	// Alocação de memória da minhoca.
	Minhoca *minhoca = (Minhoca*) calloc(WIDTH*HEIGHT, sizeof(Minhoca));
	if(minhoca == NULL){
		endwin();
		fprintf(stderr, "Falha na alocação de memória.\n");
		return -1;
	}
	
    selecionarMenu();
    inicializarMinhoca(minhoca);
    pos = gerarConsumivel(minhoca, tamanho);
    
    // Loop do jogo.
	while(jogar){
		clear();
		desenharParedes();
		desenharConsumivel(pos);
		desenharMinhoca(minhoca, tamanho); // Segmentos
		mostrarInfo();
		mostrarInfoStats(minhoca, tamanho, tamanhoM, cont);
		
		// Captar movimento:
		int tecla;
		do tecla = getch(); // Enquanto movimento for inválido.
		while(!checaMovimento(anterior, tecla)); 
		
		anterior = tecla;
		++cont; // Movs.
		usleep(10000);  // microsegundos
		
		// Posição atual do rabo (tail) da minhoca:
		int tailX = minhoca[tamanho-1].x;
		int tailY = minhoca[tamanho-1].y;
		
		// Computar tecla e verificar se próximo movimento terá colisão com parede.
		bool colidiu = preComputarMovimento(tecla, minhoca, tamanho, &direcao);
		if(!colidiu) movimentoNormal(direcao, minhoca, tamanho);
		
		// Checar se a minhoca morreu após o movimento efetuado.
	    if(checaMorte(minhoca, tamanho)){
			jogar = selecionarReinicio(false);
			if(jogar) reiniciaJogo(minhoca, &tamanho, &cont, &anterior);
			continue;
		}
		
		// Checar se a minhoca comeu a maçã com o movimento efetuado e 
		// checa se o vencedor comeu a última maçã do jogo (venceu).
    	if(checaSeComeu(minhoca, pos)){
        	crescerMinhoca(minhoca, &tamanho, tailX, tailY);
        	if(tamanho >= tamanhoM) tamanhoM = tamanho;
			
			// Checa se a minhoca não atingiu seu limite (não terminou o jogo).
			if(tamanho != WIDTH*HEIGHT) pos = gerarConsumivel(minhoca, tamanho);
			// Comeu a última maçã e venceu o jogo:
			else{ 
				jogar = selecionarReinicio(true); 
				if(jogar) reiniciaJogo(minhoca, &tamanho, &cont, &anterior);
			}
        }
        
		refresh(); // Atualizar tela
	}
	
    free(minhoca);
    endwin();
	printf("Fim do jogo.\n");
    getch();
    
	return 0;
}

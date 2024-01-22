// Funções que gerenciam a interface textual do jogo.

#include <ncurses/ncurses.h>

#include "header.h"

// Largura e comprimento do menu.
#define L 28
#define C 7
#define INICIO 3

void mostrarInfo(){
	mvprintw(0,34,"Em desenvolvimento...");
	mvprintw(2,34,"Implementações que ainda faltam:");
	mvprintw(4,34,"adicionar sons de efeito (SFX) e outros.");
	
	mvprintw(7,34,"Implementações já criadas:");
	mvprintw(9,34,"Geração do mapa, Geração da maçã, definição de paredes, colisão, ");
	mvprintw(10,34,"transferir minhoca para lado oposto da colisão, proteção p/ entrada inválida, ");
	mvprintw(11,34,"impedir minhoca de poder andar para sentido contrário (morte), ");
	mvprintw(12,34,"reinício da rodada após morte, sistema de pontuação, mensagem de fim de jogo");
	mvprintw(13,34,"e sistema que controla a trajetória da minhoca (Vetor alocado dinamicamente).");
}

void mostrarInfoStats(Minhoca *minhoca, int tamanho, int tamanhoM, int cont){
	mvprintw(13,1,"Info. úteis para teste:");
	mvprintw(15,1,"Movimentos: %d", cont);
	mvprintw(16,1,"Tamanho:    %d (Cabeça + %d segmentos)", tamanho, tamanho-1);
	mvprintw(18,1,"Rabo da minhoca: (%d,%d)", minhoca[tamanho-1].x, minhoca[tamanho-1].y);
	mvprintw(19,1,"Cabeça: (%d,%d)", minhoca->x, minhoca->y);
	mvprintw(20,1,"Posição da comida: (%d,%d)", pos.x, pos.y);
	mvprintw(21,1,"------------------------");
	mvprintw(23,1,"Tamanho máximo atingido: %d", tamanhoM);
	mvprintw(26,1,"Memória alocada (*minhoca):   %zu bytes.", (WIDTH*HEIGHT)*sizeof(minhoca));
	mvprintw(27,1,"Memória utilizada (*minhoca): %zu bytes.", tamanhoM*sizeof(minhoca));
}

void mostrarMenu(){
	for(int i = 0; i < C;++i) mvprintw(i, 0, "#");
	for(int i = 1; i < C;++i) mvprintw(i, L-1, "#");
	for(int i = 0; i < L;++i) mvprintw(0, i, "#");
	for(int i = 1; i < L;++i) mvprintw(C-1, i, "#");
	
	mvprintw(1, C/2, "Deseja jogar novamente?");
	mvprintw(INICIO, L/2-1, "Sim");
	mvprintw(INICIO+1, L/2-1, "Não");
}

bool selecionar(){
	int escolha = -1;
	int linha = 0; // Inicia como Sim.
	while(escolha != 10){
		clear();
		mostrarMenu();
		{     // Escolha atual.
			mvprintw(INICIO+linha, 9, ">");
			mvprintw(INICIO+linha, 19, "<");
		}
		escolha = getch();
		switch(escolha){
			case KEY_UP:
				if(linha == 0) break;
				--linha;
				break;
			case KEY_DOWN:
				if(linha == 1) break;
				++linha;
				break;
			case 10: // 10 <=> ENTER (ASCII).
				if(INICIO+linha == 3) return true;
				return false;
		}
		refresh();
	}
}

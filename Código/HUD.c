// Funções que gerenciam a interface textual do jogo.

#include <ncurses/ncurses.h>

#include "header.h"

// Largura e comprimento do menu inicial.
#define L_M 34
#define C_M 8
// Largura e comprimento do menu de reinício.
#define L_R 28
#define C_R 7
// Linhas do eixo x que contém a primeira escolha dos menus.
#define INICIO_M 13
#define INICIO_R 3


void mostrarInfo(){
	mvprintw(0,33,"Em desenvolvimento...");
	
	mvprintw(2,33,"Implementações já criadas:");
	mvprintw(4,33,"Geração do mapa, Geração da maçã, definição de paredes, colisão, ");
	mvprintw(5,33,"transferir minhoca para lado oposto da colisão, proteção p/ entrada inválida, ");
	mvprintw(6,33,"impedir minhoca de poder andar para sentido contrário (morte), reinício da");
	mvprintw(7,33,"rodada após morte, sistema de pontuação, seleção de tamanho do mapa, sistema ");
	mvprintw(8,33,"que mostra prévia do mapa selecionada, e sistema que controlara a trajetória");
	mvprintw(9,33,"da minhoca (Vetor alocado dinamicamente).");
	
	mvprintw(27,1,"Código criado por Ivis Muzi.");
}

void mostrarInfoStats(Minhoca *minhoca, int tamanho, int tamanhoM, int cont){
	mvprintw(13,1,"Info. úteis para teste:");
	mvprintw(15,1,"Movimentos: %d", cont);
	mvprintw(16,1,"Tamanho:    %d (Cabeça + %d segmentos)", tamanho, tamanho-1);
	mvprintw(18,1,"Rabo da minhoca: (%d,%d)", minhoca[tamanho-1].x, minhoca[tamanho-1].y);
	mvprintw(19,1,"Cabeça: (%d,%d)", minhoca->x, minhoca->y);
	mvprintw(20,1,"Posição da comida: (%d,%d)", pos.x, pos.y);
	mvprintw(21,1,"-------------------------------");
	mvprintw(22,1,"Tamanho máximo atingido: %d", tamanhoM);
	mvprintw(24,1,"Memória alocada (*minhoca):   %zu bytes.", (WIDTH*HEIGHT)*sizeof(minhoca));
	mvprintw(25,1,"Memória utilizada (*minhoca): %zu bytes.", tamanhoM*sizeof(minhoca));
}

void menuInicial(){
	for(int i = 0; i < C_M;++i) mvprintw(i+10, 0, "#");
	for(int i = 1; i < C_M;++i) mvprintw(i+10, L_M-1, "#");
	for(int i = 0; i < L_M;++i) mvprintw(0+10, i, "#");
	for(int i = 1; i < L_M;++i) mvprintw(C_M-1+10, i, "#");
	
	mvprintw(11, C_M/2, "Escolha o tamanho do mapa: ");
	mvprintw(INICIO_M, L_M/2-3, "Pequeno");
	mvprintw(INICIO_M+1, L_M/2-3, "Médio");
	mvprintw(INICIO_M+2, L_M/2-3, "Grande");
}

// Quando selecionando um mapa, mostrar uma prévia dele na direita do menu.
//                                 0 - Pequeno | 1 - Médio | 2 - Grande 

int selecionarMenu(){
	int escolha = -1;
	int linha = 0; // Inicia como Pequeno, assim como na var. global na main()
	while(escolha != 10){
		clear();
		menuInicial();
		desenharParedes();
		{     // Escolha atual.
			mvprintw(INICIO_M+linha, 10, ">");
			mvprintw(INICIO_M+linha, 23, "<");
		}
		escolha = getch();
		switch(escolha){  // 0 e 2 são os extremos do menu, usa-se esses números para limitar a seleção.
			case KEY_UP:
				if(linha == 0) break;
				--linha;
				break;
			case KEY_DOWN:
				if(linha == 2) break;
				++linha;
				break;
			case 10: // 10 <=> ENTER (ASCII).
				break;
		}
		if(linha == 0){         // Pequeno
			WIDTH = 14;
			HEIGHT = 5;
		}
		else if(linha == 1){    // Médio
			WIDTH = 20;
			HEIGHT = 6;
		}
		else{                   // Grande
			WIDTH = 25;
			HEIGHT = 7;
		}
		refresh();
	}
}

void menuReinicio(){
	for(int i = 0; i < C_R;++i) mvprintw(i, 0, "#");
	for(int i = 1; i < C_R;++i) mvprintw(i, L_R-1, "#");
	for(int i = 0; i < L_R;++i) mvprintw(0, i, "#");
	for(int i = 1; i < L_R;++i) mvprintw(C_R-1, i, "#");
	
	mvprintw(1, C_R/2, "Deseja jogar novamente?");
	mvprintw(INICIO_R, L_R/2-1, "Sim");
	mvprintw(INICIO_R+1, L_R/2-1, "Não");
}

// Receberá argumento 'true' caso o jogador vença, 'false' caso contrário
bool selecionarReinicio(bool ganhou){
	int escolha = -1;
	int linha = 0; // Inicia como Sim.
	while(escolha != 10){
		clear();
		if(ganhou) mvprintw(2, L_R/2-5, "Você ganhou!");
		menuReinicio();
		{     // Escolha atual.
			mvprintw(INICIO_R+linha, 9, ">");
			mvprintw(INICIO_R+linha, 19, "<");
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
				if(INICIO_R+linha == 3) return true;
				return false;
		}
		refresh();
	}
}

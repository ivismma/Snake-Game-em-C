#include <stdbool.h>

void inicializarMinhoca(Minhoca *minhoca){
	// Inicializa a minhoca com uma cabeça e uma parte.
	minhoca->x = WIDTH/2;
    minhoca->y = HEIGHT/2;
	minhoca[1].x = minhoca->x; 
	minhoca[1].y = minhoca->y-1;
}
#include <stdbool.h>
#include <ncurses/ncurses.h>

void inicializarMinhoca(Minhoca *minhoca){
	// Inicializa a minhoca com uma cabeça e uma parte.
	minhoca->x = WIDTH/2;
    minhoca->y = HEIGHT/2;
	minhoca[1].x = minhoca->x; 
	minhoca[1].y = minhoca->y-1;
}

void desenharParedes(){
	// Paredes verticais
	for(int i = 0; i < HEIGHT+1;++i) mvprintw(i, 0, "#");
	for(int i = 1; i < HEIGHT+1;++i) mvprintw(i, WIDTH+1, "#");
	// Paredes horizontais
	for(int i = 1; i < WIDTH+2;++i) mvprintw(0, i, "#");
	for(int i = 0; i < WIDTH+2;++i) mvprintw(HEIGHT+1, i, "#");
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
bool checaColisao(Minhoca *minhoca, int x, int y){
	// Colisão com parede vertical
	if(y == 0 || y >= HEIGHT+1) return true;
	// Colisão com parede horizontal
	else if(x == 0 || x >= WIDTH+1) return true;

	else return false; // Não haverá colisão.
}

bool checaMorte(Minhoca *minhoca, int tam){
	for(int i = 1; i < tam;++i){
		if(minhoca->x == minhoca[i].x && minhoca->y == minhoca[i].y)
			return true; // Colisão
	}
	// A cabeça da minhoca não colidiu com si mesma.
	return false;
}

Consumivel gerarConsumivel(Minhoca *minhoca,  int tam){
	srand(time(NULL));
	bool disponivel; 
	do{ // Tenta criar uma maçã em um lugar disponível.
		disponivel = true;
		pos.x = rand()%WIDTH + 1;
		pos.y = rand()%HEIGHT + 1;
		for(int i = 0; i < tam; ++i){
			if(pos.x == minhoca[i].x && pos.y == minhoca[i].y)
				disponivel = false; // Coordenada gerada está ocupada pela minhoca.
		}
	} while(!disponivel);
	mvprintw(pos.y, pos.x, "-");
	return pos;
}

void desenharConsumivel(Consumivel pos){
	mvprintw(pos.y,pos.x, "-");
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

void mostrarInfo(){
	mvprintw(0,34,"Em desenvolvimento...");
	mvprintw(2,34,"Implementações que ainda faltam:");
	mvprintw(4,34,"impedir minhoca de se movimentar a si mesmo (morte),");
	mvprintw(5,34,"reinício da rodada após morte, sistema de pontuação, mensagem de fim de jogo.");
	mvprintw(6,34,"adicionar sons de efeito (SFX) e outros.");
	
	mvprintw(8,34,"Implementações já criadas:");
	mvprintw(10,34,"Geração do mapa, Geração da maçã, definição de paredes, colisão, ");
	mvprintw(11,34,"transferir minhoca para lado oposto da colisão, proteção p/ entrada inválida");
	mvprintw(12,34,"e sistema que controla a trajetória da minhoca (Vetor alocado dinamicamente).");
}

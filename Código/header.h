#include <stdbool.h>

// Struct que será alocada dinâmicamente para conter as posiçőes em que se encontram
//  as partes da minhoca. Será alocado (linha x colunas) espaços no vetor dinâmico 
// (WIDTH*HEIGHT), a cabeça da minhoca é o primeiro índice do vetor.

typedef struct{
    int x, y;
} Minhoca;

typedef Minhoca Consumivel; // O consumível possui mesma estrutura (x e y).

extern Consumivel pos;
extern int WIDTH;
extern int HEIGHT;

void desenharParedes();
void desenharMinhoca(Minhoca *minhoca, int tam);
void atualizarMinhoca(Minhoca *minhoca, int tam);
bool checaColisao(Minhoca *minhoca, int x, int y);
bool checaMovimento(int anterior, int atual);
bool checaMorte(Minhoca *minhoca, int tam);
Consumivel gerarConsumivel(Minhoca *minhoca, int tam);
void desenharConsumivel(Consumivel pos);
void inicializarMinhoca(Minhoca *minhoca);
bool checaSeComeu(Minhoca* minhoca, Consumivel pos);
void crescerMinhoca(Minhoca *minhoca, int *tam, int x, int y);
bool preComputarMovimento(int tecla, Minhoca *minhoca, int tamanho, int *direcao);
void movimentoNormal(int direcao, Minhoca *minhoca, int tamanho);
void mostrarInfo();
void mostrarInfoStats(Minhoca *minhoca, int tamanho, int tamanhoM, int cont);
void menuReinicio();
void menuInicial();
int selecionarMenu();
bool selecionarReinicio();
void reiniciaJogo(Minhoca *minhoca, int *tamanho, int *cont, int *ant);

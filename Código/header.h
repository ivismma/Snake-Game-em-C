#include <stdbool.h>

// Tamanho: Pequeno: 14 e 5, Médio: 20 e 6, Grande: 25 e 7.
// Default: Médio
#define WIDTH 20   // Tam Horizontal
#define HEIGHT 6   // Tam Vertical

// Struct que será alocada dinâmicamente para conter as posições em que se 
// encontram as partes da minhoca. Será alocado 120 espaços no vetor dinâmico 
// (WIDTH*HEIGHT), a cabeça da minhoca é o primeiro índice do vetor.
typedef struct{
    int x, y;
} Minhoca;

typedef Minhoca Consumivel; // O consumível possui mesma estrutura (x e y).

extern Consumivel pos;

void desenharParedes();
void desenharMinhoca(Minhoca *minhoca, int tam);
void atualizarMinhoca(Minhoca *minhoca, int *tam);
bool checaColisao(Minhoca *minhoca, int x, int y);
bool checaMovimento(int direcao);
bool checaMorte(Minhoca *minhoca, int tam);
Consumivel gerarConsumivel(Minhoca *minhoca, int tam);
void desenharConsumivel(Consumivel pos);
void inicializarMinhoca(Minhoca *minhoca);
bool checaSeComeu(Minhoca* minhoca, Consumivel pos);
void crescerMinhoca(Minhoca *minhoca, int *tam);
void mostrarInfo();

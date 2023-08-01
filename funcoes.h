#include <stdlib.h>
#include <stdio.h>

typedef struct Node *Ponteiro;

typedef struct Info
{
    double valor;
    

} Info;

typedef struct TipoItem {
  TipoChave Chave;
  /* outros componentes */
} TipoItem;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct TipoFila {
  TipoApontador Frente, Tras;
} TipoFila;

void Inicializar(TipoFila *Fila);
int Vazia(TipoFila Fila);
void Enfileira(TipoItem x, TipoFila *Fila);
void Desenfileira(TipoFila *Fila, TipoItem *Item);
void Imprime(TipoFila Fila);

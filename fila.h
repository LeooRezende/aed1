#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Transacao
{
    double valor;
    char data[11];
    char descricao[100];
    struct Transacao *next;

} Transacao;

typedef struct Fila
{
    Transacao *frente;
    Transacao *tras;

} Fila;

Transacao *criarTransacao(double valor, const char *data, const char *descricao);
Fila *criarFila();
int taVazia(Fila *fila);
void adicionarTransacao(Fila *fila, Transacao *novaTransacao);
Transacao *tirarTransacao(Fila *fila);
void mostrarHistorico(Fila *fila);
void liberarFila(Fila *fila);

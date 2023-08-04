#include <time.h>

typedef struct Transacao
{
    double valor;
    int tipo;
    char dataHora[20]; // "dd/mm/yyyy HH:MM:SS\0"
    char descricao[102];
    struct Transacao *next;
} Transacao;

typedef struct Fila
{
    Transacao *frente;
    Transacao *tras;
} Fila;

Transacao *criarTransacao(double valor, int tipo, const char *dataHora, const char *descricao);
Fila *criarFila();
int taVazia(Fila *fila);
void adicionarTransacao(Fila *fila, Transacao *novaTransacao);
Transacao *tirarTransacao(Fila *fila);
void mostrarHistorico(Fila *fila);
void liberarFila(Fila *fila);

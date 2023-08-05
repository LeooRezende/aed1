#include <time.h>
#include <stdbool.h>

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
bool compararTransacoesDecrescente(Transacao *transacao1, Transacao *transacao2);
bool compararTransacoesCrescente(Transacao *transacao1, Transacao *transacao2);
bool compararDatasDecrescente(Transacao *transacao1, Transacao *transacao2);

int particionar(Transacao **transacoesArray, int esquerda, int direita, bool (*comparar)(Transacao *, Transacao *));

const char* obterTipoTransacaoString(int tipo);

void selectionSort(Transacao **transacoesArray, int numTransacoes, bool (*comparar)(Transacao *, Transacao *));
void ordenarFila(Fila *fila, bool (*comparar)(Transacao *, Transacao *));
void bubbleSortDescendingTransacoes(Fila *fila);
void quicksortTransacoesPorData(Transacao **transacoesArray, int esquerda, int direita, bool (*comparar)(Transacao *, Transacao *));


#include "funcoes.h"


void Inicializar(TipoFila *Fila)
{
    //Fila->Frente = (TipoApontador) malloc(sizeof(TipoCelula));
    Fila->Frente=NULL;
    Fila->Tras = Fila->Frente;
    //Fila->Frente->Prox = NULL;
} 

int Vazia(TipoFila Fila)
{ 
    return (Fila.Frente == NULL); 
} 

void Enfileira(int a, double b, char c[], char d[], TipoFila *Fila)
{ 
    printf("data antes de enfileirar:%.8s\n", c);
    printf("tipo antes de enfileirar:%.4s\n", d);
    Ponteiro novo = (Ponteiro) malloc(sizeof(Node));
    novo->Transacao.Id=a;
    novo->Transacao.Valor=b;
    novo->Transacao.Data[8]=c[8];
    novo->Transacao.Tipo[4]=d[4];
    novo->Prox=NULL;
    if(Fila->Frente==NULL)
    {
        Fila->Frente=novo;
    }
    else {
        Fila->Tras->Prox=novo;  
    }
    Fila->Tras = novo;
    printf("Transação adicionada: %d \n", novo->Transacao.Id);
    printf("data depois de enfileirar:%.8s\n", c);
    printf("tipo depois de enfileirar:%.4s\n", d);
} 

/*void Desenfileira(TipoFila *Fila, TipoItem *Item)
{
  TipoApontador q;
  if (Vazia(*Fila)) 
  { 
    printf("Erro fila esta vazia\n");
    return; 
  }
  q = Fila->Frente;
  printf("Desenfileirou: %d\n", q->Item.Chave);
  *Item = Fila->Frente->Item;
  Fila->Frente = Fila->Frente->Prox;
  free(q);
  if (Fila->Frente==NULL)
    Fila->Tras=NULL;
}*/

void Imprime(TipoFila Fila)
{
    Ponteiro Aux;
    Aux = Fila.Frente;
    printf("\nHistórico de Transações:\n");
    while (Aux != NULL) 
    { 
        printf("\n");
        printf("=================\n");
        printf("id:%d\n", Aux->Transacao.Id);
        printf("valor:%lf\n", Aux->Transacao.Valor);
        printf("data:%s\n", Aux->Transacao.Data);
        printf("tipo:%s\n", Aux->Transacao.Tipo);
        Aux = Aux->Prox;
    }
}
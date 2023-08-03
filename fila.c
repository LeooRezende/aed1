#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include <time.h>

// cria nova transacao pra ser colocada na hora de adicionar uma transacao na fila
Transacao *criarTransacao(double valor, const char *data, const char *descricao)
{
    Transacao *novaTransacao = (Transacao *)malloc(sizeof(Transacao));

    if (novaTransacao != NULL)
    {
        novaTransacao->valor = valor;
        strcpy(novaTransacao->data, data);
        strcpy(novaTransacao->descricao, descricao);
        novaTransacao->next = NULL;
    }

    return novaTransacao;
}

// cria nova fila vazia a ser adicionada em uma variavel
Fila *criarFila()
{
    Fila *novaFila = (Fila *)malloc(sizeof(Fila));
    if (novaFila != NULL)
    {
        novaFila->frente = NULL;
        novaFila->tras = NULL;
    }

    return novaFila;
}

// ta vazia?
int taVazia(Fila *fila)
{
    return (fila->frente == NULL);
}

// usar funcao criarTransacao no segundo termo
void adicionarTransacao(Fila *fila, Transacao *novaTransacao)
{
    if (novaTransacao != NULL)
    {
        if (taVazia(fila))
        {
            fila->frente = novaTransacao;
            fila->tras = novaTransacao;
        }
        else
        {
            fila->tras->next = novaTransacao;
            fila->tras = novaTransacao;
        }
    }
}

// apaga e retorna ultima transação
Transacao *tirarTransacao(Fila *fila)
{
    if (taVazia(fila))
    {
        printf("fila vazia vey :/\n");
        return NULL;
    }

    Transacao *antigaTransacao = fila->frente;
    fila->frente = fila->frente->next;

    if (fila->frente->next == NULL)
    {
        fila->frente = NULL;
    }
    return antigaTransacao;
}

void mostrarHistorico(Fila *fila)
{

    int numero = 0;

    if (taVazia(fila))
    {
        printf("fila vazia man, add uma transacao ai\n");
    }

    Transacao *atual = fila->frente;
    while (atual != NULL)
    {
        printf("======================================\n");
        printf("           Transação nº%d           \n", numero);
        printf("Valor: R$%.2lf, Data: %.10s\n", atual->valor, atual->data);
        printf("Descrição: %s\n", atual->descricao);
        atual = atual->next;
        numero++;
    }
    printf("======================================\n");
    numero = 0;
}

// libera a memoria que a fila ta ocupando
void liberarFila(Fila *fila)
{
    while (!taVazia(fila))
    {
        Transacao *antigaTransacao = tirarTransacao(fila);
        free(fila);
    }
}

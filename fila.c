#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fila.h"

Transacao *criarTransacao(double valor, int tipo, const char *dataHora, const char *descricao)
{
    Transacao *novaTransacao = (Transacao *)malloc(sizeof(Transacao));

    if (novaTransacao != NULL)
    {
        novaTransacao->valor = valor;
        novaTransacao->tipo = tipo;
        strncpy(novaTransacao->dataHora, dataHora, sizeof(novaTransacao->dataHora) - 1);
        novaTransacao->dataHora[sizeof(novaTransacao->dataHora) - 1] = '\0'; // Garantir terminação
        strncpy(novaTransacao->descricao, descricao, sizeof(novaTransacao->descricao) - 1);
        novaTransacao->descricao[sizeof(novaTransacao->descricao) - 1] = '\0'; // Garantir terminação
        novaTransacao->next = NULL;
    }

    return novaTransacao;
}
Fila *criarFila()
{
    Fila *novaFila = (Fila *)malloc(sizeof(Fila));
    if (novaFila != NULL)
    {
        novaFila->frente = NULL;
        novaFila->tras = NULL;
    }
    system("clear");

    return novaFila;
}

int taVazia(Fila *fila)
{
    return (fila->frente == NULL);
}

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

Transacao *tirarTransacao(Fila *fila)
{
    if (taVazia(fila))
    {
        printf("Fila vazia!\n");
        return NULL;
    }

    Transacao *antigaTransacao = fila->frente;
    fila->frente = fila->frente->next;

    if (fila->frente == NULL)
    {
        fila->tras = NULL;
    }
    return antigaTransacao;
}

void mostrarHistorico(Fila *fila)
{
    int numero = 0;

    if (taVazia(fila))
    {
        printf("Fila vazia, adicione transações.\n");
        return;
    }

    Transacao *atual = fila->frente;
    while (atual != NULL)
    {
        printf("======================================\n");
        if(atual->tipo==1)
        {
            printf("      Transação nº%d (CRÉDITO)       \n", numero);
        }
        if(atual->tipo==2)
        {
            printf("      Transação nº%d (DÉBITO)       \n", numero);
        }
        //printf("           Transação nº%d           \n", numero);
        printf("Valor: R$%.2lf, Data: %.25s\n", atual->valor, atual->dataHora);
        printf("Descrição: %s\n", atual->descricao);
        atual = atual->next;
        numero++;
    }
    printf("======================================\n");
    numero = 0;
}

void liberarFila(Fila *fila)
{
    while (!taVazia(fila))
    {
        Transacao *antigaTransacao = tirarTransacao(fila);
        free(antigaTransacao);
    }
    free(fila);
}
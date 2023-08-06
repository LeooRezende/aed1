#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "fila.h"

Transacao *criarTransacao(int id, double valor, int tipo, const char *dataHora, const char *descricao)
{
    Transacao *novaTransacao = (Transacao *)malloc(sizeof(Transacao));

    if (novaTransacao != NULL)
    {
        novaTransacao->id = id;
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

/*Transacao *tirarTransacao(Fila *fila)
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
}*/

Transacao *tirarTransacao(Fila *fila)
{
    if (taVazia(fila))
    {
        printf("Fila vazia!\n");
        return NULL;
    }

    Transacao *anterior = NULL;
    Transacao *atual = fila->frente;

    while (atual->next != NULL)
    {
        anterior = atual;
        atual = atual->next;
    }

    if (anterior == NULL)
    {
        fila->frente = NULL;
        fila->tras = NULL;
    }
    else
    {
        anterior->next = NULL;
        fila->tras = anterior;
    }

    return atual;
}


void mostrarHistorico(Fila *fila)
{
    int numero = 1;

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
        printf("ID da Transação: #%d\n", atual->id);
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

bool compararTransacoesDecrescente(Transacao *transacao1, Transacao *transacao2)
{
    return transacao1->valor > transacao2->valor;
}

bool compararTransacoesCrescente(Transacao *transacao1, Transacao *transacao2)
{
    return transacao1->valor < transacao2->valor;
}

bool compararDatasDecrescente(Transacao *transacao1, Transacao *transacao2)
{
    // Compare as datas das transações (use strcmp para comparar as strings de dataHora)
    return strcmp(transacao1->dataHora, transacao2->dataHora) > 0;
}

int particionar(Transacao **transacoesArray, int esquerda, int direita, bool (*comparar)(Transacao *, Transacao *))
{
    Transacao *pivot = transacoesArray[direita];
    int i = esquerda - 1;

    for (int j = esquerda; j <= direita - 1; j++)
    {
        if (comparar(transacoesArray[j], pivot))
        {
            i++;
            Transacao *temp = transacoesArray[i];
            transacoesArray[i] = transacoesArray[j];
            transacoesArray[j] = temp;
        }
    }

    Transacao *temp = transacoesArray[i + 1];
    transacoesArray[i + 1] = transacoesArray[direita];
    transacoesArray[direita] = temp;

    return i + 1;
}


// Função auxiliar para obter uma string representando o tipo de transação
const char* obterTipoTransacaoString(int tipo)
{
    return (tipo == 1) ? "CRÉDITO" : "DÉBITO";
}

void bubbleSortDescendingTransacoes(Fila *fila)
{
    if (taVazia(fila))
    {
        printf("Fila vazia, adicione transações.\n");
        return;
    }

    int numTransacoes = 0;
    Transacao *atual = fila->frente;
    while (atual != NULL)
    {
        numTransacoes++;
        atual = atual->next;
    }

    Transacao **transacoesArray = (Transacao **)malloc(numTransacoes * sizeof(Transacao *));
    if (transacoesArray == NULL)
    {
        printf("Erro ao alocar memória para ordenação.\n");
        return;
    }

    atual = fila->frente;
    for (int i = 0; i < numTransacoes; i++)
    {
        transacoesArray[i] = atual;
        atual = atual->next;
    }

    for (int i = 0; i < numTransacoes - 1; i++)
    {
        int swapped = 0;
        for (int j = 0; j < numTransacoes - i - 1; j++)
        {
            if (transacoesArray[j]->valor < transacoesArray[j + 1]->valor)
            {
                Transacao *temp = transacoesArray[j];
                transacoesArray[j] = transacoesArray[j + 1];
                transacoesArray[j + 1] = temp;
                swapped = 1;
            }
        }

        if (swapped == 0)
            break;
    }

    printf("========================\nTransações Ordenadas:\n");
    for (int i = 0; i < numTransacoes; i++)
    {
        printf("======================================\n");
        printf("      Transação nº%d (%s)\n", i, obterTipoTransacaoString(transacoesArray[i]->tipo));
        printf("Valor: R$%.2lf, Data: %.25s\n", transacoesArray[i]->valor, transacoesArray[i]->dataHora);
        printf("Descrição: %s\n", transacoesArray[i]->descricao);
    }
    printf("========================\n");

    free(transacoesArray);
}

void selectionSort(Transacao **transacoesArray, int numTransacoes, bool (*comparar)(Transacao *, Transacao *))
{
    for (int i = 0; i < numTransacoes - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < numTransacoes; j++)
        {
            if (comparar(transacoesArray[j], transacoesArray[minIndex]))
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            Transacao *temp = transacoesArray[i];
            transacoesArray[i] = transacoesArray[minIndex];
            transacoesArray[minIndex] = temp;
        }

    }
}

void ordenarFila(Fila *fila, bool (*comparar)(Transacao *, Transacao *))
{
    if (taVazia(fila))
    {
        printf("Fila vazia, adicione transações.\n");
        return;
    }

    int numTransacoes = 0;
    Transacao *atual = fila->frente;
    while (atual != NULL)
    {
        numTransacoes++;
        atual = atual->next;
    }

    Transacao **transacoesArray = (Transacao **)malloc(numTransacoes * sizeof(Transacao *));
    if (transacoesArray == NULL)
    {
        printf("Erro ao alocar memória para ordenação.\n");
        return;
    }

    atual = fila->frente;
    for (int i = 0; i < numTransacoes; i++)
    {
        transacoesArray[i] = atual;
        atual = atual->next;
    }

    selectionSort(transacoesArray, numTransacoes, comparar);

    printf("========================\nTransações Ordenadas:\n");
    for (int i = 0; i < numTransacoes; i++)
    {
        printf("======================================\n");
        printf("      Transação nº%d (%s)\n", i, obterTipoTransacaoString(transacoesArray[i]->tipo));
        printf("Valor: R$%.2lf, Data: %.25s\n", transacoesArray[i]->valor, transacoesArray[i]->dataHora);
        printf("Descrição: %s\n", transacoesArray[i]->descricao);
    }
    printf("========================\n");

    free(transacoesArray);
}

void quicksortTransacoesPorData(Transacao **transacoesArray, int esquerda, int direita, bool (*comparar)(Transacao *, Transacao *))
{
    if (esquerda < direita)
    {
        int indiceParticao = particionar(transacoesArray, esquerda, direita, comparar);

        quicksortTransacoesPorData(transacoesArray, esquerda, indiceParticao - 1, comparar);
        quicksortTransacoesPorData(transacoesArray, indiceParticao + 1, direita, comparar);
    }
}

void mostrarTransacoesCredito(Fila *fila)
{
    if (taVazia(fila))
    {
        printf("Fila vazia, não há transações.\n");
        return;
    }

    int numero = 0;
    Transacao *atual = fila->frente;

    while (atual != NULL)
    {
        if (atual->tipo == 1) // Verifica se é do tipo crédito (1)
        {
            printf("======================================\n");
            printf("      Transação nº%d (CRÉDITO)\n", numero);
            printf("Valor: R$%.2lf, Data: %.25s\n", atual->valor, atual->dataHora);
            printf("Descrição: %s\n", atual->descricao);
            numero++;
        }

        atual = atual->next;
    }

    if (numero == 0)
    {
        printf("Não há transações do tipo CRÉDITO.\n");
    }
}

Transacao *buscaBinariaTransacao(Transacao **transacoesArray, int esquerda, int direita, bool (*comparar)(Transacao *, Transacao *), int tipoBuscado)
{
    if (direita >= esquerda)
    {
        int meio = esquerda + (direita - esquerda) / 2;

        if (transacoesArray[meio]->tipo == tipoBuscado)
        {
            return transacoesArray[meio];
        }

        if (comparar(transacoesArray[meio], transacoesArray[meio + 1]) && tipoBuscado == 2)
        {
            return buscaBinariaTransacao(transacoesArray, esquerda, meio - 1, comparar, tipoBuscado);
        }

        return buscaBinariaTransacao(transacoesArray, meio + 1, direita, comparar, tipoBuscado);
    }

    return NULL;
}

void mostrarTransacoesDebito(Fila *fila)
{
    if (taVazia(fila))
    {
        printf("Fila vazia, não há transações.\n");
        return;
    }

    int numTransacoes = 0;
    Transacao *atual = fila->frente;

    while (atual != NULL)
    {
        numTransacoes++;
        atual = atual->next;
    }

    Transacao **transacoesArray = (Transacao **)malloc(numTransacoes * sizeof(Transacao *));
    if (transacoesArray == NULL)
    {
        printf("Erro ao alocar memória para ordenação.\n");
        return;
    }

    atual = fila->frente;
    for (int i = 0; i < numTransacoes; i++)
    {
        transacoesArray[i] = atual;
        atual = atual->next;
    }

    // Ordenar a fila por data (do mais novo ao mais antigo) para a busca binária
    quicksortTransacoesPorData(transacoesArray, 0, numTransacoes - 1, compararDatasDecrescente);

    Transacao *debitoEncontrado = buscaBinariaTransacao(transacoesArray, 0, numTransacoes - 1, compararDatasDecrescente, 2);

    if (debitoEncontrado == NULL)
    {
        printf("Não há transações do tipo DÉBITO.\n");
    }
    else
    {
        int numero = 0;
        for (int i = 0; i < numTransacoes; i++)
        {
            if (transacoesArray[i]->tipo == 2)
            {
                printf("======================================\n");
                printf("      Transação nº%d (DÉBITO)\n", numero);
                printf("Valor: R$%.2lf, Data: %.25s\n", transacoesArray[i]->valor, transacoesArray[i]->dataHora);
                printf("Descrição: %s\n", transacoesArray[i]->descricao);
                numero++;
            }
        }
    }

    free(transacoesArray);
}
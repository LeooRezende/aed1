#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.c"
#include <time.h>

int main()
{
    Fila *filalegal = criarFila();

    // criando e adicionando algumas transacoes no historico aka fila
    adicionarTransacao(filalegal, criarTransacao(24.5, "01/08/2023", "fardo de cerveja"));
    adicionarTransacao(filalegal, criarTransacao(25.5, "02/08/2023", "mais um fardinho kk"));
    adicionarTransacao(filalegal, criarTransacao(30, "03/08/2023", "nossa o preco do fardo subiu ne"));
    // adicionarTransacao(filalegal, criarTransacao(34.9, "04/08/2023", "DOBROU DE PRECO MAN"));
    // adicionarTransacao(filalegal, criarTransacao(40, "05/08/2023", "vai po caralho vou devolve"));

    // tirando a ultima transacao
    /*Transacao *antigaTransacao = tirarTransacao(filalegal);
    if (antigaTransacao != NULL)
    {
        printf("\nTransacao removida:\n");
        printf("Valor:%.2lf, Data:%s, Descricao:%s\n", antigaTransacao->valor, antigaTransacao->data, antigaTransacao->descricao);
        free(antigaTransacao);
    }*/

    int numero, temp;
    double valor;
    char data[10];
    char descricao[100];
    char oi[1];

    while (1)
    {
        system("clear");
        printf("\n");
        printf("Escolha uma opção:\n\n");
        printf("1. MOSTRAR HISTÓRICO (mais antigo até mais novo)\n");
        printf("2. ADICIONAR TRANSAÇÃO\n");
        printf("3. FECHAR PROGRAMA\n");

        scanf("%d", &numero);

        if (numero == 3)
            break;
        if (numero == 1)
        {
            mostrarHistorico(filalegal);
            printf("\nDigite qualquer coisa e dê ENTER para retornar ao menu.");
            scanf("%s", oi);
        }
        if (numero == 2)
        {
            printf("Valor da transação: ");
            scanf("%lf", &valor);
            fflush(stdin);
            printf("Data da transação: ");
            // scanf("%s", data);
            fgets(data, 10, stdin);
            printf("Descrição simples: ");
            // scanf("%[^\n]%*c", descricao);
            fgets(descricao, 100, stdin);
            adicionarTransacao(filalegal, criarTransacao(valor, data, descricao));
            printf("Transação feita com sucesso!\n");
        }
    }

    // mostrando historico, obviamente
    // mostrarHistorico(filalegal);

    // liberando a memoria e tals
    liberarFila(filalegal);

    return 0;
}
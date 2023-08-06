#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include <time.h>
#include <stdbool.h>

int main(){
    Fila *filalegal = criarFila();

    int id =202300;
    int escolha = 0;
    double valor, saldo=0;
    char descricao[102];
    int tipo=0;
    int numTransacoes = 0;

    //adicionando transações exemplo"
    /*adicionarTransacao(filalegal, criarTransacao(id, 12, 1, "01/08/2023 12:00:00", "sabonete"));
    numTransacoes++;
    id++;
    saldo=saldo+12;
    adicionarTransacao(filalegal, criarTransacao(id, 5.5, 2, "02/08/2023 12:00:00", "cerveja"));
    numTransacoes++;
    id++;
    saldo=saldo-5.5;
    adicionarTransacao(filalegal, criarTransacao(id, 100, 1, "03/08/2023 12:00:00", "quininha"));
    numTransacoes++;
    id++;
    saldo=saldo+100;
    adicionarTransacao(filalegal, criarTransacao(id, 300, 1, "04/08/2023 12:00:00", "achei na rua slc"));
    numTransacoes++;
    id++;
    saldo=saldo+300;
    adicionarTransacao(filalegal, criarTransacao(id, 250.5, 2, "05/08/2023 12:00:00", "blaze"));
    numTransacoes++;
    id++;
    saldo=saldo-250.5;*/


    while (1)
    {
        system("clear");
        printf("Escolha uma opção:\n\n");
        printf("1. ADICIONAR TRANSAÇÃO\n");
        printf("2. MOSTRAR HISTÓRICO E SALDO (mais antigo até mais novo)\n");
        printf("3. MOSTRAR HISTÓRICO E SALDO (mais novo até mais antigo)\n");
        printf("4. TIRAR ÚLTIMA TRANSAÇÃO\n");
        printf("5. MOSTRAR HISTÓRICO ORGANIZADO POR VALOR (maior para o menor)\n");
        printf("6. MOSTRAR HISTÓRICO ORGANIZADO POR VALOR (menor para o maior)\n");
        printf("7. MOSTRAR HISTÓRICO DE CRÉDITOS\n");
        printf("8. MOSTRAR HISTÓRICO DE DÉBITOS\n");
        printf("9. FECHAR PROGRAMA\n");


        scanf("%d", &escolha);
        system("clear");
        switch (escolha)
        {
        case 1:
            printf("Valor da transação: ");
            scanf("%lf", &valor);
            getchar(); // Consumir o caractere de nova linha

            time_t t = time(NULL);
            struct tm *data_atual = localtime(&t);
            char dataHora[20];
            strftime(dataHora, sizeof(dataHora), "%d/%m/%Y %H:%M:%S", data_atual);

            printf("Tipo de transação (1 para crédito, 2 para débito): ");
            scanf("%d", &tipo);
            getchar();
            if(tipo!=1 && tipo!=2)
            {
                printf("\nTipo inválido. Pressione Enter para retornar.\n");
                break;
            }
            if(tipo==1)
            {
                saldo=saldo+valor;
                printf("Crédito escolhido.\n");
            }
            if(tipo==2)
            {
                saldo=saldo-valor;
                if(saldo<0) printf("Saldo negativo, cuidado com as dívidas hein...\n");
                printf("Débito escolhido.\n");
            }

            printf("Descrição simples: ");
            fgets(descricao, sizeof(descricao), stdin);
            descricao[strlen(descricao) - 1] = '\0'; // Remover o '\n' do final
            adicionarTransacao(filalegal, criarTransacao(id, valor, tipo, dataHora, descricao));
            numTransacoes++;
            id++;
            printf("Transação adicionada com sucesso! Pressione Enter para retornar.\n");
            break;
        case 2: 
            printf("========================\nSaldo atual: R$%.2lf ||\n", saldo);
            mostrarHistorico(filalegal);
            printf("\nPressione Enter (talvez duas vezes) para retornar ao menu.\n");
            getchar(); // Aguardar um novo caractere
            break;


        case 3:
        {
            Transacao *transacoesArray[numTransacoes];
            for (int i = 0; i < numTransacoes; i++)
            {
                transacoesArray[i] = NULL;
            }

            Transacao *atual = filalegal->frente;
            int i = 0;
            while (atual != NULL)
            {
                transacoesArray[i] = atual;
                atual = atual->next;
                i++;
            }

            quicksortTransacoesPorData(transacoesArray, 0, numTransacoes - 1, compararDatasDecrescente);

            printf("========================\nTransações Ordenadas por Data (mais novo -> mais antigo):\n");
            for (int i = 0; i < numTransacoes; i++)
            {
                printf("======================================\n");
                printf("      Transação nº%d (%s)\n", i+1, obterTipoTransacaoString(transacoesArray[i]->tipo));
                printf("Valor: R$%.2lf, Data: %.25s\n", transacoesArray[i]->valor, transacoesArray[i]->dataHora);
                printf("Descrição: %s\n", transacoesArray[i]->descricao);
                printf("ID da Transação: #%d\n", transacoesArray[i]->id);
            }
            printf("========================\n");

            printf("\nPressione Enter (talvez duas vezes) para retornar ao menu.\n");
            getchar(); // Aguardar um novo caractere
        }
        break;

        case 4:
        {
            Transacao *transacaoRemovida = tirarTransacao(filalegal);
            if (transacaoRemovida != NULL)
            {
                if (transacaoRemovida->tipo == 1)
                {
                    saldo -= transacaoRemovida->valor;
                    printf("\nTransação de crédito removida. Dinheiro debitado.\n");
                }
                else if (transacaoRemovida->tipo == 2)
                {
                    saldo += transacaoRemovida->valor;
                printf("\nTransação de débito removida. Dinheiro estornado.\n");
                }

            printf("Valor: R$%.2lf, Data/Hora: %s\n", transacaoRemovida->valor, transacaoRemovida->dataHora);
            printf("Descrição: %s\n", transacaoRemovida->descricao);
            numTransacoes--;
            free(transacaoRemovida);
            }   
            else
            {
                printf("Não há transações para remover.\n");
            }
                printf("\nPressione Enter (talvez duas vezes) para retornar ao menu.\n");
                getchar(); // Aguardar um novo caractere
        }       
        break;

        case 5:
            bubbleSortDescendingTransacoes(filalegal);
            printf("\nPressione Enter (talvez duas vezes) para retornar ao menu.\n");
            getchar(); // Aguardar um novo caractere
        break;

        case 6:
            ordenarFila(filalegal, compararTransacoesCrescente);
            printf("\nPressione Enter (talvez duas vezes) para retornar ao menu.\n");
            getchar(); // Aguardar um novo caractere
            break;

        case 7:
            mostrarTransacoesCredito(filalegal);
            printf("\nPressione Enter para retornar ao menu.\n");
            getchar();
            getchar(); // Aguardar dois Enter para retornar ao menu
            break;
        case 8:
            mostrarTransacoesDebito(filalegal);
            printf("\nPressione Enter para retornar ao menu.\n");
            getchar();
            getchar(); // Aguardar dois Enter para retornar ao menu
            break;
        case 9:
            liberarFila(filalegal);
            printf("Programa encerrado.\n");
            return 0;
        default:
            printf("Opção inválida. Escolha novamente.\n");
        }

        getchar(); // Consumir o caractere de nova linha pendente
    }

    return 0;
}



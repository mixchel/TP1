#include "lista_processo.h"
#define ops_por_arquivo 2
#define ops_por_terminal 1
#define tam_nome_arquivo 100

void opera_lista(int tam_vetor, int num_teste, int qntd_de_operacoes, int *tipo_de_operacao, int *reps_da_operacao);

int main() {
    int num_teste, tam_vetor, tipo_de_operacao[ops_por_arquivo], reps_da_operacao[ops_por_arquivo], qntd_linhas;
    char tipo_da_entrada;
    char nome_arquivo[tam_nome_arquivo];

    srand(time(NULL));

    printf("Qual formato de entrada de dados? Arquivo (a) ou Terminal (t):\n");
    scanf("%s", &tipo_da_entrada);

    if (tipo_da_entrada == 't') {

        printf("Entre com o numero do teste:\n");
        scanf("%d", &num_teste);
        printf("Entre com o tamanho do vetor:\n");
        scanf("%d", &tam_vetor);
        printf("Qual operacao sera feita: Insercao (0)| Remocao (1)\n");
        scanf("%d", tipo_de_operacao);
        printf("Quantas vezes a operacao sera feita:\n");
        scanf("%d", reps_da_operacao);

        opera_lista(tam_vetor, num_teste, ops_por_terminal, tipo_de_operacao, reps_da_operacao);
        
    } else if (tipo_da_entrada == 'a'){

        printf("Entre com o nome do arquivo:\n");
        scanf("%s", nome_arquivo);
        printf("Entre com o numero do primeiro teste:\n");
        scanf("%d", &num_teste);

        FILE *fileptr;
        fileptr = fopen(nome_arquivo, "r");
        if (fileptr != NULL){
            fscanf(fileptr, "%d", &tam_vetor);
            fscanf(fileptr, "%d", &qntd_linhas);
            for (int i = 0; i < qntd_linhas; ++i) {

                fscanf(fileptr, "%d %d", &tipo_de_operacao[i], &reps_da_operacao[i]);
            }

            opera_lista(tam_vetor, num_teste, qntd_linhas, tipo_de_operacao, reps_da_operacao);
            fclose(fileptr);
        }
        else {
            printf("ERRO: Arquivo nao encontrado!");
        }
    } 
    else {
        printf("ERRO: Entrada invalida!");
    }

    return 0;
}


void opera_lista(int tam_vetor, int num_teste, int qntd_de_operacoes, int *tipo_de_operacao, int *reps_da_operacao){

    lista_processo *lista_teste;
    lista_teste = (lista_processo*) malloc(sizeof(lista_processo));
    cria_lista(lista_teste, tam_vetor);

    FILE *ptrarquivo_saida;
    ptrarquivo_saida = fopen("saida.txt","w");

    for (int i = 0; i < qntd_de_operacoes; i++) {   

        clock_t tempo_inicial = clock();

        if (tipo_de_operacao[i] == 0) { 

            for (int j = 0; j < reps_da_operacao[i]-1; ++j) {

                tipo_processo *processo_teste;
                processo_teste = initprocesso();
                insere_ordenado(lista_teste, *processo_teste);
            }
            imprime_lista(lista_teste);
        }
        else if (tipo_de_operacao[i] == 1) {

            for (int j = 0; j < reps_da_operacao[i]; ++j) {

                retira_primeiro(lista_teste);
            } 
            imprime_lista(lista_teste);
        }
            else {

                printf("ERRO: Operacao invalida!");
            }

        clock_t tempo_final = clock();
        double tempo_diferenca = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
        fprintf(ptrarquivo_saida, "Teste %d: %lf segundos\n\n", num_teste+i, tempo_diferenca);
    }
    fclose(ptrarquivo_saida);
}
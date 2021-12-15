#include "lista_processo.h"

void opera_lista(int tam_vetor, int tipo_de_operacao, int qntd_de_operacao, int num_teste);

int main() {
    int num_teste, tam_vetor, tipo_de_operacao, qntd_de_operacao, qntd_linhas;
    char tipo_da_entrada;
    char nome_arquivo[100];
    srand(time(NULL));

    printf("Qual formato de entrada de dados? Arquivo (A) ou Terminal (T):\n");
    scanf("%s", &tipo_da_entrada);

    if (tipo_da_entrada == 'T') {
        printf("Entre com o numero do teste:\n");
         scanf("%d", &num_teste);
        printf("Entre com o tamanho do vetor:\n");
        scanf("%d", &tam_vetor);
        printf("Qual operacao sera feita: Insercao (0)| Remocao (1)\n");
        scanf("%d", &tipo_de_operacao);
        printf("Quantas vezes a operacao sera feita:\n");
        scanf("%d", &qntd_de_operacao);
        opera_lista(tam_vetor, tipo_de_operacao, qntd_de_operacao, num_teste);
    } else if (tipo_da_entrada == 'A'){
        printf("Entre com o nome do arquivo:\n");
        scanf("%s", nome_arquivo);

        FILE *fileptr;
        fileptr = fopen(nome_arquivo, "r");

        fscanf(fileptr, "%d", &tam_vetor);
        fscanf(fileptr, "%d", &qntd_linhas);

        for (int i = 0; i < qntd_linhas; ++i) {
            fscanf(fileptr, "%d %d", &tipo_de_operacao, &qntd_de_operacao);
            opera_lista(tam_vetor, tipo_de_operacao, qntd_de_operacao, i+1);
        }

        fclose(fileptr);

    } 
    else {
        printf("ERRO: Entrada invalida!");
    }

    return 0;
}


void opera_lista(int tam_vetor, int tipo_de_operacao, int qntd_de_operacao, int num_teste) {

    clock_t tempo_inicial = clock();

    lista_processo *lista_teste;
    lista_teste = (lista_processo*) malloc(sizeof(lista_processo));
    cria_lista(lista_teste, tam_vetor);

    if (tipo_de_operacao == 0) { 
        for (int i = 0; i < qntd_de_operacao-1; ++i) {
            tipo_processo *processo_teste;
            processo_teste = initprocesso();
            insere_ordenado(lista_teste, *processo_teste);
        }
        imprime_lista(lista_teste);
    }
    else if (tipo_de_operacao == 1) {
            for (int i = 0; i < qntd_de_operacao-1; ++i) {
            retira_primeiro(lista_teste);
        } 
    }
        else {
            printf("ERRO: Operacao invalida!");
        }


    clock_t tempo_final = clock();
    double tempo_diferenca = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;

    printf("Teste %d: %lf segundos\n\n", num_teste, tempo_diferenca);
}
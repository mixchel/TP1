#include <stdio.h>
#include <stdlib.h>
#include "tipo_processo.h"

//Ver limite de representação de inteiro
typedef int cursor;

typedef struct {
    tipo_processo processo;
    cursor anterior;
    cursor proximo;
} tipo_celula;

typedef struct tipo_lista_processo {
    cursor primeiro;
    cursor ultimo;
    cursor prim_cel_disp;
    int num_cel_ocupadas;
    int num_cel_vazias;
    tipo_celula *vetor;
} lista_processo;

int verifica_vazia(lista_processo *lista);

int verifica_cheia(lista_processo *lista);

int cel_ocupadas(lista_processo *lista);

void cria_lista(lista_processo *lista, int n_max);

void insere_inicio(lista_processo *lista, tipo_processo processo);

void insere_meio(lista_processo *lista, tipo_processo processo, cursor indice);

void insere_final(lista_processo *lista, tipo_processo processo);

void insere_ordenado(lista_processo *lista, tipo_processo proceso);

void retira_primeiro(lista_processo *lista);

void imprime_lista(lista_processo *lista);

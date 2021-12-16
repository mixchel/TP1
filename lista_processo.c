#include "lista_processo.h"

int verifica_vazia(lista_processo *lista){
    if (lista->num_cel_ocupadas == 0) {
        return 1;
    }
    else{
        return 0;
    }
}

int verifica_cheia(lista_processo *lista){
    if (lista->num_cel_ocupadas == sizeof(lista->vetor)/(sizeof(lista->vetor[0]))){
    // if (lista->num_cel_vazias == 0) {
        return 1;
    }
    else{
        return 0;
    }
}

void cria_lista(lista_processo *lista, int n_max){
    //Seta valores da lista
    lista->primeiro = -1;
    lista->ultimo = -1;
    lista->num_cel_ocupadas = 0;
    lista->num_cel_vazias = n_max;
    lista->prim_cel_disp = 0;
    lista->vetor = (tipo_celula*) malloc(n_max*sizeof(tipo_celula));

    //Seta valores das celulas iniciais
    for (int i = 0; i < n_max; i++) {
        //Seta prox de todas as celulas vazias
        lista->vetor[i].anterior = -1;
        lista->vetor[i].proximo = i+1;

        if (i == 0) {
            lista->vetor[i].anterior = -1;                                  //Seta -1 no "anterior" da primeira vazia
            }  else if(i == n_max-1) {
                lista->vetor[i].proximo = -1;
        }   
    }
}

void insere_inicio(lista_processo *lista, tipo_processo processo){
    cursor aux;
    aux = lista->prim_cel_disp;                                             // guarda o indce da primeira cel. disp
    lista->prim_cel_disp = lista->vetor[lista->prim_cel_disp].proximo;      // muda o cursor da primeira cel. disp 

    if (verifica_vazia(lista)) {                                            //Pode ser trocado por checa vazia
        lista->ultimo = aux;                                                // aponta o "ultimo" quando primeira celula também é a ultima
    } else {
        lista->vetor[lista->primeiro].anterior = aux;                       // aponta o anterior da antiga primeira cel. para nova primeira cel.
    }
    lista->vetor[aux].proximo = lista->primeiro;                            // aponta o proximo da nova proxima para a antiga primeira
    lista->primeiro = aux;                                                  // "primeiro" aponta pra nova primeira celula

    lista->vetor[lista->primeiro].processo = processo;                      // primeira celula recebe o valor do parametro processo
    lista->num_cel_ocupadas++;                                              // numero de celulas ocupadas aumenta em 1
    lista->num_cel_vazias--;                                                // numero de celulas disponiveis diminui em 1
}

void insere_meio(lista_processo *lista, tipo_processo processo, cursor indice){
    cursor aux;
    aux = lista->prim_cel_disp;                                             // guarda o indce da primeira cel. disp
    lista->prim_cel_disp = lista->vetor[lista->prim_cel_disp].proximo;      // muda o cursor da primeira cel. disp 

    lista->vetor[aux].anterior = lista->vetor[indice].anterior;             // anterior da nova celula aponta para aterior da proxima celula
    lista->vetor[aux].proximo = indice;                                     // proximo da nova celula aponta para a proxima
    lista->vetor[lista->vetor[aux].anterior].proximo = aux;                 // "proximo" da anterior aponta para a nova celula
    lista->vetor[indice].anterior = aux;                                    // "anterior" da proxima aponta para a nova celula

    lista->vetor[aux].processo = processo;                                  // primeira celula recebe o valor do parametro processo
    lista->num_cel_ocupadas++;                                              // numero de celulas ocupadas aumenta em 1
    lista->num_cel_vazias--;                                                // numero de celulas disponiveis diminui em 1
}

void insere_final(lista_processo *lista, tipo_processo processo){
    cursor aux;
    aux = lista->prim_cel_disp;                                             // guarda o indce da primeira cel. disp
    lista->prim_cel_disp = lista->vetor[lista->prim_cel_disp].proximo;      // muda o cursor da primeira cel. disp 


    lista->vetor[aux].anterior = lista->ultimo;                             // anterior da nova celula aponta pra antiga ultima
    lista->vetor[lista->ultimo].proximo = aux;                              // atiga ultima celula aponta pra nova celula
    lista->ultimo = aux;                                                    // "ultimo" aponta pra nova celula
    lista->vetor[lista->ultimo].proximo = -1;                               // "proximo" da nova celula
    
    lista->vetor[lista->ultimo].processo = processo;                        // nova celula recebe o valor do parametro processo
    lista->num_cel_ocupadas++;                                              // numero de celulas ocupadas aumenta em 1
    lista->num_cel_vazias--;                                                // numero de celulas disponiveis diminui em 1
}

void insere_ordenado(lista_processo *lista, tipo_processo proceso){

    if (verifica_vazia(lista)) {
        insere_inicio(lista, proceso);
        } if (verifica_cheia(lista)){
                printf("ERRO: operacao nao permitida!\nLista cheia\n\n");
            }else {
        cursor indice_atual, prox_indice;
        indice_atual = lista->primeiro;

        if (proceso.PID < lista->vetor[indice_atual].processo.PID){
            insere_inicio(lista, proceso);
        } else { 
            prox_indice = lista->vetor[indice_atual].proximo;
            while (lista->vetor[prox_indice].processo.PID < proceso.PID && prox_indice != -1) {
                prox_indice = lista->vetor[prox_indice].proximo;
            }
            if (prox_indice == -1){
                insere_final(lista, proceso);
            } else{
                insere_meio(lista, proceso, prox_indice);
            }
        }
    }  
}

void retira_primeiro(lista_processo *lista){
    cursor aux;
    
    if (verifica_vazia(lista) == 1){
        printf("ERRO: opercao nao permitida!\nLista vazia\n\n");
    }
    else{
        // Temos que fazer o proximo da primeira celula como a variavel auxiliar, e o anterior deste ser a nova primeira celula disponivel
        // preenche -1 no "anterior" da celula que se torná a primeira 
        aux = lista->vetor[lista->primeiro].proximo;                        // aux recebe o indice da nova primeira celula
        lista->vetor[lista->primeiro].proximo = lista->prim_cel_disp;       // antiga primeira cel. aponta para a primeira cel. disp.
        lista->prim_cel_disp = lista->primeiro;                             // primeira cel. disp. aponta para a antiga primeira celula
        lista->primeiro = aux;                                              // primeiro agora aponta para aux 
        
        if (lista->num_cel_ocupadas==1){                                    // verifica se a operação vai ser feita na ultima celula
            lista->ultimo = -1;                                             // preenche -1 em ultimo
        }else{
            lista->vetor[lista->primeiro].anterior = -1;                    // preenche -1 no "anterior" da celula que se torná a primeira 
        }

        lista->num_cel_ocupadas--;                                          // numero de celulas ocupadas diminui em 1
        lista->num_cel_vazias++;                                            // numero de celulas disponiveis aumenta em 1
    }
}

void imprime_lista(lista_processo *lista){
        if (verifica_vazia(lista) == 1){
        printf("\nLista vazia!\n\n");
    } else {
        printf("\nLista de Processos ordenada:\n\n");
        cursor indice_atual;
        indice_atual = lista->primeiro;
        while (indice_atual != -1) {
            printprocesso(&(lista->vetor[indice_atual].processo));
            indice_atual = lista->vetor[indice_atual].proximo;
        }
    }
}

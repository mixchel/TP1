#include "tipo_processo.h"

void settime(tipo_processo *ptr) {
    time(&ptr->tempo); // armazena o tempo em segundos desde 1970
}
char* gettime(tipo_processo *ptr){
    char *str;
    str = (char *)malloc(sizeof(char)*28);
    snprintf(str, 28, "%s", asctime(localtime(&ptr->tempo))); //armazena o valor de uma string com a data em str
    return str;
}
void setprioridade(tipo_processo *ptr) {
    ptr->prioridade = (rand() % 5) + 1;
    //prioridade gerada aleatoriamente de 1 a 5
}
int getprioridade(tipo_processo *ptr){
    return ptr->prioridade;
}
void setPID(tipo_processo *ptr) {
    ptr->PID = rand() * ((rand() % 100) + 1) ;
    //PID gerado aleatoriamente
}
int getPID(tipo_processo *ptr){
    return ptr->PID;
}

void printprocesso(tipo_processo *ptr){
    printf("PID: %d\nData: %sPrioridade: %d\n\n", getPID(ptr), gettime(ptr), getprioridade(ptr));
}

struct tipo_processo * initprocesso(){
    //Função para iniciar um tipo_processo aloca e seta os valores
    tipo_processo *ptr;
    ptr = (tipo_processo *) malloc(sizeof(tipo_processo));
    settime(ptr);
    setPID(ptr);
    setprioridade(ptr);
    return ptr;
}

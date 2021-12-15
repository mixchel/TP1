#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct tipo_processo {
    int prioridade;
    int PID;
    time_t tempo; // dado do tipo time_t que é definido em time.h
} tipo_processo;

void settime(tipo_processo *ptr);

char* gettime(tipo_processo *ptr);

void setprioridade(tipo_processo *ptr);

int getprioridade(tipo_processo *ptr);

void setPID(tipo_processo *ptr);

int getPID(tipo_processo *ptr);

void printprocesso(tipo_processo *ptr);

struct tipo_processo * initprocesso();


#ifndef ELEITOR_H
#define ELEITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pessoa.h"

typedef struct {
    TPessoa base;
    int codigo;
    char titulo_eleitor[15];
    char secao[5];
    char zona[5];
} TEleitor;

TEleitor *eleitor(int codigo, char *nome, char *cpf, char *data_nascimento, char *titulo, char *secao, char* zona);

void salvaEleitor(TEleitor *eleitor, FILE *out);

int tamanho_arquivo_eleitor(FILE *arq);

TEleitor *leEleitor(FILE *in);

void imprimeEleitor(TEleitor *eleitor);

int tamanho_registro_eleitor();

void criarBaseEleitor(FILE *out, int tam);

void embaralhaEleitor(int *vet, int tam);

void imprimirBaseEleitor(FILE *out);

#endif // ELEITOR_H
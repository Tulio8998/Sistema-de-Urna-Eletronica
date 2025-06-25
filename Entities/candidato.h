#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pessoa.h"

typedef struct {
    int codigo;
    TPessoa base;
    char cargo[50];
    char partido[50];
} TCandidato;


TCandidato *candidato(int codigo, char *nome, char *cpf, char *data_nascimento, char *cargo, char *partido);

void salvaCandidato(TCandidato *cand, FILE *out);

int tamanho_arquivo_candidato(FILE *arq);

TCandidato *leCandidato(FILE *in);

void imprimeCandidato(TCandidato *cand);

int tamanho_registro_candidato();

void shuffleCandidato(int *vet,int MAX,int MIN);

void criarBaseCandidato(FILE *out, int tam);

void imprimirBaseCandidato(FILE *out);

#endif // CANDIDATO_H
#ifndef PESSOA_H_INCLUDED
#define PESSOA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct Pessoa {
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
} TPessoa;

int calcularIdade(char *data_nascimento);

int ehMaiorIdade(char *data_nascimento);

#endif // PESSOA_H_INCLUDED
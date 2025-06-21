#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pessoa.h"

typedef struct {
    TPessoa base;
    int codigo;
    bool verificacao;
} TAdm;

TAdm *administrador(int codigo, char *nome, char *cpf, char *data_nascimento, bool verificacao);

void salvaAdministrador(TAdm *adm, FILE *out);

int tamanho_arquivo_administrador(FILE *arq);

TAdm *leAdministrador(FILE *in);

// Imprime funcionario
void imprimeAdministrador(TAdm *adm);

// Criar a base de dados
void criarBaseAdministrador(FILE *out, int tam);

// Embaralha a base de dados
void shuffleAdministrador(int *vet,int MAX,int MIN);

void imprimirBaseAdministrador(FILE *out);

int tamanho_registro_administrador();

#endif // ADMINISTRADOR_H_INCLUDED

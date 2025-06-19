#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pessoa.h"

typedef struct {
    TPessoa base;
    int codigo;
    char cargo[50];
    char partido[50];
} TCandidato;

#endif // CANDIDATO_H_INCLUDED

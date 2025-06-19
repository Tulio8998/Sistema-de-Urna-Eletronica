#ifndef CANDIDATO_H
#define CANDIDATO_H

#include "pessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    TPessoa base;
    int codigo;
    bool verificacao;
} TCandidato;

#endif // CANDIDATO_H_INCLUDED

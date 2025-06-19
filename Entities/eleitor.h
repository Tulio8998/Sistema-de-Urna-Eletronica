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

#endif // ELEITOR_H_INCLUDED

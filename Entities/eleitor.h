#ifndef ELEITOR_H
#define ELEITOR_H

#include "pessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    TPessoa base;
    int codigo;
} TEleitor;

#endif // ELEITOR_H_INCLUDED

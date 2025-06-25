#ifndef QUICKSORT_DISCO_H
#define QUICKSORT_DISCO_H

#include <stdio.h>
#include "../Entities/administrador.h"
#include "../Entities/candidato.h"
#include "../Entities/eleitor.h"

void quickSortEmDiscoAdministrador(FILE *arq);

void quickSortEmDiscoCandidato(FILE *arq);

void quickSortEmDiscoEleitor(FILE *arq);

#endif // QUICKSORT_DISCO_H
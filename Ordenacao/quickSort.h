#ifndef QUICKSORT_H_INCLUDED
#define QUICKSORT_H_INCLUDED
#include "../Entities/administrador.h"
#include "../Entities/candidato.h"
#include "../Entities/eleitor.h"

void quickSortAdministrador(TAdm **vetor, int p, int r);
void quickSortCandidato(TCandidato **vetor, int p, int r);
void quickSortEleitor(TEleitor **vetor, int p, int r);

#endif // QUICKSORT_H_INCLUDED
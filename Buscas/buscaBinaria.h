#ifndef BUSCABINARIA_H_INCLUDED
#define BUSCABINARIA_H_INCLUDED
#include "../Entities/administrador.h"
#include "../Entities/candidato.h"
#include "../Entities/eleitor.h"

TAdm *buscaBinariaAdministrador(int chave, FILE *in, int inicio, int fim);

TCandidato *buscaBinariaCandidato(int chave, FILE *in, int inicio, int fim);

TEleitor *buscaBinariaEleitor(int chave, FILE *in, int inicio, int fim);

#endif // BUSCABINARIA_H_INCLUDEDT
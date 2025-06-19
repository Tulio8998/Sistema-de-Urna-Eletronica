#include "../Entities/administrador.h"
#include "../Entities/candidato.h"
#include "../Entities/eleitor.h"
#ifndef BUSCABINARIA_H_INCLUDED
#define BUSCABINARIA_H_INCLUDED


//Realiza uma busca BINARIA por um funcionario na base de dados

TAdm *buscaBinariaAdministrador(int chave, FILE *in, int inicio, int fim, FILE *log);

TCandidato *buscaBinariaCandidato(int chave, FILE *in, int inicio, int fim, FILE *log);

TEleitor *buscaBinariaEleitor(int chave, FILE *in, int inicio, int fim, FILE *log);

#endif // BUSCABINARIA_H_INCLUDEDT
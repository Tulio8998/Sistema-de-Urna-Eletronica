#ifndef BUSCASEQUENCIAL_H_INCLUDED
#define BUSCASEQUENCIAL_H_INCLUDED
#include "../Entities/administrador.h"
#include "../Entities/candidato.h"
#include "../Entities/eleitor.h"

TAdm *buscaSequencialAdministrador(int chave, FILE *in);

TCandidato *buscaSequencialCandidato(int chave, FILE *in);

TEleitor *buscaSequencialEleitor(int chave, FILE *in);


#endif // BUSCASEQUENCIAL_H_INCLUDED
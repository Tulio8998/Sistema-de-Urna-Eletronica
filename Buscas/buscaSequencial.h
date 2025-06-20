#ifndef BUSCASEQUENCIAL_H_INCLUDED
#define BUSCASEQUENCIAL_H_INCLUDED
#include "../Entities/administrador.h"
#include "../Entities/candidato.h"
#include "../Entities/eleitor.h"


//Realiza uma busca sequencial por um funcionario na base de dados

TAdm *buscaSequencialAdministrador(int chave, FILE *in, FILE *log);

TCandidato *buscaSequencialCandidato(int chave, FILE *in, FILE *log);

TEleitor *buscaSequencialEleitor(int chave, FILE *in, FILE *log);


#endif // BUSCASEQUENCIAL_H_INCLUDED
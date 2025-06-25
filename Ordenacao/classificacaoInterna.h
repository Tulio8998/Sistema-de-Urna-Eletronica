#ifndef CLASSIFICACAOINTERNA_H_INCLUDED
#define CLASSIFICACAOINTERNA_H_INCLUDED
#include "../Entities/administrador.h"
#include "../Entities/candidato.h"
#include "../Entities/eleitor.h"

int classificacaoInternaAdministrador(FILE *arq, int M);

int classificacaoInternaCandidato(FILE *arq, int M);

int classificacaoInternaEleitor(FILE *arq, int M);

#endif // CLASSIFICACAOINTERNA_H_INCLUDED
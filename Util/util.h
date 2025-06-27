#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Entities/administrador.h"
#include "../Entities/candidato.h"
#include "../Entities/eleitor.h"

void init_random(void);

void gerarNome(char *dest, size_t size);

void gerarCargo(char *dest, size_t size);

void gerarPartido(char *dest, size_t size);

TCandidato generateRandomUserCand(int condigo);

TEleitor generateRandomUserElei(int condigo);

void gerarCPF(char *cpf);

void gerarData(char *data);

void gerarSecao(char *secao);

void gerarZona(char *zona);

void gerarTitulo(char *titulo);

#endif // UTIL_H
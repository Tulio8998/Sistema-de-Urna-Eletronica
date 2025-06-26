#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Entities/administrador.h"
#include "../Entities/candidato.h"
#include "../Entities/eleitor.h"

// Função para inicializar o gerador de números aleatórios
void init_random(void);

// Geração de nome aleatório (primeiro e último)
void gerarNome(char *dest, size_t size);

// Geração de cargo aleatório com pesos
void gerarCargo(char *dest, size_t size);

// Geração de partido aleatório
void gerarPartido(char *dest, size_t size);

// Gera um candidato aleatório
TCandidato generateRandomUserCand(int condigo);

TEleitor generateRandomUserElei(int condigo);

void gerarCPF(char *cpf);

void gerarData(char *data);

void gerarSecao(char *secao);

void gerarZona(char *zona);

void gerarTitulo(char *titulo);

#endif // UTIL_H
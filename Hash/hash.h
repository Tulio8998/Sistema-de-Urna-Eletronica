#ifndef HASH_H
#define HASH_H

#include "../Entities/candidato.h"

#define TAMANHO_TABELA 101

typedef struct No {
    TCandidato *candidato;
    struct No *proximo;
} TNo;

extern TNo *tabela_hash_candidatos[TAMANHO_TABELA];

int funcao_hash_candidato(int codigo);

void inicializar_tabela_hash_candidatos();

void inserir_candidato_hash(TCandidato *candidato);

TCandidato* buscar_candidato_hash(int codigo);

int remover_candidato_hash(int codigo);

void carregar_candidatos_para_hash();

void liberar_tabela_hash_candidatos();

void imprimir_tabela_hash_candidatos();

#endif // HASH_H
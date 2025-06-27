#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pessoa.h"
#include "eleitor.h"
#include "candidato.h"

typedef struct {
    int codigo;
    TPessoa base;
    bool verificacao;
} TAdm;

TAdm *administrador(int codigo, char *nome, char *cpf, char *data_nascimento, bool verificacao);

void inicializar_adm_padrao();

void salvaAdministrador(TAdm *adm, FILE *out);

int tamanho_arquivo_administrador(FILE *arq);

TAdm *leAdministrador(FILE *in);

void imprimeAdministrador(TAdm *adm);

void criarBaseAdministrador(FILE *out, int tam);

void shuffleAdministrador(int *vet,int MAX,int MIN);

void imprimirBaseAdministrador(FILE *out);

int tamanho_registro_administrador();

TAdm* autenticar_administrador(int codigo);

void adicionar_eleitor(TEleitor *novo_elei);

int editar_eleitor(int codigo_editar, TEleitor *dados_novos);

void remover_eleitor(int codigo_remover);

void adicionar_administrador(TAdm *novo_adm);

int editar_administrador(int codigo_edita, TAdm *dados_novos);

void remover_administrador(int codigo_adm_log, int codigo_remover);

void adicionar_candidato(TCandidato *novo_cand);

int editar_candidato(int codigo_editar, TCandidato *dados_novos);

void remover_candidato(int codigo_remover);

void relatorio_votos();


#endif // ADMINISTRADOR_H_INCLUDED

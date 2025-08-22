#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

TNo *tabela_hash_candidatos[TAMANHO_TABELA];

int funcao_hash_candidato(int codigo) {
    return codigo % TAMANHO_TABELA;
}

void inicializar_tabela_hash_candidatos() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela_hash_candidatos[i] = NULL;
    }
}

void inserir_candidato_hash(TCandidato *candidato) {
    int indice = funcao_hash_candidato(candidato->codigo);
    TNo *novo_no = (TNo *) malloc(sizeof(TNo));
    if (!novo_no) {
        perror("Erro ao alocar memoria para novo no da hash de candidatos");
        return;
    }
    novo_no->candidato = candidato;
    novo_no->proximo = tabela_hash_candidatos[indice];
    tabela_hash_candidatos[indice] = novo_no;
}

TCandidato* buscar_candidato_hash(int codigo) {
    int indice = funcao_hash_candidato(codigo);
    TNo *atual = tabela_hash_candidatos[indice];
    while (atual != NULL) {
        if (atual->candidato->codigo == codigo) {
            return atual->candidato;
        }
        atual = atual->proximo;
    }
    return NULL;
}

int remover_candidato_hash(int codigo) {
    int indice = funcao_hash_candidato(codigo);
    TNo *atual = tabela_hash_candidatos[indice];
    TNo *anterior = NULL;

    while (atual != NULL && atual->candidato->codigo != codigo) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return 0; 

    if (anterior == NULL) {
        tabela_hash_candidatos[indice] = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual->candidato);
    free(atual);
    return 1;
}

void carregar_candidatos_para_hash() {
    FILE *arq = fopen("Data/candidatos.dat", "rb");
    if (arq == NULL) return;

    TCandidato *cand_lido;
    while ((cand_lido = leCandidato(arq)) != NULL) {
        inserir_candidato_hash(cand_lido);
    }
    fclose(arq);
}

void liberar_tabela_hash_candidatos() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        TNo *atual = tabela_hash_candidatos[i];
        while (atual != NULL) {
            TNo *temp = atual;
            atual = atual->proximo;
            free(temp->candidato);
            free(temp);
        }
    }
}

void imprimir_tabela_hash_candidatos() {
    printf("\n--- CONTEUDO DA TABELA HASH DE CANDIDATOS ---\n");
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        printf("Indice [%d]: ", i);
        TNo* atual = tabela_hash_candidatos[i];
        if (atual == NULL) {
            printf("Vazio\n");
        } else {
            while(atual != NULL) {
                printf("[Cod: %d, Nome: %s] -> ", atual->candidato->codigo, atual->candidato->base.nome);
                atual = atual->proximo;
            }
            printf("NULL\n");
        }
    }
    printf("---------------------------------------------\n");
}
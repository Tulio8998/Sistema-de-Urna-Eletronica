#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

// Definição da tabela hash
No* tabela[TAM];

// Função hash simples (resto da divisão)
int hash(int chave) {
    return chave % TAM;
}

void inicializarTabela() {
    for (int i = 0; i < TAM; i++) {
        tabela[i] = NULL;
    }
}

void inserir(int chave, char* valor) {
    int indice = hash(chave);

    // Criar novo nó
    No* novo = (No*) malloc(sizeof(No));
    novo->chave = chave;
    strcpy(novo->valor, valor);
    novo->prox = NULL;

    // Inserir no início da lista
    if (tabela[indice] == NULL) {
        tabela[indice] = novo;
    } else {
        novo->prox = tabela[indice];
        tabela[indice] = novo;
    }

    printf("Inserido: (%d, %s) na posição %d\n", chave, valor, indice);
}

char* buscar(int chave) {
    int indice = hash(chave);
    No* atual = tabela[indice];

    while (atual != NULL) {
        if (atual->chave == chave) {
            return atual->valor;
        }
        atual = atual->prox;
    }
    return NULL; // não encontrado
}

int remover(int chave) {
    int indice = hash(chave);
    No* atual = tabela[indice];
    No* anterior = NULL;

    while (atual != NULL) {
        if (atual->chave == chave) {
            if (anterior == NULL) {
                tabela[indice] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Removido: %d da posição %d\n", chave, indice);
            return 1; // removido com sucesso
        }
        anterior = atual;
        atual = atual->prox;
    }
    return 0; // não encontrado
}

// ===============================
// IMPRIMIR TABELA HASH
// ===============================
void imprimirTabela() {
    printf("\n--- Tabela Hash ---\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d: ", i);
        No* atual = tabela[i];
        while (atual != NULL) {
            printf(" -> (%d, %s)", atual->chave, atual->valor);
            atual = atual->prox;
        }
        printf("\n");
    }
}

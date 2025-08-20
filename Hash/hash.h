#ifndef HASH_H
#define HASH_H

#define TAM 10   // tamanho da tabela hash

// Estrutura do nó da lista (para tratar colisões)
typedef struct No {
    int chave;
    char valor[50];
    struct No* prox;
} No;

// Variável global da tabela hash
extern No* tabela[TAM];

// Funções
int hash(int chave);
void inserir(int chave, char* valor);
char* buscar(int chave);
int remover(int chave);
void imprimirTabela();
void inicializarTabela();

#endif

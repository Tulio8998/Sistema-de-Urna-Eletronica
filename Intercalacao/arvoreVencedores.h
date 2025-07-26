#ifndef ARVORE_VENCEDORES_H
#define ARVORE_VENCEDORES_H

#include "../Entities/candidato.h"

// Estrutura da célula (nó) da árvore de vencedores
typedef struct celula {
    TCandidato *candidato;       // Candidato armazenado no nó
    struct celula *esq, *dir;    // Filhos da árvore
    int indiceParticao;          // Índice da partição de onde o candidato veio
} TCel;

// Função principal: faz a intercalação final dos candidatos usando árvore de vencedores
void intercalarArquivo();

// Funções auxiliares usadas internamente (opcional exportar dependendo do uso)
TCel* criarFolha(TCandidato *candidato, int indice);
TCel* criarInterTCel(TCel *esq, TCel *dir);
TCel* construirArvore(TCel **folhas, int n);
void atualizarArvore(TCel *raiz, int indice, TCandidato *novo);

#endif // ARVORE_VENCEDORES_H
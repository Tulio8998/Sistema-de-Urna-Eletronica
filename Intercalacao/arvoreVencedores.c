#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include "../Entities/candidato.h"
#define MAX_PARTICOES 15000
long long int comparacoes_arvore = 0;
long long int leituras_arvore = 0;
long long int escritas_arvore = 0;
int particoes_geradas = 0;

typedef struct celula {
    TCandidato *candidato;
    struct celula *esq, *dir;
    int indiceParticao;
} TCel;

TCel* criarFolha(TCandidato *candidato, int indice) {
    TCel *nova = (TCel *)malloc(sizeof(TCel));
    nova->candidato = candidato;
    nova->esq = nova->dir = NULL;
    nova->indiceParticao = indice;
    return nova;
}

TCel* criarInterTCel(TCel *esq, TCel *dir) {
    TCel *nova = (TCel *)malloc(sizeof(TCel));
    nova->esq = esq;
    nova->dir = dir;
    comparacoes_arvore++;
    nova->indiceParticao = (esq->candidato->codigo <= dir->candidato->codigo) ? esq->indiceParticao : dir->indiceParticao;
    nova->candidato = (esq->candidato->codigo <= dir->candidato->codigo) ? esq->candidato : dir->candidato;
    return nova;
}

TCel* construirArvore(TCel **folhas, int n) {
    while (n > 1) {
        int k = 0;
        for (int i = 0; i < n; i += 2) {
            if (i + 1 < n) {
                folhas[k++] = criarInterTCel(folhas[i], folhas[i + 1]);
            } else {
                folhas[k++] = folhas[i];
            }
        }
        n = k;
    }
    return folhas[0];
}

void liberarArvore(TCel *raiz) {
    if (raiz) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

void atualizarArvore(TCel *raiz, int indice, TCandidato *novo) {
    if (!raiz) return;
    
    if (!raiz->esq && !raiz->dir) {
        if (raiz->indiceParticao == indice) {
            raiz->candidato = novo;
        }
        return;
    }
    
    atualizarArvore(raiz->esq, indice, novo);
    atualizarArvore(raiz->dir, indice, novo);

    if (raiz->esq && raiz->dir) {
        if (raiz->esq->candidato == NULL) {
            raiz->candidato = raiz->dir->candidato;
            raiz->indiceParticao = raiz->dir->indiceParticao;
        } else if (raiz->dir->candidato == NULL) {
            raiz->candidato = raiz->esq->candidato;
            raiz->indiceParticao = raiz->esq->indiceParticao;
        } else {
            if (raiz->esq->candidato->codigo <= raiz->dir->candidato->codigo) {
                raiz->candidato = raiz->esq->candidato;
                raiz->indiceParticao = raiz->esq->indiceParticao;
            } else {
                raiz->candidato = raiz->dir->candidato;
                raiz->indiceParticao = raiz->dir->indiceParticao;
            }
        }
    }
}

int buscarParticoes(char nomes[][100]) {
    DIR *d;
    struct dirent *dir;
    int count = 0;

    d = opendir("./Data/Particoes/");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strstr(dir->d_name, "particao_") && strstr(dir->d_name, ".dat")) {
                strcpy(nomes[count++], dir->d_name);
            }
        }
        closedir(d);
    }
    return count;
}

void intercalarArquivo() {
    comparacoes_arvore = 0;
    leituras_arvore = 0;
    escritas_arvore = 0;
    particoes_geradas = 0;

    char nomes[MAX_PARTICOES][100];
    FILE *particoes[MAX_PARTICOES];
    TCel *folhas[MAX_PARTICOES];
    int totalParticoes = buscarParticoes(nomes);
    particoes_geradas = totalParticoes;

    if (totalParticoes == 0) {
        printf(" Nenhuma partição encontrada em ./Data/Particoes/\n");
        return;
    }

    for (int i = 0; i < totalParticoes; i++) {
        char path[150];
        snprintf(path, sizeof(path), "./Data/Particoes/%s", nomes[i]);
        particoes[i] = fopen(path, "rb");
        if (!particoes[i]) {
            printf("Erro ao abrir partição %s\n", path);
            exit(1);
        }

        TCandidato *cand = leCandidato(particoes[i]);
        leituras_arvore++;
        folhas[i] = criarFolha(cand, i);
    }

    TCel *raiz = construirArvore(folhas, totalParticoes);

    FILE *saida = fopen("./Data/saida.dat", "wb");
    if (!saida) {
        printf("Erro ao criar arquivo de saída.\n");
        exit(1);
    }

    int contador = 1;
    while (raiz != NULL && raiz->candidato != NULL) {
        salvaCandidato(raiz->candidato, saida);
        escritas_arvore++;

        int idx = raiz->indiceParticao;
        TCandidato *proximo = leCandidato(particoes[idx]);
        leituras_arvore++;

        if (proximo == NULL) {
            atualizarArvore(raiz, idx, NULL);
        } else {
            atualizarArvore(raiz, idx, proximo);
        }

        if (raiz->candidato == NULL) {
            liberarArvore(raiz);
            raiz = NULL;
        }
    }

    for (int i = 0; i < totalParticoes; i++) {
        fclose(particoes[i]);
    }
    fclose(saida);
    
}
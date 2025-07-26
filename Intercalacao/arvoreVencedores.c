#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../Entities/candidato.h"

#define MAX_PARTICOES 100

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
    nova->indiceParticao = (esq->candidato->voto <= dir->candidato->voto) ? esq->indiceParticao : dir->indiceParticao;
    nova->candidato = (esq->candidato->voto <= dir->candidato->voto) ? esq->candidato : dir->candidato;
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
            if (raiz->esq->candidato->voto <= raiz->dir->candidato->voto) {
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
    char nomes[MAX_PARTICOES][100];
    FILE *particoes[MAX_PARTICOES];
    TCel *folhas[MAX_PARTICOES];
    int totalParticoes = buscarParticoes(nomes);

    if (totalParticoes == 0) {
        printf(" Nenhuma partição encontrada em ./Data/Particoes/\n");
        return;
    }

    printf("\n Iniciando intercalação com árvore de vencedores...\n\n");

    for (int i = 0; i < totalParticoes; i++) {
        char path[150];
        snprintf(path, sizeof(path), "./Data/Particoes/%s", nomes[i]);
        particoes[i] = fopen(path, "rb");
        if (!particoes[i]) {
            printf("Erro ao abrir partição %s\n", path);
            exit(1);
        }

        TCandidato *cand = leCandidato(particoes[i]);
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
        printf("%3d. Código: %d | Nome: %-20s | Cargo: %-12s | Partido: %-5s | Votos: %d\n",
               contador++,
               raiz->candidato->codigo,
               raiz->candidato->base.nome,
               raiz->candidato->cargo,
               raiz->candidato->partido,
               raiz->candidato->voto);

        salvaCandidato(raiz->candidato, saida);

        int idx = raiz->indiceParticao;
        TCandidato *proximo = leCandidato(particoes[idx]);
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

    printf("\n Intercalação concluída. Arquivo final disponível em: ./Data/saida.dat\n\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "classificacaoInterna.h"
#include "quickSort.h"

int classificacaoInternaAdministrador(FILE *arq, int M) {
    int nAdm = tamanho_arquivo_administrador(arq);
    rewind(arq);
    int reg = 0;
    int qtdParticoes = 0;
    
    char nomeParticao[40]; 

    TAdm **v = (TAdm **) malloc(sizeof(TAdm*) * M);
    if (v == NULL) return -1;

    while (reg < nAdm) {
        int i = 0;
        
        while (i < M && reg < nAdm) {
            v[i] = leAdministrador(arq);
            if (v[i] == NULL) break;
            i++;
            reg++;
        }
        int registros_lidos = i;

        quickSortAdministrador(v, 0, registros_lidos - 1);

        sprintf(nomeParticao, "Ordenacao/Particoes/particao_adm_%d.dat", qtdParticoes);
        
        FILE *p = fopen(nomeParticao, "wb");
        if (p != NULL) {
            for (i = 0; i < registros_lidos; i++) {
                
                salvaAdministrador(v[i], p);
                free(v[i]);
            }
            fclose(p);
            qtdParticoes++;
        }
    }
    free(v);
    return qtdParticoes;
}


int classificacaoInternaCandidato(FILE *arq, int M) {
    int nCand = tamanho_arquivo_candidato(arq);
    rewind(arq);
    int reg = 0;
    int qtdParticoes = 0;
    char nomeParticao[40];

    TCandidato **v = (TCandidato **) malloc(sizeof(TCandidato*) * M);
    if (v == NULL) return -1;

    while (reg < nCand) {
        int i = 0;
        while (i < M && reg < nCand) {
            v[i] = leCandidato(arq);
            if (v[i] == NULL) break;
            i++;
            reg++;
        }
        int registros_lidos = i;

        quickSortCandidato(v, 0, registros_lidos - 1);

        sprintf(nomeParticao, "Ordenacao/Particoes/particao_cand_%d.dat", qtdParticoes);
        
        FILE *p = fopen(nomeParticao, "wb");
        if (p != NULL) {
            for (i = 0; i < registros_lidos; i++) {
                salvaCandidato(v[i], p);
                free(v[i]);
            }
            fclose(p);
            qtdParticoes++;
        }
    }
    free(v);
    return qtdParticoes;
}


int classificacaoInternaEleitor(FILE *arq, int M) {
    int nEleitor = tamanho_arquivo_eleitor(arq);
    rewind(arq);
    int reg = 0;
    int qtdParticoes = 0;
    char nomeParticao[40];

    TEleitor **v = (TEleitor **) malloc(sizeof(TEleitor*) * M);
    if (v == NULL) return -1;
    
    while (reg < nEleitor) {
        int i = 0;
        while (i < M && reg < nEleitor) {
            v[i] = leEleitor(arq);
            if (v[i] == NULL) break;
            i++;
            reg++;
        }
        int registros_lidos = i;

        quickSortEleitor(v, 0, registros_lidos - 1);

        sprintf(nomeParticao, "Ordenacao/Particoes/particao_ele_%d.dat", qtdParticoes);
        
        FILE *p = fopen(nomeParticao, "wb");
        if (p != NULL) {
            for (i = 0; i < registros_lidos; i++) {
                salvaEleitor(v[i], p);
                free(v[i]);
            }
            fclose(p);
            qtdParticoes++;
        }
    }
    free(v);
    return qtdParticoes;
}
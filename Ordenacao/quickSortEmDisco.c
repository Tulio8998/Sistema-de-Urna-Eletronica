#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "quickSortEmDisco.h"

long long int comparacoes = 0;
long long  int trocas = 0; 

TAdm* leAdmPelaPosicao(FILE* in, int pos) {
    fseek(in, pos * tamanho_registro_administrador(), SEEK_SET);
    return leAdministrador(in);
}

void escreveAdmNaPosicao(FILE* out, int pos, TAdm* adm) {
    fseek(out, pos * tamanho_registro_administrador(), SEEK_SET);
    salvaAdministrador(adm, out);
}

void trocaAdmNoDisco(FILE* arq, int i, int j) {
    TAdm* adm_i = leAdmPelaPosicao(arq, i);
    TAdm* adm_j = leAdmPelaPosicao(arq, j);

    if (adm_i && adm_j) {
        escreveAdmNaPosicao(arq, i, adm_j);
        escreveAdmNaPosicao(arq, j, adm_i);
    }

    if (adm_i) free(adm_i);
    if (adm_j) free(adm_j);
}

int particionaAdmNoDisco(FILE* arq, int esq, int dir) {
    TAdm* pivo = leAdmPelaPosicao(arq, dir);
    int i = esq - 1;

    for (int j = esq; j < dir; j++) {
        TAdm* adm_j = leAdmPelaPosicao(arq, j);
        if (adm_j->codigo <= pivo->codigo) {
            i++;
            trocaAdmNoDisco(arq, i, j);
        }
        free(adm_j);
    }
    trocaAdmNoDisco(arq, i + 1, dir);
    free(pivo);
    return i + 1;
}

void quickSortRecursivoAdm(FILE* arq, int esq, int dir) {
    if (esq < dir) {
        int pivo_idx = particionaAdmNoDisco(arq, esq, dir);
        quickSortRecursivoAdm(arq, esq, pivo_idx - 1);
        quickSortRecursivoAdm(arq, pivo_idx + 1, dir);
    }
}

void quickSortEmDiscoAdministrador(FILE *arq) {
    int tam = tamanho_arquivo_administrador(arq);
    if (tam > 1) {
        quickSortRecursivoAdm(arq, 0, tam - 1);
    }
}

TCandidato* leCandPelaPosicao(FILE* in, int pos) {
    fseek(in, pos * tamanho_registro_candidato(), SEEK_SET);
    return leCandidato(in);
}

void escreveCandNaPosicao(FILE* out, int pos, TCandidato* cand) {
    fseek(out, pos * tamanho_registro_candidato(), SEEK_SET);
    salvaCandidato(cand, out);
}

void trocaCandNoDisco(FILE* arq, int i, int j) {
    TCandidato* cand_i = leCandPelaPosicao(arq, i);
    TCandidato* cand_j = leCandPelaPosicao(arq, j);
    if (cand_i && cand_j) {
        escreveCandNaPosicao(arq, i, cand_j);
        escreveCandNaPosicao(arq, j, cand_i);
    }
    if (cand_i) free(cand_i);
    if (cand_j) free(cand_j);
}

int particionaCandNoDisco(FILE* arq, int esq, int dir) {
    TCandidato* pivo = leCandPelaPosicao(arq, dir);
    int i = esq - 1;
    for (int j = esq; j < dir; j++) {
        TCandidato* cand_j = leCandPelaPosicao(arq, j);
        comparacoes++;

        if (cand_j->codigo <= pivo->codigo) {
            i++;
            trocaCandNoDisco(arq, i, j);
            trocas++;
        }
        free(cand_j);
    }
    trocaCandNoDisco(arq, i + 1, dir);
    trocas++;
    free(pivo);
    return i + 1;
}

void quickSortRecursivoCand(FILE* arq, int esq, int dir) {
    if (esq < dir) {
        int pivo_idx = particionaCandNoDisco(arq, esq, dir);
        quickSortRecursivoCand(arq, esq, pivo_idx - 1);
        quickSortRecursivoCand(arq, pivo_idx + 1, dir);
    }
}

void quickSortEmDiscoCandidato(FILE *arq, FILE *log) {
    comparacoes = 0;
    trocas = 0; 

    clock_t inicio = clock();

    int tam = tamanho_arquivo_candidato(arq);
    if (tam > 1) {
        quickSortRecursivoCand(arq, 0, tam - 1);
    }

    clock_t fim = clock(); 
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Quick Sort finalizado\n"); 
    fprintf(log, "\n--- Relatorio: Quick Sort em Disco ---\n");
    fprintf(log, "Tamanho da Base de Dados: %d registros\n", tam);
    fprintf(log, "Tempo de Execucao: %f segundos\n", tempo_gasto);
    fprintf(log, "Numero de Comparacoes entre ID's: %lld\n", comparacoes);
    fprintf(log, "Numero de Operacoes de Troca no Disco: %lld\n", trocas);
    fprintf(log, "----------------------------------------\n");

}

TEleitor* leEleitorPelaPosicao(FILE* in, int pos) {
    fseek(in, pos * tamanho_registro_eleitor(), SEEK_SET);
    return leEleitor(in);
}

void escreveEleitorNaPosicao(FILE* out, int pos, TEleitor* eleitor) {
    fseek(out, pos * tamanho_registro_eleitor(), SEEK_SET);
    salvaEleitor(eleitor, out);
}

void trocaEleitorNoDisco(FILE* arq, int i, int j) {
    TEleitor* eleitor_i = leEleitorPelaPosicao(arq, i);
    TEleitor* eleitor_j = leEleitorPelaPosicao(arq, j);
    if (eleitor_i && eleitor_j) {
        escreveEleitorNaPosicao(arq, i, eleitor_j);
        escreveEleitorNaPosicao(arq, j, eleitor_i);
    }
    if (eleitor_i) free(eleitor_i);
    if (eleitor_j) free(eleitor_j);
}

int particionaEleitorNoDisco(FILE* arq, int esq, int dir) {
    TEleitor* pivo = leEleitorPelaPosicao(arq, dir);
    int i = esq - 1;
    for (int j = esq; j < dir; j++) {
        TEleitor* eleitor_j = leEleitorPelaPosicao(arq, j);
        if (eleitor_j->codigo <= pivo->codigo) {
            i++;
            trocaEleitorNoDisco(arq, i, j);
        }
        free(eleitor_j);
    }
    trocaEleitorNoDisco(arq, i + 1, dir);
    free(pivo);
    return i + 1;
}

void quickSortRecursivoEleitor(FILE* arq, int esq, int dir) {
    if (esq < dir) {
        int pivo_idx = particionaEleitorNoDisco(arq, esq, dir);
        quickSortRecursivoEleitor(arq, esq, pivo_idx - 1);
        quickSortRecursivoEleitor(arq, pivo_idx + 1, dir);
    }
}

void quickSortEmDiscoEleitor(FILE *arq) {
    int tam = tamanho_arquivo_eleitor(arq);
    if (tam > 1) {
        quickSortRecursivoEleitor(arq, 0, tam - 1);
    }
}
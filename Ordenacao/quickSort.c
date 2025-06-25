#include <stdio.h>
#include <stdlib.h>
#include "quickSort.h"

void trocaAdm(TAdm **a, TAdm **b) { TAdm *temp = *a; *a = *b; *b = temp; }

int particionaAdm(TAdm **vetor, int p, int r) {
    int pivo_codigo = vetor[r]->codigo;
    int i = p;
    for (int j = p; j < r; j++) {
        if (vetor[j]->codigo <= pivo_codigo) {
            trocaAdm(&vetor[i], &vetor[j]);
            i++;
        }
    }
    trocaAdm(&vetor[i], &vetor[r]);
    return i;
}

void quickSortAdministrador(TAdm **vetor, int p, int r) {
    if (p < r) {
        int pivo_indice = particionaAdm(vetor, p, r);
        quickSortAdministrador(vetor, p, pivo_indice - 1);
        quickSortAdministrador(vetor, pivo_indice + 1, r);
    }
}


// --- Funções para Candidato (trabalhando com TCandidato **) ---
void trocaCand(TCandidato **a, TCandidato **b) { TCandidato *temp = *a; *a = *b; *b = temp; }

int particionaCand(TCandidato **vetor, int p, int r) {
    int pivo_codigo = vetor[r]->codigo;
    int i = p;
    for (int j = p; j < r; j++) {
        if (vetor[j]->codigo <= pivo_codigo) {
            trocaCand(&vetor[i], &vetor[j]);
            i++;
        }
    }
    trocaCand(&vetor[i], &vetor[r]);
    return i;
}

void quickSortCandidato(TCandidato **vetor, int p, int r) {
    if (p < r) {
        int pivo_indice = particionaCand(vetor, p, r);
        quickSortCandidato(vetor, p, pivo_indice - 1);
        quickSortCandidato(vetor, pivo_indice + 1, r);
    }
}


// --- Funções para Eleitor (trabalhando com TEleitor **) ---
void trocaEleitor(TEleitor **a, TEleitor **b) { TEleitor *temp = *a; *a = *b; *b = temp; }

int particionaEleitor(TEleitor **vetor, int p, int r) {
    int pivo_codigo = vetor[r]->codigo;
    int i = p;
    for (int j = p; j < r; j++) {
        if (vetor[j]->codigo <= pivo_codigo) {
            trocaEleitor(&vetor[i], &vetor[j]);
            i++;
        }
    }
    trocaEleitor(&vetor[i], &vetor[r]);
    return i;
}

void quickSortEleitor(TEleitor **vetor, int p, int r) {
    if (p < r) {
        int pivo_indice = particionaEleitor(vetor, p, r);
        quickSortEleitor(vetor, p, pivo_indice - 1);
        quickSortEleitor(vetor, pivo_indice + 1, r);
    }
}
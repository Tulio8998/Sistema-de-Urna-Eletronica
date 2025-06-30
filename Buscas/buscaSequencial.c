#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "buscaSequencial.h"

TAdm *buscaSequencialAdministrador(int chave, FILE *in, FILE *log) {
    TAdm *a = NULL;
    int achou = 0;
    int cont = 0;
    int inicio, fim;
    double total;

    rewind(in);
    inicio = clock();

    while ((a = leAdministrador(in)) != NULL) {
        cont++;
        if (a->codigo == chave) {
            achou = 1;
            break;
        }
        free(a);
    }

    if (achou == 1) {
        fprintf(log, "\nComparacoes Sequencial (Admin): %d ", cont);
        fim = clock();
        total = (double)(fim - inicio) / CLOCKS_PER_SEC;
        fprintf(log, "\nTempo Sequencial (Admin): %f ", total);
        return a;
    } else {
        printf("Administrador nao encontrado.\n");
        return NULL;
    }
}

TCandidato *buscaSequencialCandidato(int chave, FILE *in, FILE *log) {
    TCandidato *c = NULL;
    int achou = 0;
    int cont = 0;
    int inicio, fim;
    double total;

    rewind(in);
    inicio = clock();

    while ((c = leCandidato(in)) != NULL) {
        cont++;
        if (c->codigo == chave) {
            achou = 1;
            break;
        }
        
        free(c);
    }

    if (achou == 1) {
        fprintf(log, "\nComparacoes Sequencial (Candidato): %d ", cont);
        fim = clock();
        total = (double)(fim - inicio) / CLOCKS_PER_SEC;
        fprintf(log, "\nTempo Sequencial (Candidato): %f ", total);
        return c;
    } else {
        printf("Candidato nao encontrado.\n");
        return NULL;
    }
}

TEleitor *buscaSequencialEleitor(int chave, FILE *in, FILE *log) {
    TEleitor *e = NULL;
    int achou = 0;
    int cont = 0;
    int inicio, fim;
    double total;

    rewind(in);
    inicio = clock();

    while ((e = leEleitor(in)) != NULL) {
        cont++;
        if (e->codigo == chave) {
            achou = 1;
            break;
        }
        
        free(e);
    }

    if (achou == 1) {
        fprintf(log, "\nComparacoes Sequencial (Eleitor): %d ", cont);
        fim = clock();
        total = (double)(fim - inicio) / CLOCKS_PER_SEC;
        fprintf(log, "\nTempo Sequencial (Eleitor): %f ", total);
        return e;
    } else {
        printf("Eleitor nao encontrado.\n");
        return NULL;
    }
}
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>
#include "buscaBinaria.h"

TAdm *buscaBinariaAdministrador(int chave, FILE *in, int inicio, int fim, FILE *log) {
    TAdm *a = NULL;
    int cont = 0;
    int inicioT, fimT;
    double total;

    inicioT = clock();

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        fseek(in, meio * tamanho_registro_administrador(), SEEK_SET);

        if (a != NULL) {
            free(a);
        }
        a = leAdministrador(in);
        cont++;

        if (a == NULL) {
            return NULL;
        }

        if (a->codigo < chave) {
            inicio = meio + 1;
        } else if (a->codigo > chave) {
            fim = meio - 1;
        } else {
            if (log) {
                fprintf(log, "\nComparacoes Binaria (Admin): %d ", cont);
                fimT = clock();
                total = (double)(fimT - inicioT) / CLOCKS_PER_SEC;
                fprintf(log, "\nTempo Binaria (Admin): %f ", total);
            }
            return a;
        }
    }
    if (a != NULL) {
        free(a);
    }
    return NULL;
}

TCandidato *buscaBinariaCandidato(int chave, FILE *in, int inicio, int fim, FILE *log) {
    TCandidato *c = NULL;
    int cont = 0;
    int inicioT, fimT;
    double total;

    inicioT = clock();

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        fseek(in, meio * tamanho_registro_candidato(), SEEK_SET);
        if (c != NULL) free(c);
        c = leCandidato(in);
        cont++;

        if (c == NULL) return NULL;

        if (c->codigo < chave) {
            inicio = meio + 1;
        } else if (c->codigo > chave) {
            fim = meio - 1;
        } else {
            if (log) {
                fprintf(log, "\nComparacoes Binaria (Candidato): %d ", cont);
                fimT = clock();
                total = (double)(fimT - inicioT) / CLOCKS_PER_SEC;
                fprintf(log, "\nTempo Binaria (Candidato): %f ", total);
            }
            return c;
        }
    }
    if (c != NULL) free(c);
    return NULL;
}

TEleitor *buscaBinariaEleitor(int chave, FILE *in, int inicio, int fim, FILE *log) {
    TEleitor *e = NULL;
    int cont = 0;
    int inicioT, fimT;
    double total;

    inicioT = clock();

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        fseek(in, meio * tamanho_registro_eleitor(), SEEK_SET);
        if (e != NULL) free(e);
        e = leEleitor(in);
        cont++;

        if (e == NULL) return NULL;

        if (e->codigo < chave) {
            inicio = meio + 1;
        } else if (e->codigo > chave) {
            fim = meio - 1;
        } else {
            if (log) {
                fprintf(log, "\nComparacoes Binaria (Eleitor): %d ", cont);
                fimT = clock();
                total = (double)(fimT - inicioT) / CLOCKS_PER_SEC;
                fprintf(log, "\nTempo Binaria (Eleitor): %f ", total);
            }
            return e;
        }
    }
    if (e != NULL) free(e);
    return NULL;
}
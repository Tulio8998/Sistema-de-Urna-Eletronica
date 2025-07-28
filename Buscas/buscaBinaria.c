#include <string.h>
#include <stdlib.h>
#include "buscaBinaria.h"

TAdm *buscaBinariaAdministrador(int chave, FILE *in, int inicio, int fim) {
    TAdm *a = NULL;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        fseek(in, meio * tamanho_registro_administrador(), SEEK_SET);

        if (a != NULL) {
            free(a);
        }
        a = leAdministrador(in);

        if (a == NULL) {
            return NULL;
        }

        if (a->codigo < chave) {
            inicio = meio + 1;
        } else if (a->codigo > chave) {
            fim = meio - 1;
        } else {
            return a;
        }
    }
    if (a != NULL) {
        free(a);
    }
    return NULL;
}

TCandidato *buscaBinariaCandidato(int chave, FILE *in, int inicio, int fim) {
    TCandidato *c = NULL;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        fseek(in, meio * tamanho_registro_candidato(), SEEK_SET);

        if (c != NULL) {
            free(c);
        }
        c = leCandidato(in);

        if (c == NULL) {
            return NULL;
        }

        if (c->codigo < chave) {
            inicio = meio + 1;
        } else if (c->codigo > chave) {
            fim = meio - 1;
        } else {
            return c;
        }
    }
    if (c != NULL) {
        free(c);
    }
    return NULL;
}

TEleitor *buscaBinariaEleitor(int chave, FILE *in, int inicio, int fim) {
    TEleitor *e = NULL;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        fseek(in, meio * tamanho_registro_eleitor(), SEEK_SET);

        if (e != NULL) {
            free(e);
        }
        e = leEleitor(in);

        if (e == NULL) {
            return NULL;
        }

        if (e->codigo < chave) {
            inicio = meio + 1;
        } else if (e->codigo > chave) {
            fim = meio - 1;
        } else {
            return e;
        }
    }
    if (e != NULL) {
        free(e);
    }
    return NULL;
}

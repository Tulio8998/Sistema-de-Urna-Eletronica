#include <string.h>
#include <stdlib.h>
#include "buscaSequencial.h"

TAdm *buscaSequencialAdministrador(int chave, FILE *in) {
    TAdm *a = NULL;

    rewind(in);

    while ((a = leAdministrador(in)) != NULL) {
        if (a->codigo == chave) {
            return a;
        }
        free(a);
    }

    printf("Administrador nao encontrado.\n");
    return NULL;
}

TCandidato *buscaSequencialCandidato(int chave, FILE *in) {
    TCandidato *c = NULL;

    rewind(in);

    while ((c = leCandidato(in)) != NULL) {
        if (c->codigo == chave) {
            return c;
        }
        free(c);
    }

    printf("Candidato nao encontrado.\n");
    return NULL;
}

TEleitor *buscaSequencialEleitor(int chave, FILE *in) {
    TEleitor *e = NULL;

    rewind(in);

    while ((e = leEleitor(in)) != NULL) {
        if (e->codigo == chave) {
            return e;
        }
        free(e);
    }

    printf("Eleitor nao encontrado.\n");
    return NULL;
}

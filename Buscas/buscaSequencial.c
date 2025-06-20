#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "buscaSequencial.h"

TAdm *buscaSequencialAdministrador(int chave, FILE *in, FILE *log) {
    TAdm *a;
    int achou;
    int cont = 0;
    int inicio, fim;
    double total;

    rewind(in);

    inicio = clock();

    while ((a = leAdministrador(in)) != NULL){

        cont ++;

        if(a->codigo == chave){
           achou = 1;
           break;
        }
    }
        if(achou == 1){
            fprintf(log, "\nComparacoes Sequencial: %d ", cont);
            fim = clock();
            total = (fim - inicio)/CLOCKS_PER_SEC;
            fprintf(log, "\nTempo Sequencial: %f ", total);
            return a;
        }

        else {
            printf("Administrador nao encontrado");
            fprintf(log, "Comparacoes Sequencial: %d ", cont);
            fim = clock();
            total = (fim - inicio)/CLOCKS_PER_SEC;
            fprintf(log, "Tempo Sequencial: %d ", cont);
        }

        free(a);
}

TCandidato *buscaSequencialCandidato(int chave, FILE *in, FILE *log) {
    TCandidato *c;
    int achou;
    int cont = 0;
    int inicio, fim;
    double total;

    rewind(in);

    inicio = clock();

    while ((c = leCandidato(in)) != NULL){

        cont ++;

        if(c->codigo == chave){
           achou = 1;
           break;
        }
    }
        if(achou == 1){
            fprintf(log, "\nComparacoes Sequencial: %d ", cont);
            fim = clock();
            total = (fim - inicio)/CLOCKS_PER_SEC;
            fprintf(log, "\nTempo Sequencial: %f ", total);
            return c;
        }

        else {
            printf("Candidato nao encontrado");
            fprintf(log, "Comparacoes Sequencial: %d ", cont);
            fim = clock();
            total = (fim - inicio)/CLOCKS_PER_SEC;
            fprintf(log, "Tempo Sequencial: %d ", cont);
        }

        free(c);
}

TEleitor *buscaSequencialEleitor(int chave, FILE *in, FILE *log) {
    TEleitor *e;
    int achou;
    int cont = 0;
    int inicio, fim;
    double total;

    rewind(in);

    inicio = clock();

    while ((e = leEleitor(in)) != NULL){

        cont ++;

        if(e->codigo == chave){
           achou = 1;
           break;
        }
    }
        if(achou == 1){
            fprintf(log, "\nComparacoes Sequencial: %d ", cont);
            fim = clock();
            total = (fim - inicio)/CLOCKS_PER_SEC;
            fprintf(log, "\nTempo Sequencial: %f ", total);
            return e;
        }

        else {
            printf("Eleitor nao encontrado");
            fprintf(log, "Comparacoes Sequencial: %d ", cont);
            fim = clock();
            total = (fim - inicio)/CLOCKS_PER_SEC;
            fprintf(log, "Tempo Sequencial: %d ", cont);
        }

        free(e);
}
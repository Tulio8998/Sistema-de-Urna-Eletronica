#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "../Entities/administrador.h"
#include "../Entities/candidato.h"
#include "../Entities/eleitor.h"

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
            printf("Funcionario nao encontrado");
            fprintf(log, "Comparacoes Sequencial: %d ", cont);
            fim = clock();
            total = (fim - inicio)/CLOCKS_PER_SEC;
            fprintf(log, "Tempo Sequencial: %d ", cont);
        }

        free(a);
}

/*
TCandidato *buscaSequencialCandidato(int chave, FILE *in, FILE *log) {
    TCandidato *c;
    int achou;
    int cont = 0;
    int inicio, fim;
    double total;

    rewind(in);

    inicio = clock();

    while ((c = leAdministrador(in)) != NULL){

        cont ++;

        if(f->codigo == chave){
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
            printf("Funcionario nao encontrado");
            fprintf(log, "Comparacoes Sequencial: %d ", cont);
            fim = clock();
            total = (fim - inicio)/CLOCKS_PER_SEC;
            fprintf(log, "Tempo Sequencial: %d ", cont);
        }

        free(c);
}

TEleitor *buscaSequencialEleitor(int chave, FILE *in, FILE *log) {
    TAdm *e;
    int achou;
    int cont = 0;
    int inicio, fim;
    double total;

    rewind(in);

    inicio = clock();

    while ((e = leAdministrador(in)) != NULL){

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
            printf("Funcionario nao encontrado");
            fprintf(log, "Comparacoes Sequencial: %d ", cont);
            fim = clock();
            total = (fim - inicio)/CLOCKS_PER_SEC;
            fprintf(log, "Tempo Sequencial: %d ", cont);
        }

        free(e);
}
*/
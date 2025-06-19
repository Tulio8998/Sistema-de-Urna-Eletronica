#include "Entities/administrador.h"
#include "Entities/candidato.h"
#include "Entities/eleitor.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

TAdm *buscaSequencialAdministrador(int chave, FILE *in, FILE *log) {
    TAdm *f;
    int achou;
    int cont = 0;
    int inicio, fim;
    double total;

    rewind(in);

    inicio = clock();

    while ((f = leAdministrador(in)) != NULL){

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
            return f;
        }

        else {
            printf("Funcionario nao encontrado");
            fprintf(log, "Comparacoes Sequencial: %d ", cont);
            fim = clock();
            total = (fim - inicio)/CLOCKS_PER_SEC;
            fprintf(log, "Tempo Sequencial: %d ", cont);
        }

        free(f);
}

/*
TCandidato *buscaSequencialCandidato(int chave, FILE *in, FILE *log) {
    TCandidato *f;
    int achou;
    int cont = 0;
    int inicio, fim;
    double total;

    rewind(in);

    inicio = clock();

    while ((f = leAdministrador(in)) != NULL){

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
            return f;
        }

        else {
            printf("Funcionario nao encontrado");
            fprintf(log, "Comparacoes Sequencial: %d ", cont);
            fim = clock();
            total = (fim - inicio)/CLOCKS_PER_SEC;
            fprintf(log, "Tempo Sequencial: %d ", cont);
        }

        free(f);
}

TEleitor *buscaSequencialEleitor(int chave, FILE *in, FILE *log) {
    TAdm *f;
    int achou;
    int cont = 0;
    int inicio, fim;
    double total;

    rewind(in);

    inicio = clock();

    while ((f = leAdministrador(in)) != NULL){

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
            return f;
        }

        else {
            printf("Funcionario nao encontrado");
            fprintf(log, "Comparacoes Sequencial: %d ", cont);
            fim = clock();
            total = (fim - inicio)/CLOCKS_PER_SEC;
            fprintf(log, "Tempo Sequencial: %d ", cont);
        }

        free(f);
}
*/
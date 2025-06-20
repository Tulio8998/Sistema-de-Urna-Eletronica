#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>
#include "buscaBinaria.h"

//Realiza uma busca binaria por um funcionario na base de dados

TAdm *buscaBinariaAdministrador(int chave, FILE *in, int inicio, int fim, FILE *log) {
    TAdm *a = NULL;
    int cod = -1;
    int cont = 0;
    int inicioT, fimT;
    double total;

    inicioT = clock();

    while (inicio <= fim && cod != chave) {

        int meio = trunc((inicio + fim) / 2);
        //printf("Inicio: %d; Fim: %d; Meio: %d\n", inicio, fim, meio);
        fseek(in, (meio - 1) * tamanho_registro_administrador(), SEEK_SET);
        a = leAdministrador(in);
        cod = a->codigo;

        cont ++;

        if (a) {
            if (cod > chave) {
                fim = meio - 1;
            } else {
                inicio = meio + 1;
            }
        }
    }

    if (cod == chave) {
        fprintf(log, "\nComparacoes Binaria: %d ", cont);
        fimT = clock();
        total = (fimT - inicioT) / CLOCKS_PER_SEC;
        fprintf(log, "\nTempo Binaria: %f ", total);
        return a;
    }
    else return NULL;
}

TCandidato *buscaBinariaCandidato(int chave, FILE *in, int inicio, int fim, FILE *log) {
    TCandidato *c = NULL;
    int cod = -1;
    int cont = 0;
    int inicioT, fimT;
    double total;

    inicioT = clock();

    while (inicio <= fim && cod != chave) {

        int meio = trunc((inicio + fim) / 2);
        //printf("Inicio: %d; Fim: %d; Meio: %d\n", inicio, fim, meio);
        fseek(in, (meio - 1) * tamanho_registro_candidato(), SEEK_SET);
        c = leCandidato(in);
        cod = c->codigo;

        cont ++;

        if (c) {
            if (cod > chave) {
                fim = meio - 1;
            } else {
                inicio = meio + 1;
            }
        }
    }

    if (cod == chave) {
        fprintf(log, "\nComparacoes Binaria: %d ", cont);
        fimT = clock();
        total = (fimT - inicioT) / CLOCKS_PER_SEC;
        fprintf(log, "\nTempo Binaria: %f ", total);
        return c;
    }
    else return NULL;
}

TEleitor *buscaBinariaEleitor(int chave, FILE *in, int inicio, int fim, FILE *log) {
    TEleitor *e = NULL;
    int cod = -1;
    int cont = 0;
    int inicioT, fimT;
    double total;

    inicioT = clock();

    while (inicio <= fim && cod != chave) {

        int meio = trunc((inicio + fim) / 2);
        //printf("Inicio: %d; Fim: %d; Meio: %d\n", inicio, fim, meio);
        fseek(in, (meio - 1) * tamanho_registro_eleitor(), SEEK_SET);
        e = leEleitor(in);
        cod = e->codigo;

        cont ++;

        if (e) {
            if (cod > chave) {
                fim = meio - 1;
            } else {
                inicio = meio + 1;
            }
        }
    }

    if (cod == chave) {
        fprintf(log, "\nComparacoes Binaria: %d ", cont);
        fimT = clock();
        total = (fimT - inicioT) / CLOCKS_PER_SEC;
        fprintf(log, "\nTempo Binaria: %f ", total);
        return e;
    }
    else return NULL;
}
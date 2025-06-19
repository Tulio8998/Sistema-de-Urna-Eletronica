#include "Entities/administrador.h"
#include "Entities/candidato.h"
#include "Entities/eleitor.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

//Realiza uma busca binaria por um funcionario na base de dados

TAdm *buscaBinariaAdministrador(int chave, FILE *in, int inicio, int fim, FILE *log) {

    TAdm *f = NULL;
    int cod = -1;
    int cont = 0;
    int inicioT, fimT;
    double total;

    inicioT = clock();

    while (inicio <= fim && cod != chave) {

        int meio = trunc((inicio + fim) / 2);
        //printf("Inicio: %d; Fim: %d; Meio: %d\n", inicio, fim, meio);
        fseek(in, (meio -1) * tamanho_registro(), SEEK_SET);
        f = le(in);
        cod = f->codigo;

        cont ++;

        if (f) {
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
        return f;
    }
    else return NULL;
}

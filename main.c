#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Entities/administrador.h"
#include "Entities/candidato.h"
#include "Entities/eleitor.h"
#include "Ordenacao/classificacaoInterna.h"
#include "Buscas/buscaSequencial.h"
#include "Buscas/buscaBinaria.h"

int main () {
    srand(time(NULL));

#ifdef _WIN32
    system("chcp 65001");
#endif

    FILE *arq_adm, *arq_cand, *arq_eleitor;
    FILE *log;

    TAdm *adm_encontrado;
    TCandidato *cand_encontrado;
    TEleitor *eleitor_encontrado;
    
    int qnt_adm = 2;
    int qnt_cand = 3;
    int qnt_ele = 5;

    if ((log = fopen("Data/log.txt", "w")) == NULL) {
        printf("Erro ao abrir arquivo de log\n");
        exit(1);
    }

    // ADMINISTRADOR ---
    printf("\n---------- ADMINISTRADOR ----------\n");
    if ((arq_adm = fopen("Data/administradores.dat", "w+b")) == NULL) {
        printf("Erro ao criar o arquivo administradores.dat\n");
        exit(1);
    } else {
        criarBaseAdministrador(arq_adm, qnt_adm);
        int part_adm = (qnt_adm + 1) / 2;
        classificacaoInternaAdministrador(arq_adm, part_adm);
        imprimirBaseAdministrador(arq_adm);

        printf("\nBuscando Sequencial por adm codigo 2...\n");
        adm_encontrado = buscaSequencialAdministrador(2, arq_adm, log);
        if (adm_encontrado != NULL) {
            imprimeAdministrador(adm_encontrado);
            free(adm_encontrado);
        }
        fclose(arq_adm);
    }

    // CANDIDATO
    printf("\n\n\n\n---------- CANDIDATO ----------\n");
    if ((arq_cand = fopen("Data/candidatos.dat", "w+b")) == NULL) {
        printf("Erro ao criar o arquivo candidatos.dat\n");
        exit(1);
    } else {
        criarBaseCandidato(arq_cand, qnt_cand);
        imprimirBaseCandidato(arq_cand);
        int part_cand = (qnt_cand + 1) / 2;
        classificacaoInternaCandidato(arq_cand, part_cand);

        printf("\nBuscando Sequencial por candidato codigo 3...\n");
        cand_encontrado = buscaSequencialCandidato(3, arq_cand, log);
        if(cand_encontrado != NULL){
            imprimeCandidato(cand_encontrado);
            free(cand_encontrado);
        }
        fclose(arq_cand); 
    }

    // ELEITOR
    printf("\n\n\n---------- ELEITOR ----------\n");
    if ((arq_eleitor = fopen("Data/eleitores.dat", "w+b")) == NULL) {
        printf("Erro ao criar o arquivo eleitores.dat\n");
        exit(1);
    } else {
        criarBaseEleitor(arq_eleitor, qnt_ele);
        imprimirBaseEleitor(arq_eleitor);
        int part_ele = (qnt_ele + 1) / 2;
        classificacaoInternaEleitor(arq_cand, part_ele);

        printf("\nBuscando Sequencial por eleitor codigo 1...\n");
        eleitor_encontrado = buscaSequencialEleitor(1, arq_eleitor, log);
        if(eleitor_encontrado != NULL){
            imprimeEleitor(eleitor_encontrado);
            free(eleitor_encontrado);
        }
        fclose(arq_eleitor);
    }
    
    fclose(log);
    printf("\nPrograma finalizado.\n");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Entities/administrador.h"
#include "Entities/candidato.h"
#include "Entities/eleitor.h"
#include "Buscas/buscaSequencial.h"
#include "Buscas/buscaBinaria.h"

int main () {
#ifdef _WIN32
    system("chcp 65001");
#endif

    FILE *arq_adm, *arq_cand, *arq_eleitor;
    FILE *log;

    TAdm *adm_encontrado;
    TCandidato *cand_encontrado;
    TEleitor *eleitor_encontrado;

    if ((log = fopen("log.txt", "w")) == NULL) {
        printf("Erro ao abrir arquivo de log\n");
        exit(1);
    }

    // --- BLOCO DO ADMINISTRADOR ---
    printf("\n---------- ADMINISTRADOR ----------\n");
    if ((arq_adm = fopen("administradores.dat", "w+b")) == NULL) {
        printf("Erro ao criar o arquivo administradores.dat\n");
        exit(1);
    } else {
        criarBaseAdministrador(arq_adm, 2);
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
    if ((arq_cand = fopen("candidatos.dat", "w+b")) == NULL) {
        printf("Erro ao criar o arquivo candidatos.dat\n");
        exit(1);
    } else {
        criarBaseCandidato(arq_cand, 3);
        imprimirBaseCandidato(arq_cand);

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
    if ((arq_eleitor = fopen("eleitores.dat", "w+b")) == NULL) {
        printf("Erro ao criar o arquivo eleitores.dat\n");
        exit(1);
    } else {
        criarBaseEleitor(arq_eleitor, 4);
        imprimirBaseEleitor(arq_eleitor);
        
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
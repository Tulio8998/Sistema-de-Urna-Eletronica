#include <stdio.h>
#include <stdlib.h>
#include "menuEleitor.h"
#include "../Entities/candidato.h"
#include "../Votos/votacao.h"

void iniciar_menu_eleitor(TEleitor *eleitor_logado) {
    int opcao;
    printf("\nBem-vindo, Eleitor %s!", eleitor_logado->base.nome);

    do {
        printf("\n\n======================================================");
        printf("\n\tMENU ELEITOR");
        printf("\n======================================================\n");
        printf("1. Visualizar Candidatos\n");
        printf("2. Votar\n");
        printf("0. Deslogar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
         if (opcao != 1 && opcao != 2 && opcao != 0){
            printf("Opcao invalida. Tente novamente.\n");
            continue;
        }

        switch (opcao) {
            case 1: {
                FILE *arq = fopen("Data/candidatos.dat", "rb");
                if (arq == NULL) {
                    printf("Nenhum candidato cadastrado.\n");
                } else {
                    imprimirBaseCandidatoParaEleitor(arq);
                    fclose(arq);
                }
                break;
            }
            case 2:
                votacao();
                break;
            case 0:
                printf("Deslogando...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);
}
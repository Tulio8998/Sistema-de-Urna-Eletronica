#include <stdio.h>
#include <stdlib.h>
#include "votacao.h"

void votacao() {
    FILE *arq = fopen("Data/candidatos.dat", "r+b");
    if (arq == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo de candidatos.\n");
        return;
    }

    printf("\n--- CANDIDATOS DISPONIVEIS ---\n");
    imprimirBaseCandidatoParaEleitor(arq);

    int codigo_voto;
    printf("\nDigite o codigo do candidato em que deseja votar: ");
    scanf("%d", &codigo_voto);

    rewind(arq);
    TCandidato *cand_lido;
    int encontrado = 0;
    long pos;

    while ((pos = ftell(arq)), (cand_lido = leCandidato(arq)) != NULL) {
        if (cand_lido->codigo == codigo_voto) {
            cand_lido->voto++; 
            fseek(arq, pos, SEEK_SET); 
            salvaCandidato(cand_lido, arq);
            printf("\nVoto registrado com sucesso para o candidato %s!\n", cand_lido->base.nome);
            encontrado = 1;
            free(cand_lido);
            break; 
        }
        free(cand_lido);
    }

    if (!encontrado) {
        printf("Candidato com codigo %d nao encontrado.\n", codigo_voto);
    }

    fclose(arq);
}

void gerar_relatorio() {
    FILE *arq = fopen("Data/candidatos.dat", "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de candidatos.\n");
        return;
    }
    
    TCandidato *c;
    printf("\n======================================================");
    printf("\n\tRELATORIO DE VOTOS");
    printf("\n======================================================\n");
    while ((c = leCandidato(arq)) != NULL) {
        printf("Candidato: %s (%s) - Votos: %d\n", c->base.nome, c->partido, c->voto);
        free(c);
    }
    fclose(arq);
    printf("======================================================\n\n");
}
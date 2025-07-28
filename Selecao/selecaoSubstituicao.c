#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../Entities/candidato.h"
#include "../Buscas/buscaBinaria.h"
#include "selecaoSubstituicao.h"
#define M 6
#define VAZIO -1
long long int comparacoes_selecao = 0;
long long int leituras_selecao = 0;
long long int escritas_selecao = 0;

void selecaoPorSubstituicao(FILE *arqEntrada) {
    comparacoes_selecao = 0;
    leituras_selecao = 0;
    escritas_selecao = 0;

    rewind(arqEntrada);
    int numRegistrosTotal = tamanho_arquivo_candidato(arqEntrada);
    if (numRegistrosTotal == 0) {
        return;
    }

    TCandidato memoria[M];
    bool congelado[M];
    int registrosLidos = 0;

    for (int i = 0; i < M; i++) {
        if (!feof(arqEntrada)) {
            size_t lidos = fread(&memoria[i], sizeof(TCandidato), 1, arqEntrada);
            leituras_selecao++;
            if (lidos == 1) {
                 registrosLidos++;
            } else {
                memoria[i].codigo = VAZIO;
            }
        } else {
            memoria[i].codigo = VAZIO;
        }
    }

    int numParticao = 0;
    int registrosEscritos = 0;

    while (registrosEscritos < numRegistrosTotal) {
        numParticao++;
        char nomeParticao[50];
        sprintf(nomeParticao, "Data/Particoes/particao_%d.dat", numParticao);

        FILE *arqSaida = fopen(nomeParticao, "wb");
        if (arqSaida == NULL) {
            printf("Nao foi possivel criar o arquivo de particao");
            return;
        }
        for (int i = 0; i < M; i++) {
            congelado[i] = false;
        }

        while (true) {
            int codigoMenor = -1;

            for (int i = 0; i < M; i++) {
                if (!congelado[i] && memoria[i].codigo != VAZIO) {
                    if (codigoMenor == -1 || memoria[i].codigo < memoria[codigoMenor].codigo) {
                        codigoMenor = i;
                    }
                }
            }

            if (codigoMenor == -1) {
                break;
            }

            TCandidato menorCandidato = memoria[codigoMenor];
            salvaCandidato(&menorCandidato, arqSaida);
            escritas_selecao++;
            registrosEscritos++;

            if (registrosLidos < numRegistrosTotal) {
                fread(&memoria[codigoMenor], sizeof(TCandidato), 1, arqEntrada);
                leituras_selecao++;
                registrosLidos++;
                comparacoes_selecao++;
                if (memoria[codigoMenor].codigo < menorCandidato.codigo) {
                    congelado[codigoMenor] = true;
                }
            } else {
                memoria[codigoMenor].codigo = VAZIO;
            }
        }

        fclose(arqSaida);
    }
}
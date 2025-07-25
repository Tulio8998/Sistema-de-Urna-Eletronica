#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "candidato.h"
#include "../Util/util.h"


int tamanho_registro_candidato() {
    return sizeof(int)         
           + sizeof(char) * 50 
           + sizeof(char) * 15  
           + sizeof(char) * 11 
           + sizeof(char) * 50 
           + sizeof(char) * 50
           + sizeof(int);
}

TCandidato *candidato(int codigo, char *nome, char *cpf, char *data_nascimento, char *cargo, char *partido) {
    TCandidato *cand = (TCandidato *) malloc(sizeof(TCandidato));
    if (cand) memset(cand, 0, sizeof(TCandidato));
    cand->codigo = codigo;
    strcpy(cand->base.nome, nome);
    strcpy(cand->base.cpf, cpf);
    strcpy(cand->base.data_nascimento, data_nascimento);
    strcpy(cand->cargo, cargo);
    strcpy(cand->partido, partido);
    cand->voto = 0;
    return cand;
}

void salvaCandidato(TCandidato *cand, FILE *out) {
    fwrite(&cand->codigo, sizeof(int), 1, out);
    fwrite(cand->base.nome, sizeof(char), sizeof(cand->base.nome), out);
    fwrite(cand->base.cpf, sizeof(char), sizeof(cand->base.cpf), out);
    fwrite(cand->base.data_nascimento, sizeof(char), sizeof(cand->base.data_nascimento), out);
    fwrite(cand->cargo, sizeof(char), sizeof(cand->cargo), out);
    fwrite(cand->partido, sizeof(char), sizeof(cand->partido), out);
    fwrite(&cand->voto, sizeof(int), 1, out);
}

int tamanho_arquivo_candidato(FILE *arq){
    fseek(arq, 0, SEEK_END);
    int tam = trunc(ftell(arq) / tamanho_registro_candidato());
    rewind(arq);
    return tam;
}

TCandidato *leCandidato(FILE *in) {
    TCandidato *cand = (TCandidato *) malloc(sizeof(TCandidato));
    if (fread(&cand->codigo, sizeof(int), 1, in) <= 0) {
        free(cand);
        return NULL;
    }
    fread(cand->base.nome, sizeof(char), sizeof(cand->base.nome), in);
    fread(cand->base.cpf, sizeof(char), sizeof(cand->base.cpf), in);
    fread(cand->base.data_nascimento, sizeof(char), sizeof(cand->base.data_nascimento), in);
    fread(cand->cargo, sizeof(char), sizeof(cand->cargo), in);
    fread(cand->partido, sizeof(char), sizeof(cand->partido), in);
    fread(&cand->voto, sizeof(int), 1, in);
    return cand;
}

void imprimeCandidato(TCandidato *cand) {
    printf("__________________________________________________\n");
    printf("Candidato de codigo: %d\n", cand->codigo);
    printf("Nome: %s\n", cand->base.nome);
    printf("CPF: %s\n", cand->base.cpf);
    printf("Data de Nascimento: %s\n", cand->base.data_nascimento);
    printf("Cargo: %s\n", cand->cargo);
    printf("Partido: %s\n", cand->partido);
    printf("Votos: %d\n", cand->voto);
    printf("__________________________________________________\n");
}

void imprimeCandidatoParaEleitor(TCandidato *cand) {
    printf("__________________________________________________\n");
    printf("Candidato de codigo: %d\n", cand->codigo);
    printf("Nome: %s\n", cand->base.nome);
    printf("Data de Nascimento: %s\n", cand->base.data_nascimento);
    printf("Cargo: %s\n", cand->cargo);
    printf("Partido: %s\n", cand->partido);
    printf("__________________________________________________\n");
}

void criarBaseCandidato(FILE *out, int tam) {
    int vet[tam];
    TCandidato c;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;
    
    shuffleCandidato(vet, tam, 0);

    for (int i=0;i<tam;i++){
        c = generateRandomUserCand(vet[i]);
        salvaCandidato(&c, out);
    }
}

void shuffleCandidato(int *vet,int MAX,int MIN) {
    for (int i = MAX - MIN - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}

void imprimirBaseCandidato(FILE *out) {
    printf("\nImprimindo a base de dados de Candidatos...\n");
    rewind(out);
    TCandidato *c;
    while ((c = leCandidato(out)) != NULL) {
        imprimeCandidato(c);
        free(c);
    }
}

void imprimirBaseCandidatoParaEleitor(FILE *out) {
    printf("\nImprimindo a base de dados de Candidatos...\n");
    rewind(out);
    TCandidato *c;
    while ((c = leCandidato(out)) != NULL) {
        imprimeCandidatoParaEleitor(c);
        free(c);
    }
}

int comparaCandidato(TCandidato *c1, TCandidato *c2)
{
	if (c1 == NULL) {
		return (c2 == NULL);
	}
	if (c1->codigo != c2->codigo) {
		return 0;
	}
	if (strcmp(c1->base.nome, c2->base.nome) != 0) {
		return 0;
	}
	return 1;
}
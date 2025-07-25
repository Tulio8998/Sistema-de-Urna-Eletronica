#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "eleitor.h"
#include "../Util/util.h"

int tamanho_registro_eleitor() {
    return sizeof(int)         
           + sizeof(char) * 50 
           + sizeof(char) * 15  
           + sizeof(char) * 11  
           + sizeof(char) * 15  
           + sizeof(char) * 5   
           + sizeof(char) * 5;  
}

TEleitor *eleitor(int codigo, char *nome, char *cpf, char *data_nascimento, char *titulo, char *secao, char* zona) {
    TEleitor *eleit = (TEleitor *) malloc(sizeof(TEleitor));
    if (eleit) memset(eleit, 0, sizeof(TEleitor));
    
    eleit->codigo = codigo;
    strcpy(eleit->base.nome, nome);
    strcpy(eleit->base.cpf, cpf);
    strcpy(eleit->base.data_nascimento, data_nascimento);
    strcpy(eleit->titulo_eleitor, titulo);
    strcpy(eleit->secao, secao);
    strcpy(eleit->zona, zona);
    
    return eleit;
}

void salvaEleitor(TEleitor *eleit, FILE *out) {
    fwrite(&eleit->codigo, sizeof(int), 1, out);
    fwrite(eleit->base.nome, sizeof(char), sizeof(eleit->base.nome), out);
    fwrite(eleit->base.cpf, sizeof(char), sizeof(eleit->base.cpf), out);
    fwrite(eleit->base.data_nascimento, sizeof(char), sizeof(eleit->base.data_nascimento), out);
    fwrite(eleit->titulo_eleitor, sizeof(char), sizeof(eleit->titulo_eleitor), out);
    fwrite(eleit->secao, sizeof(char), sizeof(eleit->secao), out);
    fwrite(eleit->zona, sizeof(char), sizeof(eleit->zona), out);
}

int tamanho_arquivo_eleitor(FILE *arq){
    fseek(arq, 0, SEEK_END);
    int tam = trunc(ftell(arq) / tamanho_registro_eleitor());
    rewind(arq);
    return tam;
}

TEleitor *leEleitor(FILE *in) {
    TEleitor *eleit = (TEleitor *) malloc(sizeof(TEleitor));
    if (fread(&eleit->codigo, sizeof(int), 1, in) <= 0) {
        free(eleit);
        return NULL;
    }
    fread(eleit->base.nome, sizeof(char), sizeof(eleit->base.nome), in);
    fread(eleit->base.cpf, sizeof(char), sizeof(eleit->base.cpf), in);
    fread(eleit->base.data_nascimento, sizeof(char), sizeof(eleit->base.data_nascimento), in);
    fread(eleit->titulo_eleitor, sizeof(char), sizeof(eleit->titulo_eleitor), in);
    fread(eleit->secao, sizeof(char), sizeof(eleit->secao), in);
    fread(eleit->zona, sizeof(char), sizeof(eleit->zona), in);
    return eleit;
}

void imprimeEleitor(TEleitor *eleit) {
    printf("__________________________________________________\n");
    printf("Eleitor de codigo: %d\n", eleit->codigo);
    printf("Nome: %s\n", eleit->base.nome);
    printf("CPF: %s\n", eleit->base.cpf);
    printf("Data de Nascimento: %s\n", eleit->base.data_nascimento);
    printf("Titulo de Eleitor: %s\n", eleit->titulo_eleitor);
    printf("Secao: %s\n", eleit->secao);
    printf("Zona: %s\n", eleit->zona);
    printf("__________________________________________________\n");
}

void criarBaseEleitor(FILE *out, int tam) {
    int vet[tam];
    TEleitor e;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;
    
    shuffleEleitor(vet, tam, 0); 

    for (int i=0;i<tam;i++){
        e = generateRandomUserElei(vet[i]);
        salvaEleitor(&e, out);
    }
}


void shuffleEleitor(int *vet,int MAX,int MIN) {
    srand(time(NULL));
    for (int i = MAX - MIN - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}

void imprimirBaseEleitor(FILE *out) {
    printf("\nImprimindo a base de dados de Eleitores...\n");
    rewind(out);
    TEleitor *e;
    while ((e= leEleitor(out)) != NULL) {
        imprimeEleitor(e);
        free(e);
    }
}

TEleitor* autenticar_eleitor(char* titulo) {
    FILE* arq = fopen("Data/eleitores.dat", "rb");
    if (arq == NULL) return NULL;

    TEleitor *eleitor_lido;
    while ((eleitor_lido = leEleitor(arq)) != NULL) {
        if (strcmp(eleitor_lido->titulo_eleitor, titulo) == 0) {
            fclose(arq);
            return eleitor_lido;
        }
        free(eleitor_lido);
    }
    fclose(arq);
    return NULL;
}

int comparaEleitor(TEleitor *c1, TEleitor *c2)
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "administrador.h"


// Retorna tamanho do funcionario em bytes
int tamanho_registro(){
    return sizeof(int)  //cod
           + sizeof(char) * 50 //nome
           + sizeof(char) * 15 //cpf
           + sizeof(char) * 11 //data_nascimento
           + sizeof(bool); //verificacao
}

TAdm *administrador(int codigo, char *nome, char *cpf, char *data_nascimento, bool verificacao){
    TAdm *ATAdm = (TAdm *) malloc(sizeof(TAdm));
    //inicializa espaco de memoria com ZEROS
    if (ATAdm) memset(ATAdm, 0, sizeof(TAdm));
    //copia valores para os campos de ATAdm
    ATAdm->codigo = codigo;
    strcpy(ATAdm->base.nome, nome);
    strcpy(ATAdm->base.cpf, cpf);
    strcpy(ATAdm->base.data_nascimento, data_nascimento);
    ATAdm->verificacao = true;
    return ATAdm;
}

void salvaAdministrador(TAdm *adm, FILE *out){
    fwrite(&adm->codigo, sizeof(int), 1, out);
    //adm->nome ao inves de &adm->nome, pois string ja eh um ponteiro
    fwrite(adm->base.nome, sizeof(char), sizeof(adm->base.nome), out);
    fwrite(adm->base.cpf, sizeof(char), sizeof(adm->base.cpf), out);
    fwrite(adm->base.data_nascimento, sizeof(char), sizeof(adm->base.data_nascimento), out);
    fwrite(&adm->verificacao, sizeof(bool), 1, out);
}

int tamanho_arquivo_administrador(FILE *arq){
    fseek(arq, 0, SEEK_END);
    int tam = trunc(ftell(arq) / tamanho_registro());
    return tam;
}

TAdm *leAdministrador(FILE *in){
    TAdm *adm = (TAdm *) malloc(sizeof(TAdm));
    if (0 >= fread(&adm->codigo, sizeof(int), 1, in)) {
        free(adm);
        return NULL;
    }
    fread(adm->base.nome, sizeof(char), sizeof(adm->base.nome), in);
    fread(adm->base.cpf, sizeof(char), sizeof(adm->base.cpf), in);
    fread(adm->base.data_nascimento, sizeof(char), sizeof(adm->base.data_nascimento), in);
    fread(&adm->verificacao, sizeof(bool), 1, in);
    return adm;
}

// Imprime funcionario
void imprimeAdministrador(TAdm *adm){
    printf("**********************************************");
    printf("\nAdministrador de codigo ");
    printf("%d", adm->codigo);
    printf("\nNome: ");
    printf("%s", adm->base.nome);
    printf("\nCPF: ");
    printf("%s", adm->base.cpf);
    printf("\nData de Nascimento: ");
    printf("%s", adm->base.data_nascimento);
    printf("\nVerificacao: ");
    printf("%s", adm->verificacao ? "Ativo" : "Inativo");
    printf("\n**********************************************");
}

// Criar a base de dados
void criarBaseAdministrador(FILE *out, int tam){
    int vet[tam];
    TAdm *a;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;
    
    //embaralha(vet,tam);

    printf("\nGerando a base de dados...\n");

    for (int i=0;i<tam;i++){
        a = administrador(vet[i], "A", "000.000.000-00", "01/01/1980", true);
        salvaAdministrador(a, out);
    }

    free(a);
}

// Embaralha a base de dados
void embaralhaAdministrador(int *vet, int tam){
    int tmp;

    srand(time(NULL));

    int trocas = (tam*60)/100;

    for (int t = 1; t<trocas; t++) {
        int i = rand() % tam;
        int j = rand() % tam;
        tmp = vet[i];
        vet[i] = vet[j];
        vet[j] = tmp;
    }
}

void shuffle(int *vet,int MAX,int MIN) {
    srand(time(NULL));
    for (int i = MAX - MIN - 1; i > 0; i--) {
        int j = rand() % (i);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}

void imprimirBase(FILE *out){
    printf("\nImprimindo a base de dados...\n");

    rewind(out);
    TAdm *a;

    while ((a = leAdministrador(out)) != NULL)
        imprimeAdministrador(a);

    free(a);

}

int compara(TAdm *c1, TAdm *c2)
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
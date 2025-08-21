#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "administrador.h"
#include "candidato.h"
#include "eleitor.h"

int tamanho_registro_administrador(){
    return sizeof(int)
           + sizeof(char) * 50
           + sizeof(char) * 15
           + sizeof(char) * 11
           + sizeof(bool);
}

TAdm *administrador(int codigo, char *nome, char *cpf, char *data_nascimento, bool verificacao){
    TAdm *ATAdm = (TAdm *) malloc(sizeof(TAdm));
    if (ATAdm) memset(ATAdm, 0, sizeof(TAdm)); 
    else {
        printf("Erro ao alocar memoria para o administrador\n");
        return NULL;
    }
    ATAdm->codigo = codigo;
    strcpy(ATAdm->base.nome, nome);
    strcpy(ATAdm->base.cpf, cpf);
    strcpy(ATAdm->base.data_nascimento, data_nascimento);
    ATAdm->verificacao = verificacao;
    return ATAdm;
}

void inicializar_adm_padrao() {
    TAdm *adm_teste = autenticar_administrador(1);

    if (adm_teste == NULL) {
        FILE *saida = fopen("Data/administradores.dat", "ab");
        if (saida == NULL) {
            printf("Erro: Não foi possível criar/abrir o arquivo de administradores.\n");
            exit(1); 
        }
        TAdm *adm_padrao = administrador(1, "admin", "000.000.000-00", "00/00/0000", true);
        salvaAdministrador(adm_padrao, saida);

        free(adm_padrao);
        fclose(saida);
    } else {
        free(adm_teste);
    }
}

void salvaAdministrador(TAdm *adm, FILE *out){
    fwrite(&adm->codigo, sizeof(int), 1, out);
    fwrite(adm->base.nome, sizeof(char), sizeof(adm->base.nome), out);
    fwrite(adm->base.cpf, sizeof(char), sizeof(adm->base.cpf), out);
    fwrite(adm->base.data_nascimento, sizeof(char), sizeof(adm->base.data_nascimento), out);
    fwrite(&adm->verificacao, sizeof(bool), 1, out);
}

int tamanho_arquivo_administrador(FILE *arq){
    fseek(arq, 0, SEEK_END);
    int tam = trunc(ftell(arq) / tamanho_registro_administrador());
    rewind(arq);
    return tam;
}

TAdm *leAdministrador(FILE *in){
    TAdm *adm = (TAdm *) malloc(sizeof(TAdm));
    if (fread(&adm->codigo, sizeof(int), 1, in) <= 0) {
        free(adm);
        return NULL;
    }
    fread(adm->base.nome, sizeof(char), sizeof(adm->base.nome), in);
    fread(adm->base.cpf, sizeof(char), sizeof(adm->base.cpf), in);
    fread(adm->base.data_nascimento, sizeof(char), sizeof(adm->base.data_nascimento), in);
    fread(&adm->verificacao, sizeof(bool), 1, in);
    return adm;
}

void imprimeAdministrador(TAdm *adm){
    printf("__________________________________________________");
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
    printf("\n__________________________________________________\n");
}

void criarBaseAdministrador(FILE *out, int tam){
    int vet[tam];
    TAdm *a;

    for(int i = 0; i < tam;  i++)
        vet[i] = i+1;

    shuffleAdministrador(vet, tam, 0);
    printf("\nGerando a base de dados...\n");

    for (int i = 0;i < tam; i++){
        a = administrador(vet[i], "A", "000.000.000-00", "01/01/1980", true);
        salvaAdministrador(a, out);
        free(a);
    }

}

void shuffleAdministrador(int *vet,int MAX,int MIN) {
    for (int i = MAX - MIN - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}

void imprimirBaseAdministrador(FILE *out){
    printf("\nImprimindo a base de dados...\n");
    rewind(out);
    TAdm *a;
    while ((a = leAdministrador(out)) != NULL) {
        imprimeAdministrador(a);
        free(a);
    } 
}

TAdm* autenticar_administrador(int codigo) {
    FILE *arq = fopen("Data/administradores.dat", "rb");
    if (arq == NULL) return NULL;

    TAdm *adm_lido;
    while ((adm_lido = leAdministrador(arq)) != NULL) {
        if (adm_lido->codigo == codigo && adm_lido->verificacao == true) {
            fclose(arq);
            return adm_lido;
        }
        free(adm_lido);
    }
    fclose(arq);
    return NULL;
}

int comparaAdministrador(TAdm *c1, TAdm *c2)
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

void adicionar_administrador(TAdm *novo_adm) {
    FILE *arq_adm = fopen("Data/administradores.dat", "rb");
    
    if (arq_adm != NULL) {
        TAdm *adm_lido;
        while ((adm_lido = leAdministrador(arq_adm)) != NULL) {
            if (adm_lido->codigo == novo_adm->codigo) {
                printf("Erro: o código %d já pertence a outro administrador\n", novo_adm->codigo);
                free(adm_lido);
                fclose(arq_adm);
                return;
            }
            if (strcmp(adm_lido->base.cpf, novo_adm->base.cpf) == 0) {
                printf("Erro: o CPF '%s' já está cadastrado\n", novo_adm->base.cpf);
                free(adm_lido);
                fclose(arq_adm);
                return;
            }
            free(adm_lido);
        }
        fclose(arq_adm);
    }
    arq_adm = fopen("Data/administradores.dat", "ab");
    if (arq_adm == NULL) {
        printf("Erro ao abrir o arquivo para adicionar administrador\n");
        return;
    }

    salvaAdministrador(novo_adm, arq_adm);
    fclose(arq_adm);

    printf("Administrador com código %d adicionado com sucesso!\n", novo_adm->codigo);
}

void remover_administrador(int codigo_adm_logado, int codigo_remover) {
    if (codigo_remover == codigo_adm_logado) {
        printf("Erro: Você não pode remover a si mesmo\n");
        return;
    }

    FILE *arq_origem = fopen("Data/administradores.dat", "rb");
    if (arq_origem == NULL) {
        printf("Erro: Arquivo de administradores não encontrado\n");
        return;
    }

    FILE *arq_temp = fopen("Data/temp_admin.dat", "wb");
    if (arq_temp == NULL) {
        printf("Erro ao criar arquivo temporário\n");
        fclose(arq_origem);
        return;
    }

    TAdm *adm_lido;
    int encontrado = 0;
    while ((adm_lido = leAdministrador(arq_origem)) != NULL) {
        if (adm_lido->codigo == codigo_remover) {
            encontrado = 1;
        } else {
            salvaAdministrador(adm_lido, arq_temp);
        }
        free(adm_lido);
    }

    fclose(arq_origem);
    fclose(arq_temp);

    if (encontrado) {
        remove("Data/administradores.dat");
        rename("Data/temp_admin.dat", "Data/administradores.dat");
        printf("Administrador removido com sucesso\n");
    } else {
        remove("Data/temp_admin.dat");
        printf("Administrador com código %d não encontrado\n", codigo_remover);
    }
}

int editar_administrador(int codigo_editar, TAdm *dados_novos) {
    FILE *arq = fopen("Data/administradores.dat", "r+b");
    if (arq == NULL) {
        printf("Erro: Falha ao abrir o arquivo de administradores.\n");
        return 0; 
    } 

    TAdm *adm_lido;
    int encontrado = 0;
    long pos = 0;

    while (pos = ftell(arq), (adm_lido = leAdministrador(arq)) != NULL) {
        if (adm_lido->codigo == codigo_editar) {
            strcpy(adm_lido->base.nome, dados_novos->base.nome);
            strcpy(adm_lido->base.data_nascimento, dados_novos->base.data_nascimento);
            adm_lido->verificacao = dados_novos->verificacao;

            fseek(arq, pos, SEEK_SET);
            salvaAdministrador(adm_lido, arq);
            
            encontrado = 1;
            free(adm_lido);
            break;
        }
        free(adm_lido);
    }

    fclose(arq);
    return encontrado;
}
void adicionar_candidato(TCandidato *novo_candidato) {
    FILE *arq_cand = fopen("Data/candidatos.dat", "ab");
    if (arq_cand == NULL) {
        printf("Erro ao abrir o arquivo para adicionar candidato\n");
        return;
    }

    salvaCandidato(novo_candidato, arq_cand);
    fclose(arq_cand);

    printf("Candidato com codigo %d adicionado ao arquivo com sucesso!\n", novo_candidato->codigo);
}

void remover_candidato(int codigo_remover) {
    FILE *arq_origem = fopen("Data/candidatos.dat", "rb");
    if (arq_origem == NULL) {
        printf("Erro: Arquivo de candidatos não encontrado\n");
        return;
    }

    FILE *arq_temp = fopen("Data/temp_cand.dat", "wb");
    if (arq_temp == NULL) {
        printf("Erro ao criar arquivo temporário\n");
        fclose(arq_origem);
        return;
    }

    TCandidato *cand_lido;
    int encontrado = 0;
    while ((cand_lido = leCandidato(arq_origem)) != NULL) {
        if (cand_lido->codigo == codigo_remover) {
            encontrado = 1;
        } else {
            salvaCandidato(cand_lido, arq_temp);
        }
        free(cand_lido);
    }

    fclose(arq_origem);
    fclose(arq_temp);

    if (encontrado) {
        remove("Data/candidatos.dat");
        rename("Data/temp_cand.dat", "Data/candidatos.dat");
        printf("Candidato removido com sucesso.\n");
    } else {
        remove("Data/temp_cand.dat");
        printf("Candidato com código %d não encontrado\n", codigo_remover);
    }
}

int editar_candidato(int codigo_editar, TCandidato *dados_novos) {
    FILE *arq = fopen("Data/candidatos.dat", "r+b");
    if (arq == NULL) {
        printf("Erro: Falha ao abrir o arquivo de candidatos.\n");
        return 0;
    }

    TCandidato *cand_lido;
    int encontrado = 0;
    long pos = 0;

    while (pos = ftell(arq), (cand_lido = leCandidato(arq)) != NULL) {
        if (cand_lido->codigo == codigo_editar) {
            strcpy(cand_lido->base.nome, dados_novos->base.nome);
            strcpy(cand_lido->base.data_nascimento, dados_novos->base.data_nascimento);
            strcpy(cand_lido->cargo, dados_novos->cargo);
            strcpy(cand_lido->partido, dados_novos->partido);

            fseek(arq, pos, SEEK_SET);
            salvaCandidato(cand_lido, arq);
            
            encontrado = 1;
            free(cand_lido);
            break;
        }
        free(cand_lido);
    }

    fclose(arq);
    return encontrado;
}

void adicionar_eleitor(TEleitor *novo_eleitor) {
    FILE *arq_eleitor = fopen("Data/eleitores.dat", "rb");

    if (arq_eleitor != NULL) {
        TEleitor *eleitor_lido;
        while ((eleitor_lido = leEleitor(arq_eleitor)) != NULL) {
            if (eleitor_lido->codigo == novo_eleitor->codigo) {
                printf("Erro: o código %d já pertence a outro eleitor\n", novo_eleitor->codigo);
                free(eleitor_lido);
                fclose(arq_eleitor);
                return;
            }
            if (strcmp(eleitor_lido->base.cpf, novo_eleitor->base.cpf) == 0) {
                printf("Erro: o CPF '%s' já está cadastrado\n", novo_eleitor->base.cpf);
                free(eleitor_lido);
                fclose(arq_eleitor);
                return;
            }
            if (strcmp(eleitor_lido->titulo_eleitor, novo_eleitor->titulo_eleitor) == 0) {
                printf("Erro: o Título de Eleitor '%s' já está cadastrado\n", novo_eleitor->titulo_eleitor);
                free(eleitor_lido);
                fclose(arq_eleitor);
                return;
            }
            free(eleitor_lido);
        }
        fclose(arq_eleitor);
    }
    arq_eleitor = fopen("Data/eleitores.dat", "ab");
    if (arq_eleitor == NULL) {
        printf("Erro ao abrir o arquivo para adicionar eleitor\n");
        return;
    }

    salvaEleitor(novo_eleitor, arq_eleitor);
    fclose(arq_eleitor);

    printf("Eleitor '%s' (código %d) adicionado com sucesso!\n", novo_eleitor->base.nome, novo_eleitor->codigo);
}

void remover_eleitor(int codigo_remover) {
    FILE *arq_origem = fopen("Data/eleitores.dat", "rb");
    if (arq_origem == NULL) {
        printf("Erro: Arquivo de eleitores não encontrado\n");
        return;
    }

    FILE *arq_temp = fopen("Data/temp_eleitor.dat", "wb");
    if (arq_temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(arq_origem);
        return;
    }

    TEleitor *eleitor_lido;
    int encontrado = 0;
    while ((eleitor_lido = leEleitor(arq_origem)) != NULL) {
        if (eleitor_lido->codigo == codigo_remover) {
            encontrado = 1;
            printf("Eleitor '%s' (código %d) encontrado e marcado para remoção.\n", eleitor_lido->base.nome, eleitor_lido->codigo);
        } else {
            salvaEleitor(eleitor_lido, arq_temp);
        }
        free(eleitor_lido);
    }

    fclose(arq_origem);
    fclose(arq_temp);

    if (encontrado) {
        remove("Data/eleitores.dat");
        rename("Data/temp_eleitor.dat", "Data/eleitores.dat");
        printf("Eleitor removido com sucesso.\n");
    } else {
        remove("Data/temp_eleitor.dat");
        printf("Eleitor com código %d não encontrado.\n", codigo_remover);
    }
}

int editar_eleitor(int codigo_editar, TEleitor *dados_novos) {
    FILE *arq = fopen("Data/eleitores.dat", "r+b");
    if (arq == NULL) {
        printf("Erro: Falha ao abrir o arquivo de eleitores.\n");
        return 0;
    }

    TEleitor *eleitor_lido;
    int encontrado = 0;
    long pos = 0;

    while (pos = ftell(arq), (eleitor_lido = leEleitor(arq)) != NULL) {
        if (eleitor_lido->codigo == codigo_editar) {
            strcpy(eleitor_lido->base.nome, dados_novos->base.nome);
            strcpy(eleitor_lido->base.data_nascimento, dados_novos->base.data_nascimento);
            strcpy(eleitor_lido->secao, dados_novos->secao);
            strcpy(eleitor_lido->zona, dados_novos->zona);

            fseek(arq, pos, SEEK_SET);
            salvaEleitor(eleitor_lido, arq);
            
            encontrado = 1;
            free(eleitor_lido);
            break;
        }
        free(eleitor_lido);
    }

    fclose(arq);
    return encontrado;
}
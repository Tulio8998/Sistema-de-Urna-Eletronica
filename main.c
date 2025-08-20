#include <stdio.h>
#include "Util/util.h"
#include "Menu/menuConsole.h"
#include "Entities/administrador.h"
#include "Selecao/selecaoSubstituicao.h"
#include "Intercalacao/arvoreVencedores.h"
#include "Hash/hash.h"   

int main() {

#ifdef _WIN32
    system("chcp 65001");
#endif    

    init_random();

    FILE *log = fopen("Data/log.txt", "a");
    if (log == NULL) {
        perror("Erro: Nao foi possivel criar o arquivo de log.");
    }

    FILE *arq_cand = fopen("Data/candidatos.dat", "rb");
    if (arq_cand == NULL) {
        arq_cand = fopen("Data/candidatos.dat", "w+b");
        if (arq_cand != NULL) {
            criarBaseCandidato(arq_cand, 1000);
            fclose(arq_cand);
        }
    } else {
        fclose(arq_cand);
    }

    FILE *arq_elei = fopen("Data/eleitores.dat", "rb");
    if (arq_elei == NULL) {
        arq_elei = fopen("Data/eleitores.dat", "wb");
        if (arq_elei != NULL) {
            criarBaseEleitor(arq_elei, 1000);
            fclose(arq_elei);
        }
    } else {
        fclose(arq_elei);
    }

    inicializar_adm_padrao();

    // USO DA HASH
    inicializarTabela();

    inserir(101, "Joao");
    inserir(202, "Maria");
    inserir(303, "Carlos");

    imprimirTabela();

    char *res = buscar(202);
    if (res != NULL)
        printf("Encontrado: %s\n", res);
    else
        printf("Nao encontrado!\n");

    remover(101);
    imprimirTabela();

    iniciar_menu_console();
    fclose(log);

    return 0;
}

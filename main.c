#include <stdio.h>
#include "Util/util.h"
#include "Menu/menuConsole.h"
#include "Entities/administrador.h"
#include "Selecao/selecaoSubstituicao.h"

int main() {

#ifdef _WIN32
    system("chcp 65001");
#endif    

    init_random();

    FILE *arq_cand = fopen("Data/candidatos.dat", "rb");
    if (arq_cand == NULL) {
        arq_cand = fopen("Data/candidatos.dat", "w+b");
        if (arq_cand != NULL) {
            criarBaseCandidato(arq_cand, 1000);
            selecaoPorSubstituicao(arq_cand);
        }
    } else {
        selecaoPorSubstituicao(arq_cand);
    }
    if (arq_cand != NULL) {
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
    selecaoPorSubstituicao(arq_cand);
    fclose(arq_cand);
    iniciar_menu_console();
        
    return 0;
}
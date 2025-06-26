#include <stdio.h>
#include "Util/util.h"
#include "Menu/menuConsole.h"
#include "Entities/administrador.h"

int main() {

#ifdef _WIN32
    system("chcp 65001");
#endif    

    init_random();

    FILE *arq_cand = fopen("Data/candidatos.dat", "rb");
    if (arq_cand == NULL) {
        arq_cand = fopen("Data/candidatos.dat", "wb");
        if (arq_cand != NULL) {
            criarBaseCandidato(arq_cand, 10);
            fclose(arq_cand);
        }
    } else {
        fclose(arq_cand);
    }

    FILE *arq_elei = fopen("Data/eleitores.dat", "rb");
    if (arq_elei == NULL) {
        arq_elei = fopen("Data/eleitores.dat", "wb");
        if (arq_elei != NULL) {
            criarBaseEleitor(arq_elei, 10);
            fclose(arq_elei);
        }
    } else {
        fclose(arq_elei);
    }
    
    inicializar_adm_padrao();
    iniciar_menu_console();
        
    return 0;
}
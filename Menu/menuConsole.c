#include <stdio.h>
#include <stdlib.h>
#include "menuConsole.h"
#include "menuAdm.h"
#include "menuEleitor.h"
#include "../Entities/administrador.h"
#include "../Entities/eleitor.h"

void iniciar_menu_console() {
    int opcao;
    do {
        printf("\n\nSISTEMA DE URNA ELETRONICA\n");
        printf("1. Login como Administrador\n");
        printf("2. Login como Eleitor\n");
        printf("0. Sair do Sistema\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int codigo;
            printf("Digite seu codigo de administrador: ");
            scanf("%d", &codigo);
            
            TAdm *adm = autenticar_administrador(codigo);
            if (adm != NULL) {
                iniciar_menu_adm(adm);
                free(adm);
            } else {
                printf("Codigo de administrador nao encontrado ou inativo.\n");
            }

        } else if (opcao == 2) {
            char titulo[20];
            printf("Digite seu Titulo de Eleitor: ");
            scanf(" %[^\n]", titulo);

            TEleitor* eleitor = autenticar_eleitor(titulo);
            if (eleitor != NULL) {
                iniciar_menu_eleitor(eleitor);
                free(eleitor);
            } else {
                printf("Titulo de eleitor não encontrado.\n");
            }
        }

    } while (opcao != 0);

    printf("Encerrando o sistema...\n");
}
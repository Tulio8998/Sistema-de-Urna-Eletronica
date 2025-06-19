#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Entities/administrador.h"
#include "Entities/candidato.h"
#include "Entities/eleitor.h"
#include "Buscas/buscaSequencial.h"
#include "Buscas/buscaBinaria.h"

int main () {
#ifdef _WIN32
    system("chcp 65001");
#endif

    FILE *arq;
    FILE *out;
    FILE *log;

    TAdm *a, *g;
    int qtdparticoes;
    
    if ((log = fopen("log.txt", "a+")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    if ((arq = fopen("administradores.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    } else {

        criarBaseAdministrador(arq, 5);
        imprimirBase(arq);

        printf("\n\n\nORDENANDO ORDENANDO ORDENANDO ORDENANDO ORDENANDO ORDENANDO ORDENANDO\n\n\n");
        system("pause");


        printf("\nBusca sequecial\n");
        a = buscaSequencialAdministrador(1, arq, log);
        imprimeAdministrador(a);

        /*
        printf("\nBusca binaria\n");
        a = buscaBinariaAdministrador(1, arq, 0, tamanho_arquivo_administrador(arq) - 1, log);
        imprimeAdministrador(a);
        */
    }

    fclose(arq);
    fclose(log);

    return 0;
}
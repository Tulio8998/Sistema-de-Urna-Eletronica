#include "Entities/administrador.h"
#include "Entities/candidato.h"
#include "Entities/eleitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
        
    }



    
    return 0;
}
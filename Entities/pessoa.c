#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pessoa.h"

int calcularIdade(char *data_nascimento) {
    int dia, mes, ano;
    sscanf(data_nascimento, "%d/%d/%d", &dia, &mes, &ano);

    time_t t = time(NULL);
    struct tm tm_atual = *localtime(&t);

    int idade = tm_atual.tm_year + 1900 - ano;

    if (tm_atual.tm_mon + 1 < mes || 
       (tm_atual.tm_mon + 1 == mes && tm_atual.tm_mday < dia)) {
        idade--;
    }

    return idade;
}

int ehMaiorIdade(char *data_nascimento) {
    return calcularIdade(data_nascimento) >= 18;
}

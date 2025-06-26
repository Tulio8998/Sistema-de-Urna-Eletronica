#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Entities/administrador.h"
#include "../Entities/candidato.h"
#include "../Entities/eleitor.h"

const char *FIRST_NAMES[] = {
    "Jorge", "Joao", "Henrique", "Gustavo", "Guilherme", "Ornofre", "Ian",
    "Gabriel", "Cleiton", "Sergio", "Lucas", "Pedro", "Matheus", "Rafael", "Felipe", "Bruno", "Tiago",
    "Leonardo", "Daniel", "Carlos", "Vinicius", "Andre", "Marcelo", "Victor", "Ricardo", "Eduardo", "Fernando",
    "Roberto", "Alexandre", "Diego", "Antonio", "Murilo", "Leandro", "Rodrigo", "Marcos", "Wesley", "Fabio",
    "Douglas", "Igor", "Xamuel", "Jose", "William", "Nathan", "Thiago", "Everton", "Kleber", "Elton", "Luis",
    "Alex", "Cristiano", "Francisco", "Marlon", "Brayan", "Alan", "Geovanni", "Julio", "Jair", "Erick", "Edson",
    "Ronaldo", "Caio", "Otavio", "Vitor", "Afonso", "Angelo", "Matias", "Artur", "Bernardo", "Davi", "Enzo",
    "Frederico", "Heitor", "Joaquim", "Lorenzo", "Miguel", "Noah", "Benjamin", "Vicente", "Nicolas", "Tomás",
    "Alberto", "Augusto", "Sandro", "Raul", "Renato", "Sandro", "Sandro", "Rafael", "Sebastião", "Teodoro",
    "Valentim", "Walter", "Xavier", "Yuri", "Zeca", "Cesar", "Enrico", "Geraldo", "Gilberto", "Jean"
};

const char *LAST_NAMES[] = {
    "Silva", "Santos", "Oliveira", "Souza", "Pereira", "Costa",
    "Rodrigues", "Almeida", "Nascimento", "Lima", "Araújo", "Fernandes", "Carvalho", "Gomes", "Martins",
    "Rocha", "Ribeiro", "Alves", "Monteiro", "Mendes", "Barros", "Freitas", "Barbosa", "Pinto", "Correia",
    "Moreira", "Cardoso", "Teixeira", "Cavalcanti", "Dias", "Castro", "Campos", "Moura", "Peixoto", "Andrade",
    "Leal", "Vieira", "Santana", "Machado", "Duarte", "Ramos", "Freire", "Amaral", "Tavares", "Matos",
    "Azevedo", "Braga", "Cunha", "Farias", "Lopes", "Macedo", "Nogueira", "Reis", "Xavier", "Branco", "Fonseca",
    "Pacheco", "Neves", "Borges", "Siqueira", "Moraes", "Mello", "Guimaraes", "Figueiredo", "Sales", "Viana",
    "Monteiro", "Ferreira", "Vargas", "Vasconcelos", "Aguiar", "Soares", "Batista", "Parreira", "Campos",
    "Assis", "Domingues", "Aragao", "Bezerra", "Bittencourt", "Carmo", "Chaves", "Coelho", "Diniz", "Espindola",
    "Esteves", "Falcao", "Farias", "Franco", "Gama", "Garcia", "Henriques", "Lacerda", "Lourenco", "Magalhaes",
    "Medeiros", "Meireles", "Meneses", "Mesquita", "Miranda"
};

const char *PARTIDOS[] = {
    "MDB", "PDT", "PT", "PCdoB","PSB","PSDB","AGIR","MOBILIZA","CIDADANIA","AVANTE","MBL"
};

const char *CARGOS[] = {
    "CIVIL", "SENADOR", "DEPUTADO", "GOVERNADOR", "PRESIDENTE"
};

void init_random() {
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned int)time(NULL));
        initialized = 1;
    }
}

void gerarNome(char *dest, size_t size) {
    int first = rand() % (sizeof(FIRST_NAMES)/sizeof(FIRST_NAMES[0]));
    int last = rand() % (sizeof(LAST_NAMES)/sizeof(LAST_NAMES[0]));
    snprintf(dest, size, "%s %s", FIRST_NAMES[first], LAST_NAMES[last]);
}

void gerarCargo(char *dest, size_t size) {
    int pesos[] = {95, 90, 70, 20, 5};
    int totalPeso = 0;
    for (int i = 0; i < 5; i++) totalPeso += pesos[i];
    int valorAleatorio = (rand() % totalPeso) + 1;
    int acumulado = 0;
    for (int i = 0; i < 5; i++) {
        acumulado += pesos[i];
        if (valorAleatorio <= acumulado) {
            strncpy(dest, CARGOS[i], size-1);
            dest[size-1] = '\0';
            return;
        }
    }
    strncpy(dest, "CIVIL", size-1);
    dest[size-1] = '\0';
}

void gerarPartido(char *dest, size_t size) {
    int idx = rand() % (sizeof(PARTIDOS)/sizeof(PARTIDOS[0]));
    strncpy(dest, PARTIDOS[idx], size-1);
    dest[size-1] = '\0';
}

void gerarCPF(char *cpf) {
    int i;
    int numeros[11];

    for (i = 0; i < 11; i++) {
        numeros[i] = rand() % 10;
    }

    sprintf(cpf, "%d%d%d.%d%d%d.%d%d%d-%d%d",
            numeros[0], numeros[1], numeros[2],
            numeros[3], numeros[4], numeros[5],
            numeros[6], numeros[7], numeros[8],
            numeros[9],numeros[10]);
}

void gerarData(char *data) {
    int dia = 1 + rand() % 28;   
    int mes = 1 + rand() % 12;
    int ano = 1970 + rand() % 30;  

    sprintf(data, "%02d/%02d/%d", dia, mes, ano);
}

void gerarSecao(char *secao) {
    int sec = 1 + rand() % 50;   
    sprintf(secao, "%d", sec);
}

void gerarZona(char *zona) {
    int zon = 1 + rand() % 50;   
    sprintf(zona, "%d", zon);
}

void gerarTitulo(char *titulo) {
    int tit = 1000 + rand() % 9999;   
    sprintf(titulo, "%d", tit);
}

TCandidato generateRandomUserCand(int codigo) {
    TCandidato c;
    c.codigo = codigo;
    gerarNome(c.base.nome, sizeof(c.base.nome));
    gerarCargo(c.cargo, sizeof(c.cargo));
    gerarCPF(c.base.cpf);
    gerarData(c.base.data_nascimento);
    gerarPartido(c.partido, sizeof(c.partido));
    return c;
}      

TEleitor generateRandomUserElei(int codigo) {
    TEleitor e;
    e.codigo = codigo;
    gerarNome(e.base.nome, sizeof(e.base.nome));
    gerarTitulo(e.titulo_eleitor);
    gerarSecao(e.secao);
    gerarZona(e.zona);
    gerarCPF(e.base.cpf);
    gerarData(e.base.data_nascimento);
    return e;
}   
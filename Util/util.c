
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *FIRST_NAMES[] = {
    "Jorge", "Joao", "Henrique", "Gustavo", "Guilherme", "Ornofre", "Ian",
    "Gabriel", "Cleiton", "Sergio", "Lucas", "Pedro", "Matheus", "Rafael", "Felipe", "Bruno", "Tiago",
    "Leonardo", "Daniel", "Carlos", "Vinicius", "Andre", "Marcelo", "Victor", "Ricardo", "Eduardo", "Fernando",
    "Roberto", "Alexandre", "Diego", "Antonio", "Murilo", "Leandro", "Rodrigo", "Marcos", "Wesley", "Fabio",
    "Douglas", "Igor", "Samuel", "Jose", "William", "Nathan", "Thiago", "Everton", "Kleber", "Elton", "Luis",
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

typedef struct {
    int id;
    char nome[100];
    char partido[20];
    char cargo[20];
} Candidato;

static void init_random() {
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned int)time(NULL));
        initialized = 1;
    }
}

static void gerarNome(char *dest, size_t size) {
    int first = rand() % (sizeof(FIRST_NAMES)/sizeof(FIRST_NAMES[0]));
    int last = rand() % (sizeof(LAST_NAMES)/sizeof(LAST_NAMES[0]));
    snprintf(dest, size, "%s %s", FIRST_NAMES[first], LAST_NAMES[last]);
}

static void gerarCargo(char *dest, size_t size) {
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

static void gerarPartido(char *dest, size_t size) {
    int idx = rand() % (sizeof(PARTIDOS)/sizeof(PARTIDOS[0]));
    strncpy(dest, PARTIDOS[idx], size-1);
    dest[size-1] = '\0';
}

Candidato generateRandomUser() {
    init_random();
    Candidato c;
    c.id = 0;
    gerarNome(c.nome, sizeof(c.nome));
    gerarCargo(c.cargo, sizeof(c.cargo));
    if (strcmp(c.cargo, "CIVIL") == 0) {
        c.partido[0] = '\0';
    } else {
        gerarPartido(c.partido, sizeof(c.partido));
    }
    return c;
}
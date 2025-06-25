#ifndef CANDIDATO_H
#define CANDIDATO_H

// Definição da estrutura Candidato
typedef struct {
    int id;
    char nome[100];
    char partido[20];
    char cargo[20];
} Candidato;

// Função para inicializar o gerador de números aleatórios
void init_random(void);

// Geração de nome aleatório (primeiro e último)
void gerarNome(char *dest, size_t size);

// Geração de cargo aleatório com pesos
void gerarCargo(char *dest, size_t size);

// Geração de partido aleatório
void gerarPartido(char *dest, size_t size);

// Gera um candidato aleatório
Candidato generateRandomUser(void);

#endif // CANDIDATO_H

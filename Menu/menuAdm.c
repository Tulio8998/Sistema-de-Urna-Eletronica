#include <stdio.h>
#include <stdlib.h>
#include "menuAdm.h"
#include "../Entities/administrador.h"
#include "../Entities/candidato.h"     
#include "../Entities/eleitor.h"       
#include "../Buscas/buscaSequencial.h"
#include "../Buscas/buscaBinaria.h"
#include "../Ordenacao/quickSortEmDisco.h"

void iniciar_menu_adm(TAdm *adm_logado) {
    int opcao1;
    printf("\nBem-vindo, Administrador %s!", adm_logado->base.nome);

    do {
        printf("\n\nMenu do Administrador\n");
        printf("1. Gerenciar Eleitores\n");
        printf("2. Gerenciar Candidatos\n");
        printf("3. Gerenciar Administradores\n");
        printf("4. Gerar Relatórios\n");
        printf("0. Deslogar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao1);

        switch (opcao1) {
            case 1: {
                int opcao; 
                do {    
                    printf("GERENCIADOR DE ELEITORES\n");
                    printf("1. Adicionar Eleitor\n");
                    printf("2. Editar Eleitor\n");
                    printf("3. Remover Eleitor\n");
                    printf("4. Imprimir todos os Eleitores\n");
                    printf("5. Pesquisar Eleitor...\n");
                    printf("6. Preparar arquivo para busca rápida (Ordenar)\n");
                    printf("0. Voltar ao Menu Principal\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &opcao);
                    switch (opcao) {
                    case 1: {
                        TEleitor novo_eleitor;
                        printf("Digite o código do novo eleitor: ");
                        scanf("%d", &novo_eleitor.codigo);
                        printf("Digite o nome: ");
                        scanf(" %[^\n]", novo_eleitor.base.nome);
                        printf("Digite o CPF: ");
                        scanf(" %[^\n]", novo_eleitor.base.cpf);
                        printf("Digite a data de nascimento (DD/MM/AAAA): ");
                        scanf(" %[^\n]", novo_eleitor.base.data_nascimento);
                        printf("Digite o Título de Eleitor: ");
                        scanf(" %[^\n]", novo_eleitor.titulo_eleitor);
                        printf("Digite a Seção: ");
                        scanf(" %[^\n]", novo_eleitor.secao);
                        printf("Digite a Zona: ");
                        scanf(" %[^\n]", novo_eleitor.zona);
                        adicionar_eleitor(&novo_eleitor);
                        break;
                    }
                    case 2:{
                        int codigo_eleitor;
                        printf("Digite o código do eleitor a ser editado: ");
                        scanf("%d", &codigo_eleitor);
                        
                        TEleitor dados_novos;
                        printf("Digite o novo nome: ");
                        scanf(" %[^\n]", dados_novos.base.nome);
                        printf("Digite a nova data de nascimento: ");
                        scanf(" %[^\n]", dados_novos.base.data_nascimento);
                        printf("Digite a nova seção: ");
                        scanf(" %[^\n]", dados_novos.secao);
                        printf("Digite a nova zona: ");
                        scanf(" %[^\n]", dados_novos.zona);

                        if (editar_eleitor(codigo_eleitor, &dados_novos)) {
                            printf("\nEleitor atualizado com sucesso!\n");
                        } else {
                            printf("\nFalha na atualização. Eleitor não encontrado.\n");
                        }
                        break;
                    }
                    case 3:{
                        int codigo_remover;
                        printf("Digite o código do eleitor a ser removido: ");
                        scanf("%d", &codigo_remover);
                        remover_eleitor(codigo_remover);
                        break;
                    }
                    case 4: {
                        FILE *arq = fopen("Data/eleitores.dat", "rb");
                        if (arq == NULL) {
                            printf("Nenhum eleitor cadastrado.\n");
                            break;
                        }
                        imprimirBaseEleitor(arq);
                        fclose(arq);
                        break;
                        }
                    case 5: {
                        int opcao_busca, codigo_busca;
                        FILE *log_busca = fopen("Data/log.txt", "a");

                        printf("\nPesquisa de Eleitores\n");
                        printf("1. Busca Sequencial (lenta, mas sempre funciona)\n");
                        printf("2. Busca Binária (rápida, requer arquivo ordenado)\n");
                        printf("0. Voltar\n");
                        printf("Escolha o tipo de busca: ");
                        scanf("%d", &opcao_busca);
                        if (opcao_busca == 0) break;

                        printf("Digite o código do eleitor a ser buscado: ");
                        scanf("%d", &codigo_busca);

                        if (opcao_busca == 1) {
                            FILE *arq_seq = fopen("Data/eleitores.dat", "rb");
                            if (!arq_seq) {
                                printf("Erro ao abrir 'eleitores.dat'\n");
                            } else {
                                TEleitor *encontrado = buscaSequencialEleitor(codigo_busca, arq_seq, log_busca);
                                if (encontrado) {
                                    printf("Eleitor encontrado:\n");
                                    imprimeEleitor(encontrado);
                                    free(encontrado);
                                } else {
                                    printf("Eleitor com código %d não encontrado.\n", codigo_busca);
                                }
                                fclose(arq_seq);
                            }
                        } else if (opcao_busca == 2) {
                            FILE *arq_bin = fopen("Data/eleitores_ordenado.dat", "rb");
                            if (!arq_bin) {
                                printf("Erro: 'eleitores_ordenado.dat' não existe. Use a opção 6 para criá-lo.\n");
                            } else {
                                int tam = tamanho_arquivo_eleitor(arq_bin);
                                TEleitor *encontrado = buscaBinariaEleitor(codigo_busca, arq_bin, 0, tam - 1, log_busca);
                                if (encontrado) {
                                    printf("Eleitor encontrado:\n");
                                    imprimeEleitor(encontrado);
                                    free(encontrado);
                                } else {
                                    printf("Eleitor com código %d não encontrado no arquivo ordenado.\n", codigo_busca);
                                }
                                fclose(arq_bin);
                            }
                        }
                        if(log_busca) fclose(log_busca);
                        break;
                    }
                case 6: {
                    const char* original_file = "Data/eleitores.dat";
                    const char* sorted_file = "Data/eleitores_ordenado.dat";

                    FILE* arq_origem = fopen(original_file, "rb");
                    if (arq_origem == NULL) {
                        printf("Erro: Arquivo de origem '%s' nao encontrado.\n", original_file);
                        break;
                    }

                    FILE* arq_destino = fopen(sorted_file, "wb");
                    if (arq_destino == NULL) {
                        printf("Erro: Nao foi possivel criar o arquivo de destino '%s'.\n", sorted_file);
                        fclose(arq_origem);
                        break;
                    }

                    char buffer[4096];
                    size_t bytes_lidos;
                    while ((bytes_lidos = fread(buffer, 1, sizeof(buffer), arq_origem)) > 0) {
                        fwrite(buffer, 1, bytes_lidos, arq_destino);
                    }
                    fclose(arq_origem);
                    fclose(arq_destino);
                
                    FILE *arq_para_ordenar = fopen(sorted_file, "r+b");
                    if (arq_para_ordenar == NULL) {
                        printf("Erro ao reabrir o arquivo '%s' para ordenacao.\n", sorted_file);
                        break;
                    }
                    printf("Iniciando ordenacao em disco de '%s'.\n", sorted_file);
                    quickSortEmDiscoEleitor(arq_para_ordenar);
                    fclose(arq_para_ordenar);
                        printf("Arquivo '%s' ordenado com sucesso.\n", sorted_file);
                        break;
                    }
                    case 0:
                        printf("Saindo...");
                        break;
                    default:
                        break;
                    }
                } while (opcao != 0);
                break;
            }
            case 2: {
                int opcao_candidato;
                do {
                    printf("\nGerenciador de Candidatos\n");
                    printf("1. Adicionar Candidato\n");
                    printf("2. Editar Candidato\n");
                    printf("3. Remover Candidato\n");
                    printf("4. Listar Todos os Candidatos\n");
                    printf("5. Pesquisar Candidato...\n");
                    printf("6. Preparar arquivo para busca rápida (Ordenar)\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &opcao_candidato);

                    switch (opcao_candidato) {
                        case 1: {
                            TCandidato novo_candidato;
                            printf("Digite o código do novo candidato: "); 
                            scanf("%d", &novo_candidato.codigo);
                            printf("Digite o nome: "); 
                            scanf(" %[^\n]", novo_candidato.base.nome);
                            printf("Digite o CPF: "); 
                            scanf(" %[^\n]", novo_candidato.base.cpf);
                            printf("Digite a data de nascimento (DD/MM/AAAA): "); 
                            scanf(" %[^\n]", novo_candidato.base.data_nascimento);
                            printf("Digite o Cargo: "); 
                            scanf(" %[^\n]", novo_candidato.cargo);
                            printf("Digite o Partido: "); 
                            scanf(" %[^\n]", novo_candidato.partido);
                            adicionar_candidato(&novo_candidato);
                            break;
                        }
                        case 2: {
                            int codigo_candidato;
                            printf("Digite o código do candidato a ser editado: ");
                            scanf("%d", &codigo_candidato);
                            
                            TCandidato dados_novos;
                            printf("Digite o novo nome: "); 
                            scanf(" %[^\n]", dados_novos.base.nome);
                            printf("Digite a nova data de nascimento: "); 
                            scanf(" %[^\n]", dados_novos.base.data_nascimento);
                            printf("Digite o novo cargo: "); 
                            scanf(" %[^\n]", dados_novos.cargo);
                            printf("Digite o novo partido: "); 
                            scanf(" %[^\n]", dados_novos.partido);

                            if (editar_candidato(codigo_candidato, &dados_novos)) {
                                printf("\nCandidato atualizado com sucesso!\n");
                            } else {
                                printf("\nFalha na atualização. Candidato não encontrado.\n");
                            }
                            break;
                        }
                        case 3: {
                            int codigo_remover;
                            printf("Digite o código do candidato a ser removido: ");
                            scanf("%d", &codigo_remover);
                            remover_candidato(codigo_remover);
                            break;
                        }
                        case 4: {
                            FILE *arq = fopen("Data/candidatos.dat", "rb");
                            if (arq == NULL) {
                                printf("Nenhum candidato cadastrado.\n");
                            } else {
                                imprimirBaseCandidato(arq);
                                fclose(arq);
                            }
                            break;
                        }
                        case 5: {
                            int opcao_busca, codigo_busca;
                            FILE *log_busca = fopen("Data/log.txt", "a");

                            printf("\n--- Pesquisa de Candidatos ---\n");
                            printf("1. Busca Sequencial\n");
                            printf("2. Busca Binária (requer arquivo ordenado)\n");
                            printf("0. Voltar\n");
                            printf("Escolha o tipo de busca: ");
                            scanf("%d", &opcao_busca);

                            if (opcao_busca == 0) break;

                            printf("Digite o código do candidato a ser buscado: ");
                            scanf("%d", &codigo_busca);

                            if (opcao_busca == 1) {
                                FILE *arq_seq = fopen("Data/candidatos.dat", "rb");
                                if (!arq_seq) {
                                    printf("Erro ao abrir 'candidatos.dat'\n");
                                } else {
                                    TCandidato *encontrado = buscaSequencialCandidato(codigo_busca, arq_seq, log_busca);
                                    if (encontrado) {
                                        printf("Candidato encontrado:\n");
                                        imprimeCandidato(encontrado);
                                        free(encontrado);
                                    } else {
                                        printf("Candidato com código %d não encontrado.\n", codigo_busca);
                                    }
                                    fclose(arq_seq);
                                }
                            } else if (opcao_busca == 2) {
                                FILE *arq_bin = fopen("Data/candidatos_ordenado.dat", "rb");
                                if (!arq_bin) {
                                    printf("Erro: 'candidatos_ordenado.dat' não existe. Use a opção 6 para criá-lo.\n");
                                } else {
                                    int tam = tamanho_arquivo_candidato(arq_bin);
                                    TCandidato *encontrado = buscaBinariaCandidato(codigo_busca, arq_bin, 0, tam - 1, log_busca);
                                    if (encontrado) {
                                        printf("Candidato encontrado:\n");
                                        imprimeCandidato(encontrado);
                                        free(encontrado);
                                    } else {
                                        printf("Candidato com código %d não encontrado no arquivo ordenado.\n", codigo_busca);
                                    }
                                    fclose(arq_bin);
                                }
                            }
                            if(log_busca) fclose(log_busca);
                            break;
                        }
                        case 6: {
                            const char* original_file = "Data/candidatos.dat";
                            const char* sorted_file = "Data/candidatos_ordenado.dat";

                            FILE* arq_origem = fopen(original_file, "rb");
                            if (arq_origem == NULL) {
                                printf("Erro: Arquivo de origem '%s' nao encontrado.\n", original_file);
                                break;
                            }
                            FILE* arq_destino = fopen(sorted_file, "wb");
                            if (arq_destino == NULL) {
                                printf("Erro: Nao foi possivel criar o arquivo de destino '%s'.\n", sorted_file);
                                fclose(arq_origem);
                                break;
                            }

                            char buffer[4096];
                            size_t bytes_lidos;
                            while ((bytes_lidos = fread(buffer, 1, sizeof(buffer), arq_origem)) > 0) {
                                fwrite(buffer, 1, bytes_lidos, arq_destino);
                            }
                            fclose(arq_origem);
                            fclose(arq_destino);

                            FILE *arq_para_ordenar = fopen(sorted_file, "r+b");
                            if (arq_para_ordenar == NULL) {
                                printf("Erro ao reabrir o arquivo '%s' para ordenacao.\n", sorted_file);
                                break;
                            }

                            printf("Iniciando ordenacao em disco de '%s'.\n", sorted_file);
                            quickSortEmDiscoCandidato(arq_para_ordenar);  
                            fclose(arq_para_ordenar);
                            printf("Arquivo '%s' ordenado com sucesso.\n", sorted_file);
                            break;
                        }
                        case 0:
                            printf("Retornando ao menu principal...\n");
                            break;
                        default:
                            printf("Opção inválida!\n");
                            break;
                    }
                } while (opcao_candidato != 0);
                break;
            }
            case 3: {
                int opcao_adm;
                do {
                    printf("\nGerenciador de Administradores\n");
                    printf("1. Adicionar Administrador\n");
                    printf("2. Editar Administrador\n");
                    printf("3. Remover Administrador\n");
                    printf("4. Listar Todos os Administradores\n");
                    printf("5. Pesquisar Administrador...\n");
                    printf("6. Preparar arquivo para busca rápida (Ordenar)\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &opcao_adm);

                    switch (opcao_adm) {
                        case 1: {
                            TAdm novo_adm;
                            printf("Digite o código do novo administrador: "); 
                            scanf("%d", &novo_adm.codigo);
                            printf("Digite o nome: "); 
                            scanf(" %[^\n]", novo_adm.base.nome);
                            printf("Digite o CPF: "); 
                            scanf(" %[^\n]", novo_adm.base.cpf);
                            printf("Digite a data de nascimento (DD/MM/AAAA): "); scanf(" %[^\n]", novo_adm.base.data_nascimento);
                            novo_adm.verificacao = true;
                            adicionar_administrador(&novo_adm);
                            break;
                        }
                        case 2: {
                            int codigo_adm_editar;
                            printf("Digite o código do administrador a ser editado: ");
                            scanf("%d", &codigo_adm_editar);

                            if (codigo_adm_editar == adm_logado->codigo) {
                                printf("\nAVISO: Para editar seus próprios dados ou de outros administradores, use a opção apropriada no menu principal (se disponível) ou contate outro administrador.\n");
                                break;
                            }
                            
                            TAdm dados_novos;
                            int status;
                            printf("Digite o novo nome: "); 
                            scanf(" %[^\n]", dados_novos.base.nome);
                            printf("Digite a nova data de nascimento: "); 
                            scanf(" %[^\n]", dados_novos.base.data_nascimento);
                            printf("Deseja definir o status como ATIVO (1) ou INATIVO (0)? "); 
                            scanf("%d", &status);
                            dados_novos.verificacao = (status == 1);

                            if (editar_administrador(codigo_adm_editar, &dados_novos)) {
                                printf("\nAdministrador atualizado com sucesso!\n");
                            } else {
                                printf("\nFalha na atualização. Administrador não encontrado.\n");
                            }
                            break;
                        }
                        case 3: {
                            int codigo_remover;
                            printf("Digite o código do administrador a ser removido: ");
                            scanf("%d", &codigo_remover);
                            
                            remover_administrador(adm_logado->codigo, codigo_remover);
                            break;
                        }
                        case 4: {
                            FILE *arq = fopen("Data/administradores.dat", "rb");
                            if (arq == NULL) {
                                printf("Nenhum administrador cadastrado.\n");
                            } else {
                                imprimirBaseAdministrador(arq);
                                fclose(arq);
                            }
                            break;
                        }
                        case 5: {
                            int opcao_busca, codigo_busca;
                            FILE *log_busca = fopen("Data/log.txt", "a");

                            printf("\n--- Pesquisa de Administradores ---\n");
                            printf("1. Busca Sequencial\n");
                            printf("2. Busca Binária (requer arquivo ordenado)\n");
                            printf("0. Voltar\n");
                            printf("Escolha o tipo de busca: ");
                            scanf("%d", &opcao_busca);

                            if (opcao_busca == 0) break;

                            printf("Digite o código do administrador a ser buscado: ");
                            scanf("%d", &codigo_busca);

                            if (opcao_busca == 1) {
                                FILE *arq_seq = fopen("Data/administradores.dat", "rb");
                                if (!arq_seq) {
                                    printf("Erro ao abrir 'administradores.dat'\n");
                                } else {
                                    TAdm *encontrado = buscaSequencialAdministrador(codigo_busca, arq_seq, log_busca);
                                    if (encontrado) {
                                        printf("Administrador encontrado:\n");
                                        imprimeAdministrador(encontrado);
                                        free(encontrado);
                                    } else {
                                        printf("Administrador com código %d não encontrado.\n", codigo_busca);
                                    }
                                    fclose(arq_seq);
                                }
                            } else if (opcao_busca == 2) {
                                FILE *arq_bin = fopen("Data/administradores_ordenado.dat", "rb");
                                if (!arq_bin) {
                                    printf("Erro: 'administradores_ordenado.dat' não existe. Use a opção 6 para criá-lo.\n");
                                } else {
                                    int tam = tamanho_arquivo_administrador(arq_bin);
                                    TAdm *encontrado = buscaBinariaAdministrador(codigo_busca, arq_bin, 0, tam - 1, log_busca);
                                    if (encontrado) {
                                        printf("Administrador encontrado:\n");
                                        imprimeAdministrador(encontrado);
                                        free(encontrado);
                                    } else {
                                        printf("Administrador com código %d não encontrado no arquivo ordenado.\n", codigo_busca);
                                    }
                                    fclose(arq_bin);
                                }
                            }
                            if(log_busca) fclose(log_busca);
                            break;
                        }
                        case 6: {
                            const char* original_file = "Data/administradores.dat";
                            const char* sorted_file = "Data/administradores_ordenado.dat";

                            FILE* arq_origem = fopen(original_file, "rb");
                            if (arq_origem == NULL) {
                                printf("Erro: Arquivo de origem '%s' nao encontrado.\n", original_file);
                                break;
                            }

                            FILE* arq_destino = fopen(sorted_file, "wb");
                            if (arq_destino == NULL) {
                                printf("Erro: Nao foi possivel criar o arquivo de destino '%s'.\n", sorted_file);
                                fclose(arq_origem);
                                break;
                            }

                            char buffer[4096];
                            size_t bytes_lidos;
                            while ((bytes_lidos = fread(buffer, 1, sizeof(buffer), arq_origem)) > 0) {
                                fwrite(buffer, 1, bytes_lidos, arq_destino);
                            }
                            fclose(arq_origem);
                            fclose(arq_destino);

                            FILE *arq_para_ordenar = fopen(sorted_file, "r+b");
                            if (arq_para_ordenar == NULL) {
                                printf("Erro ao reabrir o arquivo '%s' para ordenacao.\n", sorted_file);
                                break;
                            }

                            printf("Iniciando ordenacao em disco de '%s'\n", sorted_file);
                            quickSortEmDiscoAdministrador(arq_para_ordenar);
                            fclose(arq_para_ordenar);
                            printf("Arquivo '%s' ordenado com sucesso.\n", sorted_file);
                            break;
                        }
                        case 0:
                            printf("Retornando ao menu principal...\n");
                            break;
                        default:
                            printf("Opção inválida!\n");
                            break;
                    }
                } while (opcao_adm != 0);
                break;
            }
            case 4:
                printf("Não fiz\n");
                break;
            case 0:
                printf("Deslogando...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao1 != 0);
}
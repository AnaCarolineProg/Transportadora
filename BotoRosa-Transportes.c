#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


// Definindo as credenciais como constantes globais
const char NOME_USUARIO_CORRETO[] = "senai";
const char SENHA_CORRETA[] = "senai";


// Funções para cadastrar, listar e excluir registros de passageiros, cargas e tripulação
bool realizarLogin();
bool cadastrarUsuario();
bool verificarCredenciais(const char* nomeUsuario, const char* senha);
void menuPassageiros();
void cadastrarPassageiro();
void listarPassageiros();
void excluirPassageiro();
bool menuCargas();
void cadastrarCarga();
void listarCargas();
void excluirCarga();
void menuTripulacao();
void cadastrarTripulacao();
void listarTripulacao();
void excluirTripulacao();
void mostrarPassageirosClasseEconomica();
void mostrarPassageirosClasseExecutiva();
void ajuda();
void sobre();
void limparBuffer();

// Estrutura para armazenar dados do passageiro
struct Passageiro {
    int codigoEmbarque;
    char nomeCompleto[100];
    char email[100];
    char classe[20];
    char cpf[15];
    char dataNascimento[11];
    char localEmbarque[100];
    char localDesembarque[100];
};
// Estrutura para armazenar dados do usuário
struct Usuario {
    char nomeUsuario[50];
    char senha[50];
};
// Estrutura para armazenar dados da carga
struct Carga {
    int codigoEmbarque; //Código de embarque da carga
    char descricao[100]; //Descrição da carga
    char dimensoes[50]; //Dimensões da carga
    float peso; // Peso da carga
    char localEmbarque[100]; //Local de embarque da carga
    char localDesembarque[100]; //Local de desembarque da carga
};

// Estrutura para armazenar dados da tripulação
struct Tripulacao {
    int codigoEmbarque;
    char nomeCompleto[100];
    char email[100];
    char patente[50];
    char cpf[15];
    char dataNascimento[11];
};

// Vetores para armazenar os registros de passageiros, cargas e tripulação
struct Usuario usuarios[100];
struct Passageiro passageiros[100];
struct Carga cargas[100];
struct Tripulacao tripulacao[100];

// Variáveis para controlar o número de registros em cada vetor
int numUsuarios = 0;
int numPassageiros=0;
int numCargas = 0;
int numTripulacao = 0;



int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    bool sair = false;



    printf("Bem-vindo(a) ao Programa de Gestão de Transporte v.1.0.0\n\n");
    realizarLogin();
    system("cls");


    do {
        system("color 1f"); // Define o fundo azul e letras brancas
        printf("Bem-vindo(a) ao Programa de Gestão de Transporte v.1.0.0\n\n");
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Passageiros\n");
        printf("2 - Cargas\n");
        printf("3 - Tripulação\n");
        printf("4 - Ajuda\n");
        printf("5 - Sobre\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o caractere de nova linha deixado pelo scanf

        switch (opcao) {
            case 1:
                system("cls");
                menuPassageiros();
                break;
            case 2:
                system("cls");
                menuCargas();
                break;
            case 3:
                system("cls");
                menuTripulacao();
                break;
            case 4:
                system("cls");
                ajuda();
                break;
            case 5:
                system("cls");
                sobre();
                break;
            case 0:
                sair = true;
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                system("pause");
                system("cls");
        }
    } while (!sair);

    printf("\nObrigado por usar o Programa de Gestão de Transporte. Até logo!\n\n");
    getchar();
    return 0;
}

bool realizarLogin() {
     system("color 5F");
    char nomeUsuario[50];
    char senha[50];

    printf("Nome de usuário: ");
    scanf("%s", nomeUsuario);

    printf("Senha: ");
    scanf("%s", senha);

    if (strcmp(nomeUsuario, NOME_USUARIO_CORRETO) == 0 && strcmp(senha, SENHA_CORRETA) == 0) {
       system("color 5F");
       printf("Login bem-sucedido!\n");
        return true; // Credenciais válidas
    } else {
    printf("Usuário inválido!");
        return false; // Credenciais inválidas
    }

}


bool verificarCredenciais(const char* nomeUsuario, const char* senha) {
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(nomeUsuario, usuarios[i].nomeUsuario) == 0 && strcmp(senha, usuarios[i].senha) == 0) {
            return true; // Credenciais válidas
        }
    }
    return false; // Credenciais inválidas
}

// Função para exibir o menu de passageiros
void menuPassageiros() {
    int opcao;
    system("color 4F");

    do {
        printf("\n=== MENU PASSAGEIROS ===\n");
        printf("1 - Listar Passageiros\n");
        printf("2 - Cadastrar Novo Passageiro\n");
        printf("3 - Excluir Cadastro de Passageiro\n");
        printf("4 - Classe Econômica\n");
        printf("5 - Classe Executiva\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o caractere de nova linha deixado pelo scanf
        system ("cls");

        switch (opcao) {
            case 1:
                system("cls");
                listarPassageiros();
                break;
            case 2:
                system("cls");
                cadastrarPassageiro();
                break;
            case 3:
                system("cls");
                excluirPassageiro();
                break;
            case 4:
                system("cls");
                mostrarPassageirosClasseEconomica();
                break;
            case 5:
                system("cls");
                mostrarPassageirosClasseExecutiva();
                break;
            case 0:
                return; // Voltar ao menu principal
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (true);
}

// Função para cadastrar um novo passageiro
void cadastrarPassageiro() {
    // Verifica se já atingiu o limite máximo de passageiros
    if (numPassageiros >= 100) {
        printf("\nLimite máximo de passageiros atingido. Impossível cadastrar um novo passageiro.\n\n");
        return;
    }

    // Solicita as informações do passageiro ao usuário
    printf("=== CADASTRO DE PASSAGEIRO ===\n");
    printf("Informe o código de embarque: ");
    scanf("%d", &passageiros[numPassageiros].codigoEmbarque);
    getchar(); // Limpa o caractere de nova linha deixado pelo scanf

    printf("Informe o nome completo do passageiro: ");
    fgets(passageiros[numPassageiros].nomeCompleto, 100, stdin);
    passageiros[numPassageiros].nomeCompleto[strcspn(passageiros[numPassageiros].nomeCompleto, "\n")] = '\0';

    printf("Informe o e-mail do passageiro: ");
    fgets(passageiros[numPassageiros].email, 100, stdin);
    passageiros[numPassageiros].email[strcspn(passageiros[numPassageiros].email, "\n")] = '\0';

    printf("Informe a classe do passageiro (Econômica ou Executiva): ");
    fgets(passageiros[numPassageiros].classe, 20, stdin);
    passageiros[numPassageiros].classe[strcspn(passageiros[numPassageiros].classe, "\n")] = '\0';

    printf("Informe o CPF do passageiro: ");
    fgets(passageiros[numPassageiros].cpf, 15, stdin);
    passageiros[numPassageiros].cpf[strcspn(passageiros[numPassageiros].cpf, "\n")] = '\0';

    printf("Informe a data de nascimento do passageiro (formato DD/MM/AAAA): ");
    scanf("%s", passageiros[numPassageiros].dataNascimento);

    printf("Informe o local de embarque do passageiro: ");
    scanf("%s", passageiros[numPassageiros].localEmbarque);

    printf("Informe o local de desembarque do passageiro: ");
    scanf("%s", passageiros[numPassageiros].localDesembarque);
    // Incrementa o número de registros de passageiros
    numPassageiros++;

    printf("\nPassageiro cadastrado com sucesso!\n\n");
    system("pause");
    system("cls");
}

// Função para listar todos os passageiros cadastrados
void listarPassageiros() {
    if (numPassageiros == 0) {
        printf("Nenhum passageiro cadastrado.\n");
        return;
    }

    printf("=== LISTA DE PASSAGEIROS ===\n");
    for (int i = 0; i < numPassageiros; i++) {
        printf("Código de Embarque: %d\n", passageiros[i].codigoEmbarque);
        printf("Nome Completo: %s\n", passageiros[i].nomeCompleto);
        printf("E-mail: %s\n", passageiros[i].email);
        printf("Classe: %s\n", passageiros[i].classe);
        printf("CPF: %s\n", passageiros[i].cpf);
        printf("Data de Nascimento: %s\n", passageiros[i].dataNascimento);
        printf("Local de Embarque: %s\n", passageiros[i].localEmbarque);
        printf("Local de Desembarque: %s\n", passageiros[i].localDesembarque);
        printf("\n");
    }
}

// Função para excluir um passageiro
void excluirPassageiro() {
    int codigoExclusao, posicaoExclusao = -1;

    // Solicita o código de embarque do passageiro a ser excluído
    printf("Informe o código de embarque do passageiro a ser excluído: ");
    scanf("%d", &codigoExclusao);
    getchar(); // Limpa o caractere de nova linha deixado pelo scanf

    // Procura a posição do passageiro a ser excluído no vetor passageiros[]
    for (int i = 0; i < numPassageiros; i++) {
        if (passageiros[i].codigoEmbarque == codigoExclusao) {
            posicaoExclusao = i;
            break;
        }
    }

    // Se não encontrar o passageiro com o código informado, exibe mensagem de erro
    if (posicaoExclusao == -1) {
        printf("Passageiro com código de embarque %d não encontrado.\n", codigoExclusao);
        return;
    }

    // Realiza a exclusão do passageiro na posição encontrada
    for (int i = posicaoExclusao; i < numPassageiros - 1; i++) {
        passageiros[i] = passageiros[i + 1];
    }

    // Atualiza o número de passageiros no vetor
    numPassageiros--;

    printf("Passageiro com código de embarque %d excluído com sucesso.\n", codigoExclusao);
}

// Função para exibir o menu de cargas
bool menuCargas() {
    int opcao;
    system("color C0");

    do {
        printf("=== MENU CARGAS ===\n");
        printf("1 - Listar Cargas\n");
        printf("2 - Cadastrar Nova Carga\n");
        printf("3 - Excluir Cadastro de Carga\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o caractere de nova linha deixado pelo scanf

        switch (opcao) {
            case 1:
                listarCargas();
                break;
            case 2:
                cadastrarCarga();
                break;
            case 3:
                excluirCarga();
                break;
            case 0:
                system("cls");
                return true; // Voltar ao menu principal
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (true);
}

// Função para cadastrar uma nova carga
void cadastrarCarga() {
        // Verifica se já atingiu o limite máximo de cargas
    if (numCargas >= 100) {
        printf("Limite máximo de cargas atingido. Impossível cadastrar uma nova carga.\n");
        return;
    }

    // Solicita as informações da carga ao usuário
    printf("=== CADASTRO DE CARGA ===\n");
    printf("Informe o código de embarque: ");
    scanf("%d", &cargas[numCargas].codigoEmbarque);
    getchar(); // Limpa o caractere de nova linha deixado pelo scanf

    printf("Informe a descrição da carga: ");
    fgets(cargas[numCargas].descricao, 100, stdin);
    cargas[numCargas].descricao[strcspn(cargas[numCargas].descricao, "\n")] = '\0';

    char dimensoesStr[15]; // Aumentar o tamanho da string para acomodar a dimensão com a unidade de medida
    printf("Informe as dimensões da carga (em m³): ");
    fgets(dimensoesStr, 15, stdin);
    dimensoesStr[strcspn(dimensoesStr, "\n")] = '\0';

    // Copia as dimensões para o campo dimensoes da carga
    strncpy(cargas[numCargas].dimensoes, dimensoesStr, sizeof(cargas[numCargas].dimensoes));

    printf("Informe o peso da carga (em kg): ");
    scanf("%f", &cargas[numCargas].peso);
    getchar();

    printf("Informe o local de embarque da carga: ");
    fgets(cargas[numCargas].localEmbarque, 100, stdin);
    cargas[numCargas].localEmbarque[strcspn(cargas[numCargas].localEmbarque, "\n")] = '\0';

    printf("Informe o local de desembarque da carga: ");
    fgets(cargas[numCargas].localDesembarque, 100, stdin);
    cargas[numCargas].localDesembarque[strcspn(cargas[numCargas].localDesembarque, "\n")] = '\0';

    // Incrementa o número de registros de cargas
    numCargas++;

    printf("Carga cadastrada com sucesso!\n");
}

// Função para listar todas as cargas cadastradas
void listarCargas() {
    if (numCargas == 0) {
        printf("Nenhuma carga cadastrada.\n");
        return;
    }

    printf("=== LISTA DE CARGAS ===\n");
    for (int i = 0; i < numCargas; i++) {
        printf("Código de Embarque: %d\n", cargas[i].codigoEmbarque);
        printf("Descrição: %s\n", cargas[i].descricao);
        printf("Dimensões: %s m³\n", cargas[i].dimensoes);
        printf("Peso: %.2f kg\n", cargas[i].peso);
        printf("Local de Embarque: %s\n", cargas[i].localEmbarque);
        printf("Local de Desembarque: %s\n", cargas[i].localDesembarque);
        printf("\n");
    }
}

// Função para excluir uma carga
void excluirCarga() {
    int codigoExclusao, posicaoExclusao = -1;

    // Solicitar o código de embarque da carga a ser excluída
    printf("Informe o código de embarque da carga a ser excluída: ");
    scanf("%d", &codigoExclusao);
    getchar(); // Limpa o caractere de nova linha deixado pelo scanf

    // Procurar a posição da carga a ser excluída no vetor cargas[]
    for (int i = 0; i < numCargas; i++) {
        if (cargas[i].codigoEmbarque == codigoExclusao) {
            posicaoExclusao = i;
            break;
        }
    }

    // Se não encontrar a carga com o código informado, exibir mensagem de erro
    if (posicaoExclusao == -1) {
        printf("Carga com código %d não encontrada.\n", codigoExclusao);
        return;
    }

    // Realizar a exclusão da carga da posição encontrada
    for (int i = posicaoExclusao; i < numCargas - 1; i++) {
        cargas[i] = cargas[i + 1];
    }

    // Atualizar o número de cargas no vetor
    numCargas--;

    printf("Carga com código %d excluída com sucesso.\n", codigoExclusao);
}

// Função para exibir o menu de tripulação
void menuTripulacao() {
    int opcao;
    system("color 60");

    do {
        printf("\n=== MENU TRIPULAÇÃO ===\n");
        printf("1 - Listar Tripulação\n");
        printf("2 - Cadastrar Novo Membro da Tripulação\n");
        printf("3 - Excluir Cadastro de Membro da Tripulação\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o caractere de nova linha deixado pelo scanf

        switch (opcao) {
            case 1:
                listarTripulacao();
                break;
            case 2:
                cadastrarTripulacao();
                break;
            case 3:
                excluirTripulacao();
                break;
            case 0:
                return; // Voltar ao menu principal
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (true);
    system("cls");
}

// Função para cadastrar um novo membro da tripulação
void cadastrarTripulacao() {
    // Verifica se já atingiu o limite máximo de membros da tripulação
    if (numTripulacao >= 100) {
        printf("Limite máximo de membros da tripulação atingido. Impossível cadastrar um novo membro.\n");
        return;
    }

    // Solicita as informações do membro da tripulação ao usuário
    printf("=== CADASTRO DE MEMBRO DA TRIPULAÇÃO ===\n");
    printf("Informe o código de embarque: ");
    scanf("%d", &tripulacao[numTripulacao].codigoEmbarque);
    getchar(); // Limpa o caractere de nova linha deixado pelo scanf

    printf("Informe o nome completo do membro da tripulação: ");
    fgets(tripulacao[numTripulacao].nomeCompleto, 100, stdin);
    tripulacao[numTripulacao].nomeCompleto[strcspn(tripulacao[numTripulacao].nomeCompleto, "\n")] = '\0';

    printf("Informe o e-mail do membro da tripulação: ");
    fgets(tripulacao[numTripulacao].email, 100, stdin);
    tripulacao[numTripulacao].email[strcspn(tripulacao[numTripulacao].email, "\n")] = '\0';

    printf("Informe a patente do membro da tripulação: ");
    fgets(tripulacao[numTripulacao].patente, 50, stdin);
    tripulacao[numTripulacao].patente[strcspn(tripulacao[numTripulacao].patente, "\n")] = '\0';

    printf("Informe o CPF do membro da tripulação: ");
    fgets(tripulacao[numTripulacao].cpf, 15, stdin);
    tripulacao[numTripulacao].cpf[strcspn(tripulacao[numTripulacao].cpf, "\n")] = '\0';

    printf("Informe a data de nascimento do membro da tripulação: ");
    fgets(tripulacao[numTripulacao].dataNascimento, 11, stdin);
    tripulacao[numTripulacao].dataNascimento[strcspn(tripulacao[numTripulacao].dataNascimento, "\n")] = '\0';

    // Incrementa o número de registros de membros da tripulação
    numTripulacao++;

    printf("Membro da tripulação cadastrado com sucesso!\n");
    getchar();
    system("cls");
}

// Função para listar todos os membros da tripulação cadastrados
void listarTripulacao() {
    if (numTripulacao == 0) {
        printf("Nenhum membro da tripulação cadastrado.\n");
        return;
    }

    printf("=== LISTA DE MEMBROS DA TRIPULAÇÃO ===\n");
    for (int i = 0; i < numTripulacao; i++) {
        printf("Código de Embarque: %d\n", tripulacao[i].codigoEmbarque);
        printf("Nome Completo: %s\n", tripulacao[i].nomeCompleto);
        printf("E-mail: %s\n", tripulacao[i].email);
        printf("Patente: %s\n", tripulacao[i].patente);
        printf("CPF: %s\n", tripulacao[i].cpf);
        printf("Data de Nascimento: %s\n", tripulacao[i].dataNascimento);
        printf("\n");
    }
}

// Função para excluir um membro da tripulação
void excluirTripulacao() {

    int codigoExclusao, posicaoExclusao = -1;

    // Solicita o código de embarque do membro a ser excluído
    printf("Informe o código de embarque do membro da tripulação a ser excluído: ");
    scanf("%d", &codigoExclusao);
    getchar();

    // Procurar a posição do membro a ser excluído no vetor tripulacao[]
    for (int i = 0; i < numTripulacao; i++) {
        if (tripulacao[i].codigoEmbarque == codigoExclusao) {
            posicaoExclusao = i;
            break;
        }
    }

    // Se não encontrar o membro com o código informado, exibir mensagem de erro
    if (posicaoExclusao == -1) {
        printf("Membro da tripulação com código de embarque %d não encontrado.\n", codigoExclusao);
        return;
    }

    // Realizar a exclusão do membro da posição encontrada
    for (int i = posicaoExclusao; i < numTripulacao - 1; i++) {
        tripulacao[i] = tripulacao[i + 1];
    }

    // Atualizar o número de membros da tripulação no vetor
    numTripulacao--;

    printf("Membro da tripulação com código de embarque %d excluído com sucesso.\n", codigoExclusao);
}

// Função para exibir os nomes dos passageiros na classe econômica
void mostrarPassageirosClasseEconomica() {
    bool encontrouEconomica = false;

    printf("=== PASSAGEIROS NA CLASSE ECONÔMICA ===\n");
    for (int i = 0; i < numPassageiros; i++) {
        // Verificar se a classe é "Econômica" ou "econômica" (ignorando o case)
        if (strcasecmp(passageiros[i].classe, "Econômica") == 0) {
            printf("%s\n", passageiros[i].nomeCompleto);
            encontrouEconomica = true;
        }
    }

    if (!encontrouEconomica) {
        printf("\nNenhum passageiro na classe econômica cadastrado.\n\n");
    }
}

// Função para exibir os nomes dos passageiros na classe executiva
void mostrarPassageirosClasseExecutiva() {
    bool encontrouExecutiva = false;

    printf("=== PASSAGEIROS NA CLASSE EXECUTIVA ===\n");
    for (int i = 0; i < numPassageiros; i++) {
        // Verificar se a classe é "Executiva" ou "executiva" (ignorando o case)
        if (strcasecmp(passageiros[i].classe, "Executiva") == 0) {
            printf("%s\n", passageiros[i].nomeCompleto);
            encontrouExecutiva = true;
        }
    }

    if (!encontrouExecutiva) {
        printf("\nNenhum passageiro na classe executiva cadastrado.\n\n");
    }
}

// Função para exibir a ajuda do programa
void ajuda() {
    system("color F0");
    printf("=== AJUDA ===\n");
    printf("Este programa foi desenvolvido para gerir os elementos de transporte de uma empresa.\n");
    printf("Utilize o menu principal para acessar as funcionalidades disponíveis:\n");
    printf("1 - Passageiros: Permite cadastrar, listar e excluir passageiros.\n");
    printf("2 - Cargas: Permite cadastrar, listar e excluir cargas.\n");
    printf("3 - Tripulação: Permite cadastrar, listar e excluir membros da tripulação.\n");
    printf("4 - Ajuda: Exibe esta mensagem de ajuda.\n");
    printf("5 - Sobre: Exibe informações sobre o programa.\n");
    printf("0 - Sair: Encerra o programa.\n");
    printf("Para selecionar uma opção, digite o número correspondente e pressione Enter.\n\n\n");
    getchar();
    system("cls");
}

// Função para exibir informações sobre o programa
void sobre() {
    system("color F0");
    printf("\n=== SOBRE O PROGRAMA ===\n");
    printf("Programa de Gestão de Transporte.\n");
    printf("Funcionalidades disponíveis:\n");
    printf("- Passageiros: Permite cadastrar, listar e excluir passageiros.\n");
    printf("- Cargas: Permite cadastrar, listar e excluir cargas.\n");
    printf("- Tripulação: Permite cadastrar, listar e excluir membros da tripulação.\n");
    printf("- Ajuda: Exibe informações de como usar o programa.\n");
    printf("- Sair: Encerra o programa.\n");
    printf("Desenvolvido por: Ana Caroline Ferreira da Piedade \n");
    printf("Versão do programa: v.1.0.0 \n");
    printf("Direitos reservados.\n\n");
    getchar();
    system("cls");

}


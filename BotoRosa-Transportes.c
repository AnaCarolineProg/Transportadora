#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


// Definindo as credenciais como constantes globais
const char NOME_USUARIO_CORRETO[] = "senai";
const char SENHA_CORRETA[] = "senai";


// Fun��es para cadastrar, listar e excluir registros de passageiros, cargas e tripula��o
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
// Estrutura para armazenar dados do usu�rio
struct Usuario {
    char nomeUsuario[50];
    char senha[50];
};
// Estrutura para armazenar dados da carga
struct Carga {
    int codigoEmbarque; //C�digo de embarque da carga
    char descricao[100]; //Descri��o da carga
    char dimensoes[50]; //Dimens�es da carga
    float peso; // Peso da carga
    char localEmbarque[100]; //Local de embarque da carga
    char localDesembarque[100]; //Local de desembarque da carga
};

// Estrutura para armazenar dados da tripula��o
struct Tripulacao {
    int codigoEmbarque;
    char nomeCompleto[100];
    char email[100];
    char patente[50];
    char cpf[15];
    char dataNascimento[11];
};

// Vetores para armazenar os registros de passageiros, cargas e tripula��o
struct Usuario usuarios[100];
struct Passageiro passageiros[100];
struct Carga cargas[100];
struct Tripulacao tripulacao[100];

// Vari�veis para controlar o n�mero de registros em cada vetor
int numUsuarios = 0;
int numPassageiros=0;
int numCargas = 0;
int numTripulacao = 0;



int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    bool sair = false;



    printf("Bem-vindo(a) ao Programa de Gest�o de Transporte v.1.0.0\n\n");
    realizarLogin();
    system("cls");


    do {
        system("color 1f"); // Define o fundo azul e letras brancas
        printf("Bem-vindo(a) ao Programa de Gest�o de Transporte v.1.0.0\n\n");
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Passageiros\n");
        printf("2 - Cargas\n");
        printf("3 - Tripula��o\n");
        printf("4 - Ajuda\n");
        printf("5 - Sobre\n");
        printf("0 - Sair\n");
        printf("Escolha uma op��o: ");
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
                printf("Op��o inv�lida. Tente novamente.\n");
                system("pause");
                system("cls");
        }
    } while (!sair);

    printf("\nObrigado por usar o Programa de Gest�o de Transporte. At� logo!\n\n");
    getchar();
    return 0;
}

bool realizarLogin() {
     system("color 5F");
    char nomeUsuario[50];
    char senha[50];

    printf("Nome de usu�rio: ");
    scanf("%s", nomeUsuario);

    printf("Senha: ");
    scanf("%s", senha);

    if (strcmp(nomeUsuario, NOME_USUARIO_CORRETO) == 0 && strcmp(senha, SENHA_CORRETA) == 0) {
       system("color 5F");
       printf("Login bem-sucedido!\n");
        return true; // Credenciais v�lidas
    } else {
    printf("Usu�rio inv�lido!");
        return false; // Credenciais inv�lidas
    }

}


bool verificarCredenciais(const char* nomeUsuario, const char* senha) {
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(nomeUsuario, usuarios[i].nomeUsuario) == 0 && strcmp(senha, usuarios[i].senha) == 0) {
            return true; // Credenciais v�lidas
        }
    }
    return false; // Credenciais inv�lidas
}

// Fun��o para exibir o menu de passageiros
void menuPassageiros() {
    int opcao;
    system("color 4F");

    do {
        printf("\n=== MENU PASSAGEIROS ===\n");
        printf("1 - Listar Passageiros\n");
        printf("2 - Cadastrar Novo Passageiro\n");
        printf("3 - Excluir Cadastro de Passageiro\n");
        printf("4 - Classe Econ�mica\n");
        printf("5 - Classe Executiva\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("Escolha uma op��o: ");
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
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (true);
}

// Fun��o para cadastrar um novo passageiro
void cadastrarPassageiro() {
    // Verifica se j� atingiu o limite m�ximo de passageiros
    if (numPassageiros >= 100) {
        printf("\nLimite m�ximo de passageiros atingido. Imposs�vel cadastrar um novo passageiro.\n\n");
        return;
    }

    // Solicita as informa��es do passageiro ao usu�rio
    printf("=== CADASTRO DE PASSAGEIRO ===\n");
    printf("Informe o c�digo de embarque: ");
    scanf("%d", &passageiros[numPassageiros].codigoEmbarque);
    getchar(); // Limpa o caractere de nova linha deixado pelo scanf

    printf("Informe o nome completo do passageiro: ");
    fgets(passageiros[numPassageiros].nomeCompleto, 100, stdin);
    passageiros[numPassageiros].nomeCompleto[strcspn(passageiros[numPassageiros].nomeCompleto, "\n")] = '\0';

    printf("Informe o e-mail do passageiro: ");
    fgets(passageiros[numPassageiros].email, 100, stdin);
    passageiros[numPassageiros].email[strcspn(passageiros[numPassageiros].email, "\n")] = '\0';

    printf("Informe a classe do passageiro (Econ�mica ou Executiva): ");
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
    // Incrementa o n�mero de registros de passageiros
    numPassageiros++;

    printf("\nPassageiro cadastrado com sucesso!\n\n");
    system("pause");
    system("cls");
}

// Fun��o para listar todos os passageiros cadastrados
void listarPassageiros() {
    if (numPassageiros == 0) {
        printf("Nenhum passageiro cadastrado.\n");
        return;
    }

    printf("=== LISTA DE PASSAGEIROS ===\n");
    for (int i = 0; i < numPassageiros; i++) {
        printf("C�digo de Embarque: %d\n", passageiros[i].codigoEmbarque);
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

// Fun��o para excluir um passageiro
void excluirPassageiro() {
    int codigoExclusao, posicaoExclusao = -1;

    // Solicita o c�digo de embarque do passageiro a ser exclu�do
    printf("Informe o c�digo de embarque do passageiro a ser exclu�do: ");
    scanf("%d", &codigoExclusao);
    getchar(); // Limpa o caractere de nova linha deixado pelo scanf

    // Procura a posi��o do passageiro a ser exclu�do no vetor passageiros[]
    for (int i = 0; i < numPassageiros; i++) {
        if (passageiros[i].codigoEmbarque == codigoExclusao) {
            posicaoExclusao = i;
            break;
        }
    }

    // Se n�o encontrar o passageiro com o c�digo informado, exibe mensagem de erro
    if (posicaoExclusao == -1) {
        printf("Passageiro com c�digo de embarque %d n�o encontrado.\n", codigoExclusao);
        return;
    }

    // Realiza a exclus�o do passageiro na posi��o encontrada
    for (int i = posicaoExclusao; i < numPassageiros - 1; i++) {
        passageiros[i] = passageiros[i + 1];
    }

    // Atualiza o n�mero de passageiros no vetor
    numPassageiros--;

    printf("Passageiro com c�digo de embarque %d exclu�do com sucesso.\n", codigoExclusao);
}

// Fun��o para exibir o menu de cargas
bool menuCargas() {
    int opcao;
    system("color C0");

    do {
        printf("=== MENU CARGAS ===\n");
        printf("1 - Listar Cargas\n");
        printf("2 - Cadastrar Nova Carga\n");
        printf("3 - Excluir Cadastro de Carga\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("Escolha uma op��o: ");
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
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (true);
}

// Fun��o para cadastrar uma nova carga
void cadastrarCarga() {
        // Verifica se j� atingiu o limite m�ximo de cargas
    if (numCargas >= 100) {
        printf("Limite m�ximo de cargas atingido. Imposs�vel cadastrar uma nova carga.\n");
        return;
    }

    // Solicita as informa��es da carga ao usu�rio
    printf("=== CADASTRO DE CARGA ===\n");
    printf("Informe o c�digo de embarque: ");
    scanf("%d", &cargas[numCargas].codigoEmbarque);
    getchar(); // Limpa o caractere de nova linha deixado pelo scanf

    printf("Informe a descri��o da carga: ");
    fgets(cargas[numCargas].descricao, 100, stdin);
    cargas[numCargas].descricao[strcspn(cargas[numCargas].descricao, "\n")] = '\0';

    char dimensoesStr[15]; // Aumentar o tamanho da string para acomodar a dimens�o com a unidade de medida
    printf("Informe as dimens�es da carga (em m�): ");
    fgets(dimensoesStr, 15, stdin);
    dimensoesStr[strcspn(dimensoesStr, "\n")] = '\0';

    // Copia as dimens�es para o campo dimensoes da carga
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

    // Incrementa o n�mero de registros de cargas
    numCargas++;

    printf("Carga cadastrada com sucesso!\n");
}

// Fun��o para listar todas as cargas cadastradas
void listarCargas() {
    if (numCargas == 0) {
        printf("Nenhuma carga cadastrada.\n");
        return;
    }

    printf("=== LISTA DE CARGAS ===\n");
    for (int i = 0; i < numCargas; i++) {
        printf("C�digo de Embarque: %d\n", cargas[i].codigoEmbarque);
        printf("Descri��o: %s\n", cargas[i].descricao);
        printf("Dimens�es: %s m�\n", cargas[i].dimensoes);
        printf("Peso: %.2f kg\n", cargas[i].peso);
        printf("Local de Embarque: %s\n", cargas[i].localEmbarque);
        printf("Local de Desembarque: %s\n", cargas[i].localDesembarque);
        printf("\n");
    }
}

// Fun��o para excluir uma carga
void excluirCarga() {
    int codigoExclusao, posicaoExclusao = -1;

    // Solicitar o c�digo de embarque da carga a ser exclu�da
    printf("Informe o c�digo de embarque da carga a ser exclu�da: ");
    scanf("%d", &codigoExclusao);
    getchar(); // Limpa o caractere de nova linha deixado pelo scanf

    // Procurar a posi��o da carga a ser exclu�da no vetor cargas[]
    for (int i = 0; i < numCargas; i++) {
        if (cargas[i].codigoEmbarque == codigoExclusao) {
            posicaoExclusao = i;
            break;
        }
    }

    // Se n�o encontrar a carga com o c�digo informado, exibir mensagem de erro
    if (posicaoExclusao == -1) {
        printf("Carga com c�digo %d n�o encontrada.\n", codigoExclusao);
        return;
    }

    // Realizar a exclus�o da carga da posi��o encontrada
    for (int i = posicaoExclusao; i < numCargas - 1; i++) {
        cargas[i] = cargas[i + 1];
    }

    // Atualizar o n�mero de cargas no vetor
    numCargas--;

    printf("Carga com c�digo %d exclu�da com sucesso.\n", codigoExclusao);
}

// Fun��o para exibir o menu de tripula��o
void menuTripulacao() {
    int opcao;
    system("color 60");

    do {
        printf("\n=== MENU TRIPULA��O ===\n");
        printf("1 - Listar Tripula��o\n");
        printf("2 - Cadastrar Novo Membro da Tripula��o\n");
        printf("3 - Excluir Cadastro de Membro da Tripula��o\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("Escolha uma op��o: ");
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
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (true);
    system("cls");
}

// Fun��o para cadastrar um novo membro da tripula��o
void cadastrarTripulacao() {
    // Verifica se j� atingiu o limite m�ximo de membros da tripula��o
    if (numTripulacao >= 100) {
        printf("Limite m�ximo de membros da tripula��o atingido. Imposs�vel cadastrar um novo membro.\n");
        return;
    }

    // Solicita as informa��es do membro da tripula��o ao usu�rio
    printf("=== CADASTRO DE MEMBRO DA TRIPULA��O ===\n");
    printf("Informe o c�digo de embarque: ");
    scanf("%d", &tripulacao[numTripulacao].codigoEmbarque);
    getchar(); // Limpa o caractere de nova linha deixado pelo scanf

    printf("Informe o nome completo do membro da tripula��o: ");
    fgets(tripulacao[numTripulacao].nomeCompleto, 100, stdin);
    tripulacao[numTripulacao].nomeCompleto[strcspn(tripulacao[numTripulacao].nomeCompleto, "\n")] = '\0';

    printf("Informe o e-mail do membro da tripula��o: ");
    fgets(tripulacao[numTripulacao].email, 100, stdin);
    tripulacao[numTripulacao].email[strcspn(tripulacao[numTripulacao].email, "\n")] = '\0';

    printf("Informe a patente do membro da tripula��o: ");
    fgets(tripulacao[numTripulacao].patente, 50, stdin);
    tripulacao[numTripulacao].patente[strcspn(tripulacao[numTripulacao].patente, "\n")] = '\0';

    printf("Informe o CPF do membro da tripula��o: ");
    fgets(tripulacao[numTripulacao].cpf, 15, stdin);
    tripulacao[numTripulacao].cpf[strcspn(tripulacao[numTripulacao].cpf, "\n")] = '\0';

    printf("Informe a data de nascimento do membro da tripula��o: ");
    fgets(tripulacao[numTripulacao].dataNascimento, 11, stdin);
    tripulacao[numTripulacao].dataNascimento[strcspn(tripulacao[numTripulacao].dataNascimento, "\n")] = '\0';

    // Incrementa o n�mero de registros de membros da tripula��o
    numTripulacao++;

    printf("Membro da tripula��o cadastrado com sucesso!\n");
    getchar();
    system("cls");
}

// Fun��o para listar todos os membros da tripula��o cadastrados
void listarTripulacao() {
    if (numTripulacao == 0) {
        printf("Nenhum membro da tripula��o cadastrado.\n");
        return;
    }

    printf("=== LISTA DE MEMBROS DA TRIPULA��O ===\n");
    for (int i = 0; i < numTripulacao; i++) {
        printf("C�digo de Embarque: %d\n", tripulacao[i].codigoEmbarque);
        printf("Nome Completo: %s\n", tripulacao[i].nomeCompleto);
        printf("E-mail: %s\n", tripulacao[i].email);
        printf("Patente: %s\n", tripulacao[i].patente);
        printf("CPF: %s\n", tripulacao[i].cpf);
        printf("Data de Nascimento: %s\n", tripulacao[i].dataNascimento);
        printf("\n");
    }
}

// Fun��o para excluir um membro da tripula��o
void excluirTripulacao() {

    int codigoExclusao, posicaoExclusao = -1;

    // Solicita o c�digo de embarque do membro a ser exclu�do
    printf("Informe o c�digo de embarque do membro da tripula��o a ser exclu�do: ");
    scanf("%d", &codigoExclusao);
    getchar();

    // Procurar a posi��o do membro a ser exclu�do no vetor tripulacao[]
    for (int i = 0; i < numTripulacao; i++) {
        if (tripulacao[i].codigoEmbarque == codigoExclusao) {
            posicaoExclusao = i;
            break;
        }
    }

    // Se n�o encontrar o membro com o c�digo informado, exibir mensagem de erro
    if (posicaoExclusao == -1) {
        printf("Membro da tripula��o com c�digo de embarque %d n�o encontrado.\n", codigoExclusao);
        return;
    }

    // Realizar a exclus�o do membro da posi��o encontrada
    for (int i = posicaoExclusao; i < numTripulacao - 1; i++) {
        tripulacao[i] = tripulacao[i + 1];
    }

    // Atualizar o n�mero de membros da tripula��o no vetor
    numTripulacao--;

    printf("Membro da tripula��o com c�digo de embarque %d exclu�do com sucesso.\n", codigoExclusao);
}

// Fun��o para exibir os nomes dos passageiros na classe econ�mica
void mostrarPassageirosClasseEconomica() {
    bool encontrouEconomica = false;

    printf("=== PASSAGEIROS NA CLASSE ECON�MICA ===\n");
    for (int i = 0; i < numPassageiros; i++) {
        // Verificar se a classe � "Econ�mica" ou "econ�mica" (ignorando o case)
        if (strcasecmp(passageiros[i].classe, "Econ�mica") == 0) {
            printf("%s\n", passageiros[i].nomeCompleto);
            encontrouEconomica = true;
        }
    }

    if (!encontrouEconomica) {
        printf("\nNenhum passageiro na classe econ�mica cadastrado.\n\n");
    }
}

// Fun��o para exibir os nomes dos passageiros na classe executiva
void mostrarPassageirosClasseExecutiva() {
    bool encontrouExecutiva = false;

    printf("=== PASSAGEIROS NA CLASSE EXECUTIVA ===\n");
    for (int i = 0; i < numPassageiros; i++) {
        // Verificar se a classe � "Executiva" ou "executiva" (ignorando o case)
        if (strcasecmp(passageiros[i].classe, "Executiva") == 0) {
            printf("%s\n", passageiros[i].nomeCompleto);
            encontrouExecutiva = true;
        }
    }

    if (!encontrouExecutiva) {
        printf("\nNenhum passageiro na classe executiva cadastrado.\n\n");
    }
}

// Fun��o para exibir a ajuda do programa
void ajuda() {
    system("color F0");
    printf("=== AJUDA ===\n");
    printf("Este programa foi desenvolvido para gerir os elementos de transporte de uma empresa.\n");
    printf("Utilize o menu principal para acessar as funcionalidades dispon�veis:\n");
    printf("1 - Passageiros: Permite cadastrar, listar e excluir passageiros.\n");
    printf("2 - Cargas: Permite cadastrar, listar e excluir cargas.\n");
    printf("3 - Tripula��o: Permite cadastrar, listar e excluir membros da tripula��o.\n");
    printf("4 - Ajuda: Exibe esta mensagem de ajuda.\n");
    printf("5 - Sobre: Exibe informa��es sobre o programa.\n");
    printf("0 - Sair: Encerra o programa.\n");
    printf("Para selecionar uma op��o, digite o n�mero correspondente e pressione Enter.\n\n\n");
    getchar();
    system("cls");
}

// Fun��o para exibir informa��es sobre o programa
void sobre() {
    system("color F0");
    printf("\n=== SOBRE O PROGRAMA ===\n");
    printf("Programa de Gest�o de Transporte.\n");
    printf("Funcionalidades dispon�veis:\n");
    printf("- Passageiros: Permite cadastrar, listar e excluir passageiros.\n");
    printf("- Cargas: Permite cadastrar, listar e excluir cargas.\n");
    printf("- Tripula��o: Permite cadastrar, listar e excluir membros da tripula��o.\n");
    printf("- Ajuda: Exibe informa��es de como usar o programa.\n");
    printf("- Sair: Encerra o programa.\n");
    printf("Desenvolvido por: Ana Caroline Ferreira da Piedade \n");
    printf("Vers�o do programa: v.1.0.0 \n");
    printf("Direitos reservados.\n\n");
    getchar();
    system("cls");

}


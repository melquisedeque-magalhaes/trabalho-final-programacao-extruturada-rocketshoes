#include "client.h"
#include "../files/files.c"
#include "../settings/settings.h"
#include "string.h"

#define True 1
#define False 0

#define LENGTH 100

struct clientData {

    int id;
    char name[100];
    char password[50];
    char email[100];

};


int MenuClient() {
    int option;
    int error = False;

    do {

        printf("\n \n MENU CLIENTE \n \n");
        printf("1 -> CADASTRAR \n");
        printf("2 -> ENTRAR \n");
        printf("0 -> SAIR DO PROGRAMA \n\n\n");

        printf("Digite sua opção: ");
        ClearBuffer();
        scanf("%d", &option);

        error = option > 2 || option < 0 ? True : False;

        if(error)
            printf("\n Erro opção invalida! \n TENTE NOVAMENTE \n");

    } while(error);

    return option;
}

void switchClientMenu(int optionMenuClient){

    struct clientData client;
    int isLogin, option;

    /* ABRINDO ARQUIVOS */

    FILE *fileClient;

    fileClient = openFile("./files/client.dat");

    if(fileClient == NULL)
        printf("\n ERRO de abertura do arquivo! \n");

    switch(optionMenuClient) {
        case 1: 
            registerCLient(client, fileClient, -1);
            break;
        case 2:
            isLogin = loginClient(client, fileClient);
            if(isLogin)
                option = MenuClientLogin();
            break;
        default:
            printf("\n Error escolha invalida! \n");
            break;
    }

    fclose(fileClient);
}

void registerCLient(
    struct clientData client, 
    FILE *fileClient,
    int reg
){
    int index;

    printf("\n\n\n ### REGISTRANDO CLIENTE ### \n\n\n");

    do{
        printf("Digite o codigo do cliente: ");
        ClearBuffer();
        scanf("%d", &client.id);

        index = getClient(client.id, fileClient);

        if(index > 0)
            printf("\n\n   ERRO!, codigo ja existente, tente novamente!    \n\n");
            
    }while(index > 0);

    printf("Digite seu nome: ");
    ClearBuffer();
    fgets(client.name, 100, stdin);

    printf("Digite sua senha: ");
    ClearBuffer();
    fgets(client.password, 100, stdin);

    printf("Digite seu e-mail: ");
    ClearBuffer();
    fgets(client.email, 100, stdin);

    if(reg <= 0)
        fseek(fileClient, 0, SEEK_END);
    else 
        fseek(fileClient, (client.id - 1) * sizeof(client), SEEK_SET);

    fwrite(&client, sizeof(client), 1, fileClient);
}

int loginClient(
    struct clientData client, 
    FILE *fileClient
){
    char email[100];
    char password[100];
    int i;
    int error = False; 
    int exitSignIN = True;
    char optionThen;

    do {
        fseek(fileClient, 0, SEEK_SET);

        printf("\n\n\n ### FAZENDO LOGIN DO CLIENTE ### \n\n\n");

        printf("Email: ");
        ClearBuffer();
        fgets(email, 100, stdin);

        printf("Senha: ");
        ClearBuffer();
        fgets(password, 100, stdin);

        while (fread(&client, sizeof(client), 1, fileClient)){
            if(!strcmp(email, client.email) && !strcmp(password, client.password)){

                printf("\n Bem vindo %s !", client.name);
                printf("Fazendo login...\n");
                

                return True;

            }

            i++;
        }

        printf("\n Sinto muito Email ou Senha incorreta! \n");

        printf("Deseja tentar novamente ? (S) Sim ou (N) Não: ");
        optionThen = getchar();

        if(optionThen == 'N' | optionThen == 'n'){
            exitSignIN = True;
            error = False;
        }

    } while(error || !exitSignIN);

    ClearWindows();

    return False;

}

int getClient(int id, FILE *nameFile){
    int idClient = 0;
    struct clientData client;

    fseek(nameFile, 0, SEEK_SET);

    while (fread(&client, sizeof(client), 1, nameFile)){
        idClient++;

        if(id == client.id)
            return idClient;
    }

    return -1;
    
}

int MenuClientLogin() {
    int option;
    int error = False;

    do {

        printf("\n \n MENU DE COMPRAS \n \n");
        printf("1 -> LISTAR TODOS OS TENIS \n");
        printf("2 -> MOSTRAR CARRINHO \n");
        printf("0 -> SAIR DA MINHA CONTA \n\n\n");

        printf("Digite sua opção: ");
        ClearBuffer();
        scanf("%d", &option);

        error = option > 2 || option < 0 ? True : False;

        if(error)
            printf("\n Erro opção invalida! \n TENTE NOVAMENTE \n");

    } while(error);

    return option;
}
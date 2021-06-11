#include "string.h"
#include <ctype.h> 

#include "client.h"
#include "../files/files.c"
#include "../settings/settings.h"

#include "../tenis/tenis.h"
#include "../cart/cart.c"

#define True 1
#define False 0

struct clientData {

    int id;
    char name[100];
    char password[50];
    char email[100];
    char del;
    
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

            if(isLogin != -1){
                do{

                    option = MenuClientLogin();
                    switchLoginMenu(option, isLogin);

                }while(option != 0);
                
            }
                
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
    int erro = False;

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

    do{

        printf("Digite seu e-mail: ");
        ClearBuffer();
        fgets(client.email, 100, stdin);

        erro = getByEmail(client.email, fileClient);

        if(erro)
            printf("\nE-mail ja cadastrado tente um email diferente!\n\n");

    } while(erro);

    
    if(reg <= 0)
        fseek(fileClient, 0, SEEK_END);
    else 
        fseek(fileClient, (client.id - 1) * sizeof(client), SEEK_SET);

    fwrite(&client, sizeof(client), 1, fileClient);

    ClearWindows();
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
        ClearWindows();

        printf("\n\n\n ### FAZENDO LOGIN DO CLIENTE ### \n\n\n");

        printf("Email: ");
        ClearBuffer();
        fgets(email, 100, stdin);

        printf("Senha: ");
        ClearBuffer();
        fgets(password, 100, stdin);

        while (fread(&client, sizeof(client), 1, fileClient)){
            
            if(!strcmp(email, client.email) && !strcmp(password, client.password)){

                printf("\n Bem vindo %s \n", client.name);
                printf("Fazendo login...\n\n");
                

                return client.id;

            }

            i++;
        }

        printf("\n Sinto muito Email ou Senha incorreta! \n");


        do{

            printf("Deseja tentar novamente ? (S) Sim ou (N) Não: ");
            ClearBuffer();
            optionThen = toupper(getchar());

            if(optionThen != 'N' && optionThen != 'S')
                printf("Opção invalida tente novamente! \n");

        }while (optionThen != 'N' && optionThen != 'S');

        if(optionThen == 'N' | optionThen == 'n'){
            exitSignIN = True;
            error = True;
        }

    } while(!error || !exitSignIN);

    ClearWindows();

    return -1;

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
        printf("===================================\n");
        printf("        MENU DE COMPRAS \n");
        printf("===================================\n");

        MenuCart();

        printf("5 -> LISTAR TODOS OS TENIS \n");
        printf("===================================\n");

        printf("0 -> SAIR DA MINHA CONTA \n\n");
        printf("===================================\n");


        printf("Digite sua opção: ");
        ClearBuffer();
        scanf("%d", &option);

        error = option > 5 || option < 0 ? True : False;

        if(error)
            printf("\n Erro opção invalida! \n TENTE NOVAMENTE \n");

    } while(error);

    return option;
}

void switchLoginMenu(int option, int clientId){

    FILE *fileTenis;

    fileTenis = openFile("./files/tenis.dat");

    if(fileTenis == NULL)
        printf("\n ERRO de abertura do arquivo! \n");


    if(option > 0 && option < 5)
        switchCart(option, clientId);

    switch(option){

        case 5: 
            listTenis(fileTenis);
            break;
    }

    fclose(fileTenis);
}

void listClient( FILE *fileClient ){

    struct clientData client;

    fseek(fileClient, 0, SEEK_SET);

    while(fread(&client, sizeof(client), 1, fileClient)){
        if(client.del != '*'){
            printf("Id do cliente: %d\n", client.id);
            printf("Nome do cliente: %s\n", client.name);
            printf("Email do cliente: %s\n", client.email);
        }
    }
    
}

void deleteClient(FILE *fileClient){
    struct clientData client;
    int index;

    do{
        printf("Digite o codigo do cliente: ");
        ClearBuffer();
        scanf("%d", &client.id);

        index = getClient(client.id, fileClient);

        if(index < 0)
            printf("\n\n   ERRO!, codigo não existente, tente novamente!    \n\n");
            
    }while(index < 0);

    if(index > 0)
        eraseClient(index, fileClient);
    else 
        printf("Cliente não encontrado !!!\n");
}

void eraseClient(int index, FILE *fileClient){

    struct clientData client;

    fseek(fileClient, (index-1)*sizeof(client), SEEK_SET);

    fread(&client, sizeof(client), 1, fileClient);

    client.del = '*';

    fseek(fileClient, -sizeof(client), SEEK_CUR);

    fwrite(&client, sizeof(client), 1, fileClient);

    printf("Cliente apagado com sucesso!");
}

struct clientData readClient(int index, FILE *fileClient) {
	struct clientData client;
        
    fseek(fileClient, (index - 1) * sizeof(client), SEEK_SET);

    fread(&client, sizeof(client), 1, fileClient);

    printf("id: %d\n", client.id);

 	return client;
}

int getByEmail(char email [], FILE *file){

    struct clientData clientTmp;
    int erro;

    fseek(file, 0, SEEK_SET);

    while(fread(&clientTmp, sizeof(clientTmp), 1, file)){

        if(!strcmp(clientTmp.email, email))
            return erro = True;
            
    }

    return erro = False;

}
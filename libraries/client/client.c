#include "client.h"
#include "../settings/settings.h"
#include "string.h"

#define True 1
#define False 0

#define LENGTH 100

struct {

    int id;
    char name[100];
    char password[50];
    char email[100];

} client [LENGTH];

struct {

    int amountClient;

} controllClientInfos = {

    .amountClient = 0

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

    switch(optionMenuClient) {
        case 1: 
            registerCLient();
            break;
        case 2:
            loginClient();
            break;
        default:
            printf("\n Error escolha invalida! \n");
            break;
    }
}

void registerCLient(){

    int ClientID;

    if(controllClientInfos.amountClient == 0)
        ClientID = 0;
    else 
        ClientID = controllClientInfos.amountClient + 1;

    printf("\n\n\n ### REGISTRANDO CLIENTE ### \n\n\n");

    client[ClientID].id = ClientID;

    printf("Digite seu nome: ");
    ClearBuffer();
    fgets(client[ClientID].name, 100, stdin);

    printf("Digite sua senha: ");
    ClearBuffer();
    fgets(client[ClientID].password, 100, stdin);

    printf("Digite seu e-mail: ");
    ClearBuffer();
    fgets(client[ClientID].email, 100, stdin);

    controllClientInfos.amountClient += 1;

}

void loginClient(){
    char email[100];
    char password[100];
    int i;
    int error = False; 
    int exitSignIN = True;
    char optionThen;

    do {

        printf("\n\n\n ### FAZENDO LOGIN DO CLIENTE ### \n\n\n");

        printf("Email: ");
        ClearBuffer();
        fgets(email, 100, stdin);

        printf("Senha: ");
        ClearBuffer();
        fgets(password, 100, stdin);

        for(i = 0; i < controllClientInfos.amountClient; i++){

            if(!strcmp(email, client[i].email) && !strcmp(password, client[i].password)){

                printf("Nome: %s", client[i].name);
                printf("Fazendo login...");

                error = False;

            }else
                error = True;

        }

        if(error){
            printf("\n Sinto muito Email ou Senha incorreta! \n");

            printf("Deseja tentar novamente ? (S) Sim ou (N) Não: ");
            optionThen = getchar();

            if(optionThen == 'N' | optionThen == 'n'){
                exitSignIN = True;
                error = False;
            }

        }

    } while(error | !exitSignIN);

}
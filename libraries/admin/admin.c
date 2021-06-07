#include "admin.h"
#include "../files/files.h"
#include "../settings/settings.h"
#include "string.h"

#define True 1
#define False 0

struct adminData {

    int id;
    char name[100];
    char password[50];
    char email[100];

};


int MenuAdmin() {
    int option;
    int error = False;

    do {

        printf("\n \n MENU ADMINISTRADOR \n \n");
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

void switchAdminMenu(int optionMenuClient){

    struct adminData admin;
    int isLogin, option;

    /* ABRINDO ARQUIVOS */

    FILE *fileAdmin;

    fileAdmin = openFile("admin.dat");

    if(fileAdmin == NULL)
        printf("\n ERRO de abertura do arquivo! \n");

    switch(optionMenuClient) {
        case 1: 
            registerAdmin(admin, fileAdmin, -1);
            break;
        case 2:
            isLogin = loginAdmin(admin, fileAdmin);

            if(isLogin)
                option = MenuAdminLogin();

            break;
        default:
            printf("\n Error escolha invalida! \n");
            break;
    }

    fclose(fileAdmin);
}

void registerAdmin(
    struct adminData admin, 
    FILE *fileAdmin,
    int reg
){
    int index;

    printf("\n\n\n ### REGISTRANDO ADMINISTRADOR ### \n\n\n");

    do{
        printf("Digite o codigo do administrador: ");
        ClearBuffer();
        scanf("%d", &admin.id);

        index = getClient(admin.id, fileAdmin);

        if(index > 0)
            printf("\n\n   ERRO!, codigo ja existente, tente novamente!    \n\n");
            
    }while(index > 0);

    printf("Digite seu nome: ");
    ClearBuffer();
    fgets(admin.name, 100, stdin);

    printf("Digite sua senha: ");
    ClearBuffer();
    fgets(admin.password, 100, stdin);

    printf("Digite seu e-mail: ");
    ClearBuffer();
    fgets(admin.email, 100, stdin);

    if(reg <= 0)
        fseek(fileAdmin, 0, SEEK_END);
    else 
        fseek(fileAdmin, (admin.id - 1) * sizeof(admin), SEEK_SET);

    fwrite(&admin, sizeof(admin), 1, fileAdmin);
}

int loginAdmin(
    struct adminData admin, 
    FILE *fileAdmin
){
    char email[100];
    char password[100];
    int i;
    int error = False; 
    int exitSignIN = True;
    char optionThen;

    do {
        fseek(fileAdmin, 0, SEEK_SET);

        printf("\n\n\n ### FAZENDO LOGIN DO ADMINISTRADOR ### \n\n\n");

        printf("Email: ");
        ClearBuffer();
        fgets(email, 100, stdin);

        printf("Senha: ");
        ClearBuffer();
        fgets(password, 100, stdin);

        while (fread(&admin, sizeof(admin), 1, fileAdmin)){
            if(!strcmp(email, admin.email) && !strcmp(password, admin.password)){

                printf("\n Bem vindo %s !", admin.name);
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

int getAdmin(int id, FILE *nameFile){
    int idAdmin = 0;
    struct adminData admin;

    fseek(nameFile, 0, SEEK_SET);

    while (fread(&admin, sizeof(admin), 1, nameFile)){
        idAdmin++;

        if(id == admin.id)
            return idAdmin;
    }

    return -1;
    
}

int MenuAdminLogin() {
    int option;
    int error = False;

    do {

        printf("\n \n MENU ADM \n \n");

        printf("\n===================================\n\n");

        printf("1 -> LISTAR TODOS OS TENIS \n");
        printf("2 -> CONSULTAR UM TENIS \n");
        printf("3 -> ADICIONAR TENIS \n");
        printf("4 -> ALTERAR TENIS \n");
        printf("5 -> EXCLUIR TENIS \n");

        printf("\n===================================\n\n");

        printf("6 -> LISTAR TODOS OS CLIENTES \n");
        printf("7 -> EXCLUIR UM CLIENTE \n");

        printf("\n===================================\n\n");

        printf("8 -> LISTAR COMPRAS \n");

        printf("\n===================================\n\n");

        printf("0 -> SAIR DA MINHA CONTA \n\n\n");

        printf("\n===================================\n\n");

        printf("Digite sua opção: ");
        ClearBuffer();
        scanf("%d", &option);

        error = option > 8 || option < 0 ? True : False;

        if(error)
            printf("\n Erro opção invalida! \n TENTE NOVAMENTE \n");

    } while(error);

    return option;
}
#include <stdio.h>
#include <stdlib.h>

#include "./libraries/settings/settings.c"
#include "./libraries/client/client.c"
#include "./libraries/admin/admin.c"

#define True 1
#define False 0

int menuMain();

int main(void){
    int optionMenu, optionMenuClient, optionMenuAdmin;
    int amount = 0;
    
    do{
        
        optionMenu = menuMain();

        switch(optionMenu){
            case 1: 
                optionMenuClient = MenuClient();
                switchClientMenu(optionMenuClient);
                break;

            case 2:
                optionMenuAdmin = MenuAdmin();
                switchAdminMenu(optionMenuAdmin);
                break;
            case 3:
                deletePermanteTenis();
                printf("Cache do programa apagado ! \n");
                
                break;
            default:
                printf("SAINDO DO PROGRAMA ....\n\n\n");
        }
        
    }while(optionMenu != 0);    

}

// FUNCTIONS

int menuMain() {
    int option;
    int errorMenuOption = False;

    do {

        printf("\n \n MENU \n \n");
        printf("1 -> CLIENTE \n");
        printf("2 -> ADMINISTRADOR \n");
        printf("3 -> APAGAR CACHE \n");
        printf("0 -> SAIR DO PROGRAMA \n\n\n");

        printf("Digite sua opção: ");
        ClearBuffer();
        scanf("%d", &option);

        errorMenuOption = option > 3 || option < 0 ? True : False;

        if(errorMenuOption)
            printf("Erro opção invalida! \n TENTE NOVAMENTE \n");

    } while(errorMenuOption);

    return option;
}


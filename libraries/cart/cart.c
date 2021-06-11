#include <stdio.h>
#include "cart.h"
#include "../tenis/tenis.h"

#define True 1
#define False 0

struct tenisDataCart{
	int id;
	char del;
	char name[30];
	float price;
	int amount;
};

struct cartData {
    int id;
    struct tenisDataCart tenis;
    int clientId;
    char del;
};

void MenuCart() {

    printf("1 -> ADICIONAR UM TENIS NO CARRINHO \n");

    printf("===================================\n");

    printf("2 -> LISTAR CARRINHO \n");

    printf("===================================\n");

    printf("3 -> DELETAR TENIS DO CARRINHO \n");

    printf("===================================\n");

}

int listTenisCart( FILE *fileCart, FILE *fileTenis){

    struct cartData cart;

    int isEmptyCart = True;

    fseek(fileCart, 0, SEEK_SET);

    ClearWindows();

    while(fread(&cart, sizeof(cart), 1, fileCart)){

        if(cart.del != '*'){

            printf("id do carrinho: %d\n", cart.id);
            printf("id do cliente: %d\n", cart.clientId);
            printf("id do tenis: %d\n", cart.tenis.id);
            printf("nome do tenis: %s\n", cart.tenis.name);
            printf("preço do tenis: %.2f\n", cart.tenis.price);
            printf("quantidade do tenis no estoque: %d\n", cart.tenis.amount);

            isEmptyCart = False;

        }
            
    }
    
    return isEmptyCart;
     
}

struct tenisDataCart readTenisCart(int reg, FILE *fileTenis) {
	struct tenisDataCart tenis;

	fseek(fileTenis, (reg-1)*sizeof(tenis), SEEK_SET);

    fread(&tenis, sizeof(tenis), 1, fileTenis);

 	return tenis;
}

void registerTenisCart(
    struct cartData tenisCart, 
    FILE *fileCart,
    int reg,
    int idClient,
    FILE *fileTenis
){

    int index;

    int haveTenis = haveTenisStock(fileTenis);

    if(haveTenis){

        printf("\n\n\n ### REGISTRANDO TENIS NO CARRINHO ### \n\n\n");

        do{
            printf("Digite o codigo do carrinho: ");
            ClearBuffer();
            scanf("%d", &tenisCart.id);

            index = getTenis(tenisCart.id, fileCart);

            if(index > 0)
                printf("\n\n   ERRO!, codigo ja existente, tente novamente!    \n\n");
                
        }while(index > 0);

        tenisCart.clientId = idClient;

        do{
            printf("Digite o codigo do tenis: ");
            ClearBuffer();
            scanf("%d", &tenisCart.tenis.id);

            index = getTenis(tenisCart.tenis.id, fileTenis);

            if(index < 0)
                printf("\n\n   ERRO!,codigo não existente, tente novamente!    \n\n");
                
        }while(index < 0);

        tenisCart.tenis = readTenisCart(index, fileTenis);

        if(reg <= 0)
            fseek(fileCart, 0, SEEK_END);
        else 
            fseek(fileCart, (tenisCart.id - 1) * sizeof(tenisCart), SEEK_SET);

        fwrite(&tenisCart, sizeof(tenisCart), 1, fileCart);

        printf("Tenis adicionado no carrinho!\n");

    }
}


void switchCart(int option, int clientId ){

    struct cartData cart;
    int isEmptyCart;

    /* ABRINDO ARQUIVOS */

    FILE *fileCart;

    fileCart = openFile("./files/cart.dat");

    FILE *fileTenis;

    fileTenis = openFile("./files/tenis.dat");

    if(fileTenis == NULL || fileCart == NULL)
        printf("\n ERRO de abertura do arquivo! \n");


    switch(option){
        case 1:
            registerTenisCart(cart, fileCart, -1, clientId, fileTenis);
            break;
        case 2: 
            isEmptyCart = listTenisCart(fileCart, fileTenis);

            if(isEmptyCart)
                printf("\nO carrinho estar vazio!\n\n");

            break;
        case 3:
            deleteCartTenis(fileCart, fileTenis);
            break;
    }

    fclose(fileCart);
    fclose(fileTenis);
}

int getTenisCart(int id, FILE *nameFile){
    int idCart = 0;
     struct cartData cart;

    fseek(nameFile, 0, SEEK_SET);

    while (fread(&cart, sizeof(cart), 1, nameFile)){
        idCart++;

        if(id == cart.id && cart.del != '*')
            return idCart;
    }

    return -1;
    
}

void deleteCartTenis(FILE *fileCart, FILE *fileTenis){
    struct cartData cart;
    int index;

    ClearWindows();

    int haveTenis = haveTenisStock(fileTenis);

    if(haveTenis){
        do{
            printf("Digite o codigo do carrinho: ");
            ClearBuffer();
            scanf("%d", &cart.id);

            index = getTenisCart(cart.id, fileCart);

            if(index < 0)
                printf("\n\n   ERRO!, codigo não existente, tente novamente!    \n\n");
                
        }while(index < 0);

        if(index > 0)
            eraseCartTenis(index, fileCart);
        else 
            printf("Tenis não encontrado no carrinho !!!\n");
    }
    
}

void eraseCartTenis(int index, FILE *fileCart){
    struct cartData cart;

    fseek(fileCart, (index-1)*sizeof(cart), SEEK_SET);

    fread(&cart, sizeof(cart), 1, fileCart);

    cart.del = '*';

    fseek(fileCart, -sizeof(cart), SEEK_CUR);

    fwrite(&cart, sizeof(cart), 1, fileCart);

    printf("Tenis removido do carrinho!\n");
}
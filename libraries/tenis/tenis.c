#include <stdio.h>
#include <stdlib.h>
#include "tenis.h"

#define True 1
#define False 0

struct tenisData{
	int id;
	char del;
	char name[30];
	float price;
	int amount;
};

void menuTenis(){

    printf("\n===================================\n\n");

    printf("1 -> LISTAR TODOS OS TENIS \n");
    printf("2 -> CONSULTAR UM TENIS \n");
    printf("3 -> ADICIONAR TENIS \n");
    printf("4 -> ALTERAR TENIS \n");
    printf("5 -> EXCLUIR TENIS \n");
    printf("6 -> EXPORTAR TENIS EM XML\n");

    printf("\n===================================\n\n");
    
}

void switchTenisMenu(int optionMenuClient){

    struct tenisData tenis;
    int option;

    /* ABRINDO ARQUIVOS */

    FILE *fileTenis;

    fileTenis = openFile("./files/tenis.dat");

    if(fileTenis == NULL)
        printf("\n ERRO de abertura do arquivo! \n");

    switch(optionMenuClient) {
        case 1: 
            listTenis(fileTenis);
            break;
        case 2: 
            ConsultTenis(fileTenis);
            break;
        case 3: 
            registerTenis(tenis, fileTenis, -1);
            break;
        case 4:
            updateTenis(fileTenis);
            break;
        case 5:
            deleteTenis(fileTenis);
            break;
        case 6:
            exportTenis(fileTenis, "tenis.xml");
            break;
        default:
            printf("\n Error escolha invalida! \n");
            break;
    }

    fclose(fileTenis);
}

void ConsultTenis(FILE *fileTenis){
    struct tenisData tenis;
    int index;

    do{
        printf("Digite o codigo do tenis: ");
        ClearBuffer();
        scanf("%d", &tenis.id);

        index = getTenis(tenis.id, fileTenis);

        if(index < 0)
            printf("\n\n   ERRO!, codigo não existente, tente novamente!    \n\n");
            
    }while(index < 0);

    if(index > 0){
        tenis = readTenis(index, fileTenis);
        printf("Nome do tenis: %s\n", tenis.name);
        printf("Quantidade no estoque do tenis: %d\n", tenis.amount);
        printf("preço do tenis: R$%.2f\n", tenis.price);
    }else
        printf("Tenis não encontrado !!!\n");
}

int getTenis(int id, FILE *nameFile){
    int idTenis = 0;
    struct tenisData tenis;

    fseek(nameFile, 0, SEEK_SET);

    while (fread(&tenis, sizeof(tenis), 1, nameFile)){
        idTenis++;

        if(id == tenis.id && tenis.del != '*')
            return idTenis;
    }

    return -1;
    
}

void registerTenis(
    struct tenisData tenis, 
    FILE *fileTenis,
    int reg
){

    int index;

    printf("\n\n\n ### REGISTRANDO TENIS ### \n\n\n");

    do{
        printf("Digite o codigo do tenis: ");
        ClearBuffer();
        scanf("%d", &tenis.id);

        index = getTenis(tenis.id, fileTenis);

        if(index > 0)
            printf("\n\n   ERRO!, codigo ja existente, tente novamente!    \n\n");
            
    }while(index > 0);

    printf("Digite o nome do tenis: ");
    ClearBuffer();
    fgets(tenis.name, 30, stdin);

    printf("Digite o preço do tenis: ");
    ClearBuffer();
    scanf("%f", &tenis.price);

    printf("Digite a quantidade de tenis: ");
    ClearBuffer();
    scanf("%d", &tenis.amount);

    if(reg <= 0)
        fseek(fileTenis, 0, SEEK_END);
    else 
        fseek(fileTenis, (tenis.id - 1) * sizeof(tenis), SEEK_SET);

    fwrite(&tenis, sizeof(tenis), 1, fileTenis);
}

void writeTenis(
    struct tenisData tenis, 
    FILE *fileTenis,
    int reg
){
    if(reg <= 0)
        fseek(fileTenis, 0, SEEK_END);
    else 
        fseek(fileTenis, (tenis.id - 1) * sizeof(tenis), SEEK_SET);

    fwrite(&tenis, sizeof(tenis), 1, fileTenis);
}

void listTenis( FILE *fileTenis ){

    struct tenisData tenis;

    fseek(fileTenis, 0, SEEK_SET);

    printf("\nid                    nome                  preço   quantidade\n");

    printf("---------------------------------------------------------------------------\n");

    while(fread(&tenis, sizeof(tenis), 1, fileTenis)){
        if(tenis.del != '*')
            printf("%5d    %s   %.2f    %d\n", tenis.id, tenis.name, tenis.price, tenis.amount);
    }
    
}

struct tenisData readTenis(int reg, FILE *fileTenis) {
	struct tenisData tenis;

	fseek(fileTenis, (reg-1)*sizeof(tenis), SEEK_SET);

    fread(&tenis, sizeof(tenis), 1, fileTenis);

 	return tenis;
}

void updateTenis(FILE *fileTenis){
    struct tenisData tenis;
    int index;

    do{
        printf("Digite o codigo do tenis: ");
        ClearBuffer();
        scanf("%d", &tenis.id);

        index = getTenis(tenis.id, fileTenis);

        if(index < 0)
            printf("\n\n   ERRO!, codigo não existente, tente novamente!    \n\n");
            
    }while(index < 0);

    if(index > 0){
        tenis = readTenis(index, fileTenis);

        printf("Nome do tenis: %s\n", tenis.name);
        printf("Digite o nome do tenis: ");
        ClearBuffer();
        fgets(tenis.name, 30, stdin);

        printf("Quantidade no estoque do tenis: %d\n", tenis.amount);
        printf("Digite a quantidade de tenis: ");
        ClearBuffer();
        scanf("%d", &tenis.amount);

        printf("preço do tenis: R$%.2f\n", tenis.price);
        printf("Digite o preço do tenis: ");
        ClearBuffer();
        scanf("%f", &tenis.price);

        writeTenis(tenis, fileTenis, index);

    }else
        printf("Tenis não encontrado !!!\n");
    
}

void deleteTenis(FILE *fileTenis){
    struct tenisData tenis;
    int index;

    do{
        printf("Digite o codigo do tenis: ");
        ClearBuffer();
        scanf("%d", &tenis.id);

        index = getTenis(tenis.id, fileTenis);

        if(index < 0)
            printf("\n\n   ERRO!, codigo não existente, tente novamente!    \n\n");
            
    }while(index < 0);

    if(index > 0)
        eraseTenis(index, fileTenis);
    else 
        printf("Tenis não encontrado !!!\n");
}

void eraseTenis(int index, FILE *fileTenis){
    struct tenisData tenis;

    fseek(fileTenis, (index-1)*sizeof(tenis), SEEK_SET);

    fread(&tenis, sizeof(tenis), 1, fileTenis);

    tenis.del = '*';

    fseek(fileTenis, -sizeof(tenis), SEEK_CUR);

    fwrite(&tenis, sizeof(tenis), 1, fileTenis);
}

void deletePermanteTenis(){
    FILE *fileTenis, *tmpFile;
    struct tenisData tenis;

    fileTenis = openFile("./files/tenis.dat");
    tmpFile = fopen("./files/tenis.tmp", "wb");

    printf("antes tinha : %ld bytes\n", sizeof(fileTenis) * 8);

    if(fileTenis == NULL || tmpFile == NULL)
        printf("\n ERRO de abertura do arquivo! \n");

    fseek(fileTenis, 0, SEEK_SET);

    while (fread(&tenis, sizeof(tenis), 1, fileTenis)){
        if (tenis.del != '*')
			fwrite(&tenis, sizeof(tenis), 1, tmpFile);
    }
    	
    
    printf("agora tem tanto: %ld bytes \n", sizeof(tmpFile) * 8);

	fclose(fileTenis);
	fclose(tmpFile);

	remove("./files/tenis.dat");
	rename("./files/tenis.tmp", "./files/tenis.dat");

}

void exportTenis(FILE * fileTenis,  char nameFileXML[]){
    struct tenisData tenis;

    FILE *fileXML = fopen(nameFileXML, "w");
	if (fileXML == NULL)
		printf("\n ERRO de abertura do arquivo! \n");

    fseek(fileTenis, 0, SEEK_SET);

    fprintf(fileXML, "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n");
   	fprintf(fileXML, "<tenis>\n");

    while(fread(&tenis, sizeof(tenis), 1, fileTenis)){
        if(tenis.del != '*'){
            fprintf(fileXML, "    <tenis codigo=\"%d\">\n", tenis.id);
            fprintf(fileXML, "        <name>%s</name>\n", tenis.name);
            fprintf(fileXML, "        <preço>%.2f</preço>\n", tenis.price);
            fprintf(fileXML, "        <quantidade>%d</quantidade>\n", tenis.amount);
            fprintf(fileXML, "    </tenis>\n");
        }
    }

    fprintf(fileXML, "</tenis>\n");

    fclose(fileXML);

    printf("Expotando arquivo ... \n");
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tProduct{
	int id;
	char del;
	char name[45];
	float price;
	int amount;
};

int menuAdm(void);
FILE *openArchive(char []);
void addProduct(struct tProduct, int, FILE *);
int consultProduct(int, FILE *);
struct tProduct readProduct(int, FILE *);
void listProduct(FILE *);
void delProduct(int, FILE *);
//void delProduct(FILE **, char []);

int main(void){

	int opcao, id, pos;
	struct tProduct product;
	
	FILE *arcProduct = openArchive("product.dat");

	if(arcProduct==NULL){

	    printf("Erro! Não foi possivel abrir o arquivo.");
	    return 1;

	}

	do{
		opcao = menuAdm();

		switch(opcao){

			   case 1:
			        printf("~~~~~~	Inclusão	~~~~~~\n\n\n");

			          printf("Digite o ID do tenis:\n");
			          scanf("%d", &product.id);

			          printf("Digite o nome do tenis\n");
			          fflush(stdin);
			          fgets(product.name, 49, stdin);

			          printf("Digite o preço do tenis\n");
			          scanf("%f", &product.price);

			          addProduct(product, -1, arcProduct);
			        break;
					
				case 2:
				    printf("~~~~~~	Alteração	~~~~~~\n\n\n");
					printf("Digite o ID do produto:\n");
					scanf("%d", &id);
					
					break;	  
					
				case 3:
				    printf("~~~~~~	Consultar um produto especifico	~~~~~~\n\n\n");

					printf("Digite o ID do produto:\n");
					scanf("%d", &id);

					pos = consultProduct(id, arcProduct);

					if(pos > 0){
						product = readProduct(pos, arcProduct);
						printf("Nome do tenis ---: %s\n",	product.name);
						printf("Valor do tenis --: %.2f\n", product.price);
					   
					}   
					else
					    printf("Erro! Não foi possivel encontrar essa ID.\n");	
					
					break;
					
				case 4:

				    printf("~~~~~~	Consultar todos os produtos	~~~~~~\n\n\n");
					// listProduct(arcProduct);

					break;		
							
				case 5:
				    printf("~~~~~~	Exclusão	~~~~~~\n\n\n");
                    printf("Digite o ID do produto:\n");
					scanf("%d", &id);

					pos = consultProduct(id, arcProduct);

					// if(pos > 0)
					//     // delProduct(pos, arcProduct);
					// else
					//     printf("Erro! Não foi possivel encontrar essa ID.\n");    
					
					break;				      
		}
	}while(opcao != 0);

	fclose(arcProduct);

	return 0;
}

int menuAdm(void){

	int opcao;

	printf("~~~~~~~~~~ Menu do Administrador ~~~~~~~~~~\n\n");
	printf("1- Incluir\n");
	printf("2- Alteração\n");
	printf("3- Consultar um produto especifico\n");
	printf("4- Consultar todos os produtos\n");
	printf("5- Exclusão\n");
	printf("6- Sair do programa\n");
	printf("Escolha uma das opções acima:\n");

	scanf("%d", &opcao);

	return opcao;
}

FILE *openArchive(char archive[]){
	FILE *arc = fopen(archive, "r+b");

	if(arc==NULL)
	    arc=fopen(archive, "w+b");

	return arc;    
}

void addProduct(struct tProduct prod, int rec, FILE *arc){

	if(rec<=0)
		fseek(arc, 0, SEEK_END);
	else
	    fseek(arc, (rec-1)*sizeof(prod), SEEK_SET);

	fwrite(&prod, sizeof(prod), 1, arc);		
}

int consultProduct(int id1, FILE *arc){
	struct tProduct prod;
	int rec = 0;

	fseek(arc, 0, SEEK_SET);

    while(fread(&prod, sizeof(prod), 1, arc)){
	    rec++;

	 	if((prod.id == id1) && (prod.del != '*'));

    }

    return -1;
}

struct tProduct readProduct(int rec, FILE *arc){
	struct tProduct prod;
	fseek(arc, (rec-1)*sizeof(prod), SEEK_SET);
	fread(&prod, sizeof(prod), 1, arc);
	return prod;
}

// void listProduct(FILE *arc){
// 	struct tProduto prod;
// 	fseek(arc, 0, SEEK_SET);
//     while(fread(&prod, sizeof(prod), 1, arc))
// 	if(prod.del != '*')	
//         printf("ID ----------: %d", prod.id);
// 	    printf("Name --------: %s", prod.name);
// 	    printf("Pre%co ------: %.2f", prod.price);
	   
// }

// void delProduct(int rec, FILE *arc){
// 	struct tProduct prod;
// 	fseek(arc(rec-1)*sizeof(prod), SEEK_SET);
// 	fread(&prod, sizeof(prod), 1, arc);
// 	prod.del = '*';
// 	fseek(arc, -sizeof(prod), SEEK_CUR);
// 	fwrite(&prod, sizeof(prod), 1, arc);
// }

//void delProduct(FILE **arc, char archive[]){

// 	struct tProduct prod;
// 	FILE *archive = fopen("product.aux", "wb");
// 	if(arcAux==NULL)
// 	   return;
// 	fseek(*arc, 0, SEEK_SET);
// 	while(fread(&prod, sizeof(prod), 1, *arcAux));
// 	    if(prod.del != '*')
// 		    fwrite(&prod, sizeof(prod), 1, arcAux);
// 		fclose(*arc);
// 		fclose(arcAux);
// 		remove("product.aux", archive);
// 		*arc = openArchive(archive);
	   
// }



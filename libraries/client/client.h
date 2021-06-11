/*

*/

#ifndef CLIENT_H
#define CLIENT_H


int MenuClient();

void switchClientMenu(int);

void registerCLient();

int loginClient();

int getClient(int id, FILE *nameFile);

int MenuClientLogin();

void switchLoginMenu(int option, int clientId);

void listClient( FILE *fileClient );

void deleteClient(FILE *fileClient);

void eraseClient(int index, FILE *fileClient);

struct clientData readClient(int id, FILE *fileClient);

int getByEmail(char email [], FILE *file);

#endif
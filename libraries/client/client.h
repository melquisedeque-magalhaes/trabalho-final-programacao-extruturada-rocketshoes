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

#endif
#include <stdio.h>

/*

*/

#ifndef ADMIN_H
#define ADMIN_H

int MenuAdmin();

void switchAdminMenu(int);

void registerAdmin();

int loginAdmin();

int getAdmin(int id, FILE *nameFile);

int MenuAdminLogin();

void eraseAdmin(int index, FILE *fileAdmin);

void deleteAdmin(FILE *fileAdmin);

void listAdmin( FILE *fileAdmin );

#endif
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

#endif
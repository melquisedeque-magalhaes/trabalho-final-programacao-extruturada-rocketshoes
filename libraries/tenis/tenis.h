#include <stdio.h>

/*

*/

#ifndef TENIS_H
#define TENIS_H

void menuTenis();

void switchTenisMenu(int optionMenuClient);

int getTenis(int id, FILE *nameFile);

void registerTenis();

void listTenis(FILE *fileTenis );

void ConsultTenis(FILE *fileTenis);

struct tenisData readTenis(int reg, FILE *fileTenis);

void updateTenis(FILE *fileTenis);

void writeTenis(
    struct tenisData tenis, 
    FILE *fileTenis,
    int reg
);

void deleteTenis(FILE *fileTenis);

void eraseTenis(int index, FILE *fileTenis);

void deletePermanteTenis();

void exportTenis(FILE * fileTenis, char nameFileXML[]);

#endif
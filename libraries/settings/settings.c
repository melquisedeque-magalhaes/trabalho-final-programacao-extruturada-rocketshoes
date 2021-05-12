#include "settings.h"

#include <stdio.h>
#include <stdlib.h>

void ClearBuffer(){
    #ifdef __unix__
        #include <stdio_ext.h>
        __fpurge(stdin); // Limpar o Buffer do Teclado no Linux

    #elif defined(_WIN32) || defined(WIN32) 
        fflush(stdin); // Limpar o Buffer do Teclado no Windows

    #endif
}

void ClearWindows(){
    #ifdef __unix__         
        system("clear");

    #elif defined(_WIN32) || defined(WIN32) 
        system("cls");

    #endif
}

#include <stdio.h>

/*

*/

#ifndef CART_H
#define CART_H

void MenuCart();
void switchCart(int option, int idClient);
void listTenisCart( FILE *fileTenis );
void registerTenisCart();
void deleteCartTenis(FILE *fileCart);
void eraseCartTenis(int index, FILE *fileCart);

#endif
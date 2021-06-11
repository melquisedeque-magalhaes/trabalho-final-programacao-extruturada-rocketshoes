#include <stdio.h>

/*

*/

#ifndef CART_H
#define CART_H

void MenuCart();
void switchCart(int option, int idClient);
int listTenisCart( FILE *fileCart, FILE *fileTenis );
void registerTenisCart();
void deleteCartTenis(FILE *fileCart, FILE *fileTenis);
void eraseCartTenis(int index, FILE *fileCart);

#endif
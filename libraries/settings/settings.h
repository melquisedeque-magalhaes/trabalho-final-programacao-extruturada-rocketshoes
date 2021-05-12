/*
    Essa biblioteca tem por objetivo salvar as funções padrão para o funcionamento do programa
    essa função são para adaptar o programar funcionar correntamente no sistema unix e no sistema
    windows.
*/

#ifndef SETTINGS_H
#define SETTINGS_H

// Função para limpar o buffer do teclado tanto no unix quanto no linux
void ClearBuffer(); 

 // Função para limpar a tela quanto no unix quanto no windows
void ClearWindows();

#endif
//
// Created by bartosz bugla on 19/12/2021.
//

#ifndef MONOPOLYV2_BOARD_H
#define MONOPOLYV2_BOARD_H
#include <struct.h>
// funkcja odpowiada za inicjalizację gry
// wczytuje dane z pliku w postaci stringu
// podaje kazda linijke do funckji convert
//a pozniej wykorzystuje objekt TileInfo do wygenrowania struktury Tile (Możnabybylo to znacznie uprościć)
// obiektu board
//jesli wczytujemy gre ustawia wartosc na wartosc z wczytanej gry
Tile* initBoard();
//inicjalizuje graczy ustawia wszystkie wartosc na defaultowe
//jesli wczytujemy gre ustawia wartosc na wartosc z poprzedniej gry
Player* initPlayers();
// powyższe funckje powinno się wywołać tylko raz !!!!!!!!!!!

//generuje całą planszę wraz ze stanem konta danego gracza
//przed wywołaniem funckji powinno sie uzyć komendy clearScreen
void generateBoard( int currentPlayer);
#endif

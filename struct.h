

#ifndef MONOPOLYV2_STRUCT_H
#define MONOPOLYV2_STRUCT_H
#include <string>
#include <iostream>
using namespace std;
//liczba graczy podaje gracz
extern int playerNumber;
//rozmiar planszy bazowo 40
extern const int boardSize;

enum class tile_type{
    normal ,
    event,
    nothing,
};
// struktura pola
struct Tile{
    string name;
    tile_type  type= tile_type::normal;
    int price = 0;
    int level= 0 ;
    int cost[4];
    int ownerId = -1;
    string monopoly;
    int upgrade_cost= 0;
    string eventName;

};
//strutkrua grazca
struct Player{
    int money = 0 ;
//    string color;
    string name="";
    int *items = new int[boardSize];
    int position;
    char symbol;
    int jail;
};
//struktura pomaga w inicjalizacji gry ( nie optymalne )
struct TileInfo{
    string name;
    tile_type type= tile_type::normal;
    int price = 0;
    int upgradeCost = 0;
    int cost[4]{};
    string monopoly;
    string eventName = "";

};
// struktura pomaga w utworzeniu menu
//message : wiadomosc która sie wyswietli
//key : fraza którą należy wpisac aby odpalić funkcję
//f : funkcja któ®a sie stanie po wpisaniu frazy
//cont : czy nalezy kontynuować to menu, czy go opuścić ( lekko zbugowane )
struct Option{
    string message = " ";
    string key = " " ;
    const function<void()> f = [](){ cout<<"You forgot to enter a callback :( "<<endl;};
    bool cont = false;
};
// Globalna tablica graczy
extern Player* players;
// globalna tablica planszy
extern Tile* board;
//globalna obecna tura
extern int turn;
//ściezka do pliku .exe
//poprostu lekkie zabezpieczenie
extern string path;

#endif //MONOPOLYV2_STRUCT_H

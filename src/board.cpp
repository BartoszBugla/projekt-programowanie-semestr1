
#include  "../headers/struct.h"
#include <iostream>
#include "../headers/functions.h"
#include <fstream>

TileInfo* tilesInfoArray = new TileInfo[boardSize];
void readFromFile (){
    fstream file;
    //path
    file.open(path+"/default.txt", ios::in);

    int i = 0 ;
    if(file.good()){
        while(!file.eof()){
            Tile tile;
            string linia;
            getline(file , linia);
            tilesInfoArray[i] = convert(linia);
            i++;
        }
    }
    else{
        cerr << "Nie mozna wczytac planszy!!!"<<endl;
    }

}

Tile* initBoard(){
    readFromFile();
    Tile* b = new Tile[boardSize];

    for (int i = 0; i < boardSize; ++i) {
        b[i].type = tilesInfoArray[i].type;
        b[i].name = tilesInfoArray[i].name;
        b[i].price = tilesInfoArray[i].price;
        b[i].monopoly = tilesInfoArray[i].monopoly;
        b[i].eventName = tilesInfoArray[i].eventName;
        b[i].upgrade_cost = tilesInfoArray[i].upgradeCost;
        for (int j = 0; j < 4; ++j) {
            b[i].cost[j] = tilesInfoArray[i].cost[j];
        }
    }
    delete[] tilesInfoArray;
    return b;

}
void generateBoard(int currentPlayer){
    int tilesInOneRow = 4;

    cout << endl;

    for (int i = 0; i < boardSize; i++) {
        int color = 37;
        int basePlayerColor = 31;

        string tileName;
        //jesli pole to event lub start
        if(board[i].type == tile_type::event || board[i].type == tile_type::nothing){
             tileName = board[i].name;
             color = 36;
        //normalne pole do kupienia
        }else if(board[i].type == tile_type::normal) {

            //jesli miasto jest juz kupione
            if (board[i].ownerId > -1) {
                color = basePlayerColor + board[i].ownerId;
                tileName = board[i].name + " " + to_string(board[i].cost[board[i].level]) + "$" + " lvl:" + to_string(board[i].level);
            }else {
                tileName = board[i].name + " " + to_string(board[i].price) + "$" + " ";
            }

        }
        //dodaj pusta spacje
        tileName += " ";
        int playersOnTileCount = 0;
        for (int j = 0; j < playerNumber; ++j) {
            if( i == players[j].position){
                tileName = tileName + "\033[1;"+to_string(basePlayerColor+j)+"m"+ players[j].name+ " "+"\033[0m" ;
                playersOnTileCount++;
            }}
        //wyrownaj string do 30 znakow
        while(tileName.length() - playersOnTileCount*11 < 30){
            tileName = tileName + " ";
        }
        cout << "|";
        //kolorowe wyswieltnie nazwy gracza
        cout<<"\033[0;"<<color<<"m"<< tileName<<"\033[0m";
        cout.width(1);
        wcout << "|  ";
        if((i+1)%tilesInOneRow == 0 )
            cout << endl<<endl;
        }

    cout << endl;
    cout << "Cześć "<<"\033[1;" <<currentPlayer+31 <<"m"<< players[currentPlayer].name <<"\033[0m\n" << endl;
    cout <<"Obecna tura : "<<turn<<endl;
    cout << "Stan konta : "<< players[currentPlayer].money<<endl;


}
Player* initPlayers(){

    Player *playerList = new Player[playerNumber];
    clearScreen();
    cout << "Nazwa gracza moze miec makymalnie 10 znakow oraz nie moze zawierac spacji."<<endl;
    cout <<endl;
    string name;
    cin.ignore();
    for (int i = 0; i < playerNumber; ++i) {

        ask:

            cout << "Podaj nazwe "<< i+1<<" gracza: ";
            getline(cin,name);




        if(name.length() > 10) {
            cout << " Za dluga nazwa gracza!"<<endl;
            goto ask;
        }

        if( name.find(" ") != string::npos){
            cout << "Prosilem bez spacji."<<endl;
            goto ask;
        }

        playerList[i].name=name;

    }
    //give money
    for (int i = 0; i < playerNumber; ++i) {
        playerList[i].money = 3000;
        playerList[i].position = 0 ;
    }
    return playerList;

}

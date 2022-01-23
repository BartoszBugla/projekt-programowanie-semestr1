//
// Created by bartosz bugla on 02/01/2022.
//
#include<fstream>
#include "../headers/struct.h"
#include <string>
#include <iostream>
using namespace std;
void save(){
    ofstream file;

    file.open(path+"/testsave.bin", ios::binary);
    if(file.is_open()){
            file.write((char*)(&board[0]), sizeof(Tile) * boardSize );
            file.write((char*)(&players[0]), sizeof(Player) * playerNumber);
            file.write((char*)(&turn), sizeof(int));
            file.write((char*)(&playerNumber),sizeof(int));
        cout <<" zapisano gre pomyslnie "<<endl;

    }else {
        cerr << "Z jakiegos powodu nie mozna zapisac pliku. Przepraszam :( "<<endl ;
    }
    file.close();
}
bool load(){
    ifstream file;

    file.open(path+"/testsave.bin", ios_base::binary);
    if (file.is_open())
    {
        board = new Tile[boardSize];
        players = new Player[2];
        file.read((char*)(&board[0]), sizeof(Tile)* 40 );
        file.read((char*)(&players[0]), sizeof(Player)*2);
        file.read((char*)(&turn),sizeof(int));
        file.read((char*)(&playerNumber),sizeof(int));
        file.close() ;
        return true;
    }else {
        return false;
    }
}
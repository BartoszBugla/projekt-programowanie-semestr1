#include <iostream>
#include "headers/functions.h"
#include "headers/struct.h"
#include "headers/board.h"
#include "headers/game.h"
#include "headers/saveload.h"
using namespace std;

int askForNumber(){
    string pnum;
    cout <<"Podaj liczbe graczy (2-4) "<<endl;
    cin >> pnum;
    if(pnum =="4"){
        return 4;
    }else if (pnum =="2"){
        return 2;

    }else if (pnum=="3"){
        return 3;
    }else {
         cout << "Wpisales nie to o co cie prosilem. Sproboj ponownie."<<endl;
         return askForNumber();
    }


}
void initGame(){
    playerNumber = askForNumber();
   while(playerNumber < 2 || playerNumber > 5 ){
       playerNumber = askForNumber();
   }

//sdsds
    board = initBoard();
     players = initPlayers();

    game();
}
void loadGame(){
    load();
    cout << "Load success"<<endl;
    game();

}
int main(int argc,char* argv[]) {
    path = argv[0];
    path = path.substr(0, path.find_last_of("/"));
    clearScreen();

    cout << "\033[1;31m" <<"Zalecane jest granie na pelnym ekranie" <<"\033[0m\n" <<endl;
    Option options[]{{"1.Rozpocznij gre." , "1" ,initGame, false },
                      {"2.Wyjdz" ,"2",[](){},true },
                      {"3.Wczytaj gre" , "3" , loadGame , true}
    };
    option_menu(options,3);


}
//
// Created by bartosz bugla on 23/12/2021.
//

#include "../headers/struct.h"
#include "../headers/board.h"
#include "../headers/functions.h"
#include <iostream>
typedef void (*IntFunctionWithOneParameter) (int player_id);
void trigger_event(int currentPlayer, string event="random");
void go_to_jail(int player_id){
    cout << "Niestey idziesz do więzienia :( "<<endl;
    players[player_id].jail = 3 ;
    players[player_id].position = 31 ;
    cout << "Ale możesz zapłacić 200$, aby z niego wyjść"<<endl;
    Option options[]={{"1. Zostań w więzieniu","1",[](){},},
                {"2. Zaplać aby wyjść","2",[&player_id]() {
                            if (players[player_id].money > 200) {
                                players[player_id].money -= 200;
                                players[player_id].jail = 0;
                                cout << "zaplaciles 200$ aby wyjsc" << endl;
                                cout << "Twoj stan konta teraz:" << players[player_id].money << endl;
                            }else {
                                cout <<"Niestety nie stac cie. Kolejne 3 tury spędzisz w więzieniu."<<endl;
                            }
                        }
        }};
        option_menu(options , 2 ,clearScreen );
}
void bills200(int player_id){
    cout<<"Niestety musisz zaplacic podatek w wysokosci 200$"<<endl;
    players[player_id].money-=200 ;
    cout << "Twoj stan konta teraz:"<< players[player_id].money<<endl;

}
void bills100(int player_id){
    cout<<"Niestety musisz zaplacic podatek w wysokosci 100$"<<endl;
    players[player_id].money-=100;
    cout << "Twoj stan konta teraz:"<< players[player_id].money<<endl;

}
void birthday50(int player_id){
    cout<<"Masz urodziny z tej okazji dajesz kazdemu graczowi 50$"<<endl;
    int value = 50 ;
    int total_money  = value* (playerNumber-1);
    players[player_id].money -= total_money;
    for (int i = 0; i < playerNumber; ++i) {
        if(i != player_id){
            players[i].money+= value;
        }
    }
    cout << "Twoj stan konta teraz:"<< players[player_id].money<<endl;
}
void lottery(int player_id){
    int value = 50*random(1,4);
    players[player_id].money+=value;
    cout <<"Wow udalo ci sie wygrać "<< value<<"$ na loterii"<<endl;
    cout << "Twoj stan konta teraz:"<< players[player_id].money<<endl;

}
void add150(int player_id){
    players[player_id].money+=150;
    cout << "Zostalo ci dodane 150$ do konta"<<endl;
    cout << "Twoj stan konta teraz:"<< players[player_id].money<<endl;
}
void hospital(int player_id){
    players[player_id].jail = 2 ;
    players[player_id].money -=200;
    cout <<"Trafiasz do szpitala spedzisz tu 2 tury i musisz wydac 200$ za leczenie"<<endl;
    cout << "Twoj stan konta teraz:"<< players[player_id].money<<endl;
}

void trigger_event(int player_id,string eventName ){
    clearScreen();
    generateBoard(player_id);
    IntFunctionWithOneParameter random_events[4]= {
            bills100,
            bills200,
            birthday50,
            go_to_jail


    };

    if(eventName == "bills100"){
        bills100(player_id);
    }else if(eventName == "bills200") {
        bills200(player_id);
    }else if(eventName == "add150"){
        add150(player_id);
    }else if(eventName == "jail"){
        go_to_jail(player_id);
    }else if(eventName=="lottery"){
        lottery(player_id);
    }else if(eventName=="hospital"){
        hospital(player_id);
    }
    else if(eventName == "random" ){
        int num = random(0,3);

        IntFunctionWithOneParameter event = random_events[num];
        event(player_id);

    }


}
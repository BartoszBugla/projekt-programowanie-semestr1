#include <string>
#include <iostream>
#include <random>
#include <ctime>
#include <thread>
#include <chrono>
#include "../headers/struct.h"
using namespace std;
void clearScreen(){
//wersja windows
//system("cls);
//wesja mac linux
    system("clear");
}
mt19937 generator(time(nullptr));

int random(int a, int b ){
    uniform_int_distribution<int> number(a, b);

    return number(generator);;
}
void wait(int milliseconds ){
    this_thread::sleep_for(chrono::milliseconds (milliseconds));
}
TileInfo convert(string line){
    string tab[10];
    string delimiter = " ";
    size_t pos = 0;
    string token;
    int i = 0 ;
    while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        tab[i] = token;
        i++;
    }
    TileInfo pole;
    if(tab[0] == "event" || tab[0]=="Event"){
        pole.name = tab[1];
        pole.type = tile_type::event;
        pole.eventName = tab[2];

    }else if(tab[0]=="start" || tab[0]== "Start"){
        pole.name = tab[0];
        pole.type = tile_type::nothing;
    }
    else if(tab[0].length() > 0){
        pole.name = tab[0];
        pole.type = tile_type::normal;
        pole.price = stoi(tab[1]);
        pole.cost[0] = stoi(tab[2]);
        pole.cost[1] = stoi(tab[3]);
        pole.cost[2] = stoi(tab[4]);
        pole.cost[3] = stoi(tab[5]);
        pole.upgradeCost = stoi(tab[6]);
        pole.monopoly = tab[7];
    }


    return pole;

}
void input_to_continue(){

    string a;
    cout << endl << "Wpisz cokolwiek aby kontunowac...";
    cin >> a;
}
int option_menu(Option opt[] , int size , const function<void()> initF = [](){}){
    //usunac spacje
    string choice;
    while(true){
        choice = "";
        initF();
        for (int i = 0; i < size; ++i) {
            cout << opt[i].message<<endl;
        }
        cout << "Twoj wybor: ";
        cin >> choice;

        bool correct = false;
        for (int i = 0; i < size; ++i) {
            if(choice == opt[i].key){
                correct = true;
                 opt[i].f();
                 if(opt[i].cont == true){
                     goto cont;
                 }
                 goto br;
            }
        }
        if(!correct){
            cout <<" Nie znam takiej komendy :("<<endl;
            wait(333);
             continue;
        }
        cont:
            continue;
        br:
            break;
    }
    return 0;
}



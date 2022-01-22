#include "../headers/struct.h"
#include <iostream>
#include "../headers/events.h"
#include "../headers/board.h"
#include "../headers/functions.h"
#include "../headers/saveload.h"
//opis znajduje sie przy samej deklaracji
void dice_roll(int);
void show_list(int);
void show_list_of_all();
void on_normal_tile(int currentPlayer, int pos);
bool is_monopoly(int currentPlayer , int pos);
bool check_jail(int currentPlayer);
void upgrade(int player_id, int pos);
void sell(int player_id , int pos );
bool check_if_any_mono(int player_id);
//czy ulepszono juz pole
bool upgradedTile = 0 ;
void game(){

    while(true){
        if(turn == 50) break;
        int currentPlayer = turn % playerNumber;
        //check if winner

            if(players[currentPlayer].money < 0 ) {turn++; continue;}
            int pleft = 0;
            int winnerId = -1;
        //sprawdzamy ile graczy ma wiecej niz 0$
            for (int i = 0; i < playerNumber; ++i) {
                if(players[i].money > 0 ) {
                    pleft++;
                    winnerId = i ;
                    continue;
                }
            }
            // jezeli zostal jeden gracz to konczymy gre
        if(pleft == 1){
            clearScreen();
            cout << "Gra zakonczyla sie zwycieza "<<players[winnerId].name<<endl;
            input_to_continue();
            delete[] players;
            delete[] board;
            break;
        }
            bool isJail = check_jail(currentPlayer);
            if(isJail){
                players[currentPlayer].jail--;
                cout << "Niestety ale gracz "<<players[currentPlayer].name<< " jest w więzeiniu"<<endl;
                cout << "Jeszcze przez "<< players[currentPlayer].jail<<" tury"<<endl;
                input_to_continue();
                turn++;
                continue ;
            }
            upgradedTile = 0 ;

            auto initFunction = [&currentPlayer](){
                clearScreen();
                generateBoard(currentPlayer);
                if(check_if_any_mono(currentPlayer) && upgradedTile == 0 ){
                    cout << "\033[1;" <<31 <<"m"<<"Mozesz ulepszyc jakies pole!"<<"\033[0m\n"<<endl;
                }

            };

            Option opt[] ={
                    {"1.Rzut kostka","1",[&currentPlayer](){dice_roll(currentPlayer);},false},
                    {"2.Lista posiadanych pol (ulepsz, sprzedaj) " ,"2" , [&currentPlayer](){ show_list(currentPlayer);} , true},
                    {"3.Lista wszystkich miast(sprawdz informacje na temat miasta)" , "3" ,show_list_of_all , true},
                    {"4.Zapisz grę" , "4" , save , true }
            };
             option_menu(opt , 4 ,initFunction);
        turn++;
        }


}
//wyswietla informacje o dnanym polu
void show_info(int city_id){

     cout << "Nazwa pola: " << board[city_id].name<<endl;
    cout << "Cena zakupu: " << board[city_id].price<<endl;
    cout << "Wlasiciciel: " << players[board[city_id].ownerId].name<<endl;
    cout << "Poziom pola: " << board[city_id].level<<endl;
    cout << "Cena za postoj poziom 0: " << board[city_id].cost[0]<<endl;
    cout << "Cena za postoj poziom 1: " << board[city_id].cost[1]<<endl;
    cout << "Cena za postoj poziom 2: " << board[city_id].cost[2]<<endl;
    cout << "Cena za postoj poziom 3: " << board[city_id].cost[3]<<endl;
    cout << "Cena ulepszenia pola to : "<< board[city_id].upgrade_cost<<endl;
}
//wyswietla lsite wszystkich pol
void show_list_of_all(){
    clearScreen();
    int choice = 0;
    cout << "wybierz numer 0 aby wyjsc lub inny numer aby zobaczyc informacje o polu.";
    for (int i = 0; i < boardSize ; ++i) {
        cout << i+1<< ". " << board[i].name <<endl;
    }
    while(true){
        cin>>choice;
        if(choice==0){
            break;
        }else if ( choice >0 && choice <boardSize){
            show_info(choice-1);
            continue;
        }
    }
}
void give_money_for_passing_start(int player_id , int value){
    players[player_id].money +=value;
    cout << "zostalo ci dodane 250$"<<endl;
    wait(500);
}
//rzut kostka
void dice_roll(int currentPlayer){

    cout << "rzucam kostką..."<<endl;

    wait(500);

    int rolled  = random(1,6);
    cout << "Wylosowano "<<  rolled <<endl;
    int *pos = &players[currentPlayer].position;
    //animacja ruchu
    for (int i = 0 ;i < rolled; ++i) {
        *pos += 1;
        if(*pos > boardSize-1 ){
            give_money_for_passing_start(currentPlayer,250);
            *pos = 0;
        }
        wait(333);
        clearScreen();
        generateBoard(currentPlayer);
        cout << "Wylosowano "<<  rolled <<endl;
    }

    wait(1000);
    clearScreen();
    generateBoard(currentPlayer);

    if(board[*pos].type == tile_type::normal){
        on_normal_tile(currentPlayer,*pos);

    }else if(board[*pos].type == tile_type::event) {
        trigger_event(currentPlayer, board[*pos].eventName);
    }

    input_to_continue();

}
//wyswietla liste twoich pól
void show_list(int currentPlayer){
    while(true){
        int choice= -1;
        clearScreen();
        generateBoard(currentPlayer);
        bool atleastOne = false ;
        int list[40]{};
        int iterator = 1;
        for (int i = 0; i < boardSize; ++i) {
            if(players[currentPlayer].items[i] == 1){
                cout <<iterator<< ". "<< board[i].name <<endl;
                list[iterator]=i;
                atleastOne= true ;
                iterator++ ;
            }
        }
        if(!atleastOne){
            cout << "Narazie niczego nie  posiadasz:( "<<endl;
            string a;
            cout<<"Wpisz cokolwiek aby wyjsc z listy : ";
            cin >> a;
            return;
        }

        cout <<"Wpisz 0 aby wrocic"<<endl;
        cout << "Wybierz pole: ";
        cin >> choice;
        if(choice == 0){
            break;
        }else if(choice > 0 && choice < 40){
            int cityId = list[choice];
            if(cityId == 0 ){
                cout << "Taki numer nie znajduje sie na liscie :("<<endl;
                wait(500);
                continue;
            }
            auto initFunction = [&cityId](){
                clearScreen();
                show_info(cityId);
            };
            Option upgradeMenu[3] ={{"0.Cofnij","0",[](){} , false},
                                        {"1.Sprzedaj" , "1",[&currentPlayer,&cityId](){sell(currentPlayer,cityId);},false   },
                                        {"2.Ulepsz","2", [&currentPlayer,&cityId](){ upgrade(currentPlayer,cityId);} ,true }};

            option_menu(upgradeMenu, 3 ,initFunction);
        }else {
            cout <<"Nie znam takiej komendy :("<<endl;
        }
    }
    clearScreen();
    generateBoard(currentPlayer);

}
void on_normal_tile(int currentPlayer,int pos){
    //buy f
    auto buy = [&currentPlayer, &pos](){
        if (players[currentPlayer].money - board[pos].price > 0) {
            players[currentPlayer].items[pos] = 1;
            board[pos].ownerId = currentPlayer;
            players[currentPlayer].money -= board[pos].price;
            clearScreen();
            generateBoard(currentPlayer);

            cout << "Gratulacje " << board[pos].name << " nalezy teraz do ciebie! ";
        }
    };
    // Puste pole
    if(board[pos].ownerId  == -1) {
        cout <<endl<<"*********************************************"<<endl;
        show_info(pos);
        cout <<"*********************************************"<<endl<<endl;
        cout << "Czy chcesz kupic " << board[pos].name << " za : " << board[pos].price << "$" << endl;
        cout << "Twoj stan po transkacji bedzie wynosil: "<< players[currentPlayer].money - board[pos].price<< "$"<<endl;

        Option options[2] = {{"1.Tak" , "1" ,buy , false } , {"2.Nie " , "2" , [](){} , false}};

        option_menu(options,2 );

        }else if(board[pos].ownerId == currentPlayer){
        cout <<"Jestes na swoim polu, nic sie nie dzieje "<<endl;
    }
    //zajete pole
    else{
        bool is_mono = is_monopoly(board[pos].ownerId , pos );
        int multiplier = 1;
        int value = board[pos].cost[board[pos].level];
        if(is_mono) multiplier = 2 ;
        //odbierz pieniadze
        players[currentPlayer].money -= value* multiplier;
        //dodaj pieniadze
        players[board[pos].ownerId].money += value*multiplier;

        cout << "O nie wszedles na pole innego gracza !" << endl;
        cout << value << "$" << " zostalo przekazane do gracza " << players[board[pos].ownerId].name << endl;

    }

};
//sprawdza czy dany gracz ma na danym polu monopol
bool is_monopoly(int player_id , int pos ){
    string mono = board[pos].monopoly;
    bool is_monopoly = true;
    for (int i = 0; i < boardSize; ++i) {
       if(board[i].monopoly == board[pos].monopoly && board[i].ownerId != player_id) {
           is_monopoly = false;
       }

    }
    return is_monopoly;
}
//ulepsza pole
void upgrade(int player_id, int pos ){
    bool is_mono = is_monopoly(player_id,pos);

    if(upgradedTile){
        cout << "Juz ulepszyles jakies pole w tej turze, sproboj ponownie w kolejnej. "<<endl;
        input_to_continue();
        return;

    }
    if(player_id != board[pos].ownerId) {
        cout << "To pole nie nalezy do ciebie nie mozesz go ulepszyć";
        input_to_continue();
        return;
    };
    if(is_mono){
        players[player_id].money -= board[pos].upgrade_cost;
        board[pos].level++;
        upgradedTile = 1 ;
        cout <<"Udalo ci sie ulepszyc pole: "<< board[pos].name<< endl;
    }else {
        cout << "Nie masz na tym polu monopolu wiec nie mozesz go ulepszyć"<<endl;
    }
    input_to_continue();
}
//sprawdza czy gracz jest w wiezieniu
bool check_jail(int currentPlayer){
    bool isJail = false;
     if(players[currentPlayer].jail > 0  ){
         isJail = true;

     }
     return isJail;

}
//sprzedaje pole do banku za pol ceny
void sell(int player_id , int pos ){
    auto confirm_sell = [&player_id , &pos](){
        players[player_id].items[pos] = -1;
        board[pos].ownerId = -1;
        players[player_id].money += board[pos].price/2;
        cout <<" Sprzedales to pole "<<endl;

    };
    clearScreen();
    cout <<"Czy napewno chcesz sprzedac "<<board[pos].name<<" otrzymasz za to: "<< board[pos].price/2<<endl;
    Option opt[2] = {{"0.Nie ", "0", []() {},      false},
                     {"1.Tak",  "1", confirm_sell, false},};
    option_menu(opt , 2 );

}
//spradza czy mamy gdzies monopol, czyli czy mozna ulepszyc jakies pole
bool check_if_any_mono(int player_id){
    string name;
    for (int i = 0; i < boardSize; ++i) {
        if(is_monopoly(player_id,i)){
            return true;
        }

    }
    return false;
}

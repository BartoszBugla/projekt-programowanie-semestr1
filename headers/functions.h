//
// Created by bartosz bugla on 19/12/2021.
//

#ifndef MONOPOLYV2_FUNCTIONS_H
#define MONOPOLYV2_FUNCTIONS_H
#include <string>
#include "struct.h"
//czysci okno konsoli
void clearScreen();

//losuje liczbe w przediale od a do b
int random(int a, int b);

//zatrzymuje dzialanie programu na ilosc milisekund podana jako argument
void wait(int milliseconds);

//zamienia striga w obiekt w którym znajduja się informajce o polu
TileInfo convert(string );

//wyswietla napis "wpisz cokolwiek aby kontynuowac..."
void input_to_continue();


//odpowiada za generowanie menu
//gdzie ostatni argument to funckja lambda "const function<void()>", szczerze poporstu skopiowane z internetu
//nie do konca wiem co oznacza ale daje mozliwosc podania definicji funkcji jako argument
//co w tym przyadpku jest bardzo przydatne

//funckja init odpala sie przed każdym wyświetleniem menu
int option_menu(Option opt[], int size,const function<void()> init = [](){});
#endif //MONOPOLYV2_FUNCTIONS_H

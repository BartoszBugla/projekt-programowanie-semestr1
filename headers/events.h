//
// Created by bartosz bugla on 23/12/2021.
//

#ifndef MONOPOLYV2_EVENTS_H
#define MONOPOLYV2_EVENTS_H
//Funckja odpowiada za wywołanie jakiegos zdarzenia na planszy np: dodanie graczowi 150$
//pierwszy argument odpowiada za gracza na ktorym sie ma dane zdarzenie wydarzyć
//drugi argument odpowiada za nazwe eventu w postaci stringu
//Wszystki możliwe funckje znajdują sie w samym pliku .cpp lub w pliku instrukcja.txt

void trigger_event(int player_id, string eventName);
#endif //MONOPOLYV2_EVENTS_H

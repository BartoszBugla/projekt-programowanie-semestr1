# Projekt na programowanie - Monopoly 
## Opis 
Projekt miał na celu wiernie na odtworzyć podstawowe mechaniki popularnej gry planszowej "Monopoly" .
Do tych mechanik należą m.in.:
* rzut kostką 
* ruch pionka
* kupno, sprzedaż, ulepszenie pola
* mechanika budżetu
* warunki zwycięstwa
* zdarzenia losowe oraz zdarzenia stale(wiezeinie , szpital itd.)
* mechanika monopolu  

Dodatkowo gra miała zawierać: 
* wczytywanie planszy z pliku 
* zapis odczyt gry 
* wybór ilośći graczy 

## Najwazniejsze funkcje kodu 
Wszystkie funkcje opisane sa w kodzie.

### OptionMenu (functions)

Funckja odpowiada za generowanie prostego menu opcji 
```
$ struct Option{
$   string message = " ";
$   string key = " " ;
$   const function<void()> f = [](){ };
$   bool cont = false;
$ };
$
$ int option_menu ( Option opt[], int size , const function<void()>  init = [](){});
$
```
init  funkcja, która dzieje sie przed wyświetleniem całego menu ( w moim projekcie stosowana to wyswietlenia większości menu wyboru) 
Option to tablica struktur opcji podajemy tam : 
* wiadomość, która się ma wyświetlić 
* string , który należy wpisać, aby włączyć podaną funcje podaną 
* f to podana funkcja, która ma się stać po wisaniu stringa "key" 
* cont - czy po wpisaniu danej opcji mamy wyjść z menu (po rzucie kostką wychdozimy z menu, natomiast po wybraniu opcji pokaz liste miast nie konczymy pętli) 

### Convert (functions) 
Zamienia nam linijke z pliku na strukture. 

### LoadFromFile (board) 
Wczytuje linijki z pliku default.txt 

### Plik saveload.cpp
Save -  zapisują binarnie do pliku dane o strukturze board , players i informacje o aktualnej turze. 
Load - wczytuje i zapisuje dane do globalnych zmiennych. 

### Plik game.cpp
Zawiera wszystkie większośc funkcji odpowiadzlanych za podstawowwe mechaniki. 

Za każdą petlą po koleji: 

Sprawdzamy:
* Liczbe graczy, którzy posiadają więcej niż 0$, jeżeli jest tylko jeden gracz to kończymy grę
* Czy gracz, którego tura ma więcej niż 0$
* Czy gracz jest w więzieniu
* Czy dany gracz ma jakiś monopol
* Czy dany gracz ulepszył już pole 
* czy dany gracz może ulepszyć jakieś pole (warunkowane na podstawie powyzszych kroków) 

Każdą turę kończymy rzutem kostką, pózniej następuje ruch pionka. 
Później w zaleności od na jakim polu staniemy dzieje się funckja, możliwości:
* puste, nie zakupione pole do kupna 
* kupione pole przez innego gracza 
* pole eventu 
* pole startu (nic sie nie dzieje) 

### trigger_event 
Włącza funkje podaną jako string. Opiera sie na prostym switchu.
Jeżeli podamy parametr "random" , wtedy losuje się jedna z kilku funkcji podanych w tablicy.  




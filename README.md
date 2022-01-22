# Projekt na programowanie - Monopoly 
## Opis 
Projekt miał na celu wiernie na odtworzyć podstawowe mechaniki popularnej gry planszowej "Monopoly" .
Do tych mechanik należą m.in.:
* rzut kostką 
* ruch pionka
* kupno, sprzedaż, ulepszenie pola
* mechanika budżetu
* warunki zwycięstwa
* zdarzenia losowe oraz zdarzenia stale (więzienie , szpital itd.)
* mechanika monopolu  

Dodatkowo gra miała zawierać: 
* wczytywanie planszy z pliku 
* zapis i odczyt gry 
* wybór ilośći graczy 

## Najważniejsze funkcje kodu 
Wszystkie funkcje opisane są w kodzie. Lista kilku najciekawszych.

### OptionMenu (functions)

Funkcja odpowiada za generowanie prostego menu opcji 
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
init  funkcja, która dzieje sie przed wyświetleniem całego menu ( w moim projekcie stosowana do czyszczenia ekranu i generowania nowego ekranu planszy ) 
Option to tablica struktur opcji podajemy tam: 
* wiadomość, która się ma wyświetlić 
* string, który należy wpisać, aby włączyć funkcję
* f to podana funkcja, która ma się stać po wpisaniu stringa "key" 
* cont - czy po wpisaniu danej opcji mamy wyjść z menu (po rzucie kostką wychdozimy z menu, natomiast po wybraniu opcji pokaż listę, nie kończymy pętli) 

### Convert (functions) 
Zamienia nam linijkę z pliku na strukturę. 

### LoadFromFile (board) 
Wczytuje po koleji linijki z pliku default.txt. 

### Plik saveload.cpp
Save - zapisują binarnie do pliku dane o strukturze board, players i informacje o aktualnej turze. 
Load - wczytuje i zapisuje dane do globalnych zmiennych. 

### Plik game.cpp
Zawiera wszystkie większość funkcji odpowiadzialnych za podstawowe mechaniki. 

W każdym obiegu petli sprawdzamy:
* Liczbę graczy, którzy posiadają więcej niż 0$, jeżeli jest tylko jeden gracz to kończymy grę
* Czy gracz, którego jest tura ma więcej niż 0$
* Czy gracz jest w więzieniu
* Czy dany gracz ma jakiś monopol
* Czy dany gracz ulepszył już pole 
* czy dany gracz może ulepszyć jakieś pole (warunkowane na podstawie powyższych kroków) 

Każdą turę kończymy rzutem kostką, pózniej następuje ruch pionka. 
Możliwości po rzucie kostki:
* puste, nie zakupione pole do kupna 
* kupione pole przez innego gracza 
* pole eventu 
* pole startu (nic się nie dzieje) 

### trigger_event 

Włącza funkcje na podstowie stringu. Opiera sie na prostym switchu.

Jeżeli podamy parametr "random" , wtedy losuje się jedna z kilku funkcji podanych w tablicy.  




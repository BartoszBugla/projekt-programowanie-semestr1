# Projekt na programowanie - Monopoly 
## 1.Opis projektu.
Projekt miał na celu, wiernie odtworzyć popularną grę planszową “Monopoly”, wraz z jej podstawowymi mechanikami.
## 2. Wymagania 
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
* wybór ilości graczy 

## 3. Przebieg realizacji

Projekt składa się z  plików: 
### main.cpp
Następuje inicjalizacja gry poprzez stworzenie nowej lub wczytanie poprzedniej. 
### board.cpp
W pliku znajdują się funkcje odpowiedzialne za stworzenie planszy, wczytanie danych o planszy z pliku oraz ogólną inicjalizacji gry. 


#### Funkcja LoadFromFile 
Wczytuje po koleji linijki z pliku default.txt. 
### functions.cpp
Zawiera funkcje pomocnicze np:losowanie liczby, czyszczenie ekranu
Funkcja OptionMenu odpowiada za generowanie prostego menu opcji 
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
* f to podana tzw. funkcja lambda , która ma się stać po wpisaniu stringa "key" 
 funkcja lambda ma to do siebie, że może ją deklarować gdziekolwiek.
* cont - czy po wpisaniu danej opcji mamy wyjść z menu (po rzucie kostką wychdozimy z menu, natomiast po wybraniu opcji pokaż listę, nie kończymy pętli) 
### struct.cpp 
Zawiera struktury oraz zmienne globalne 
### game.cpp
Zawiera wszystkie większość funkcji odpowiedzialnych za podstawowe mechaniki. 

W każdym obiegu pętli sprawdzamy:
* Liczbę graczy, którzy posiadają więcej niż 0$, jeżeli jest tylko jeden gracz to kończymy grę
* Czy gracz, którego jest tura ma więcej niż 0$
* Czy gracz jest w więzieniu
* Czy dany gracz ma jakiś monopol
* Czy dany gracz ulepszył już pole 
* czy dany gracz może ulepszyć jakieś pole (warunkowane na podstawie powyższych kroków) 
Każdą turę kończymy rzutem kostką, pózniej następuje ruch pionka. 
W pliku znajdują się funkcje kupna, sprzedaży, ulepszenia , płacenia innymi graczu oraz funkcje sprawdzania stanu naszych posiadłości jak i lista opisu wszystkich pól
### events.cpp
Znajdują się tam wszystkie mechaniki pól “event” 
Włącza funkcje na podstawie stringu. Opiera się na prostym switchu.
Jeżeli podamy parametr "random" , wtedy losuje się jedna z kilku funkcji podanych w tablicy.  

### saveload.cpp
Save - zapisują binarnie do pliku dane o strukturze board, players i informacje o aktualnej turze. 
Load - wczytuje i zapisuje dane do globalnych zmiennych. 
## 4. Instrukcja użytkownika 
Po włączeniu gry dostajemy menu, w którym można stworzyć nową grę lub wczytać zapisaną. Po wpisaniu ilości graczy oraz wyboru nazw graczy otwiera się menu gracza. Widzimy nas stan gry oraz możliwe akcje. Możemy sprawdzić opis naszych posiadłości, sprzedać i ulepszyć (jeżeli jest taka możliwości). Ulepszyć można pole jeżeli mamy na nim monopol, czyli mamy wszystkie pola należące do tej samej kategorii.Program poinformuje nas, jeżeli jest mamy jakikolwiek monopol. W bazowej wersji mapy pola należące do tej samej kategorii są oddzielone polami zdarzeń (pomarańczowe) oraz polami akcji ( w cudzysłowiu ) . Jeżeli gracz stworzy własną mapę, może się to różnić.
Przykład Monopolu:

![Screenshot](Screenshot 2022-01-23 at 13.15.16.png)

Możliwości po rzucie kostki:

* puste, nie zakupione pole do kupna 
* kupione pole przez innego gracza 
* pole eventu 
* pole startu (nic się nie dzieje) 

### Jak tworzyć własne mapy: 
W pliku "default.txt" każda linijka to jedno pole, pól musi być 40, 
a pierwsza linijka to zawsze powinno być pole start.
Jak budować pole miasta: 
1) nazwa miasta (nie może być event lub start)
2) cena (liczba całkowita)
3) ilość, która zapłaci gracz ,  który stanie na polu jeżeli miasto ma poziom 0 (liczba całkowita)
4) -||- poziom 1 (liczba całkowita) 
5) -||- poziom 2 (liczba całkowita)
6) -||- poziom 3 (liczba całkowita)
7) cena ulepszenia (liczba całkowita)
8) monopol, do którego należy miasto np (sklep, Europa, skl, a)
Każdą instrukcje trzeba zakończyć spacja!!!!!!!!!!!!!!!
, po której można napisać cokolwiek w podstawowym pliku jest to liczba linijki 
Jak budować pole jakiegoś wydarzenia: 
1)wpisujemy "event"
2)nazwa pola 
3)funkcja
Lista funkcji: 

Bills100,bills200,hospital,jail,random,add150,lottery,birthday50

Plansza w programie generowana jest na podstawie pliku default.txt, więc plik z naszą planszą musi mieć taką nazwę.
## 5. Podsumowanie i wnioski.
Udało mi się zrealizować wszystkie, postawione sobie cele. Zaczynając od tych banalnych, a kończąc na tych nieco bardziej zaawansowanych. O dziwo największym problemem był mój system operacyjny. Mianowicie, brak dostępu do funkcji, pozwalających zarządzać ekranem konsoli. Przez co kilka pomysłów, który przyszły mi w trakcie tworzenia nie udało się zrealizować. Gdyby wystarczyło mi czasu, to napewno dodałbym jeszcze licytacje pól, zoptymalizowałbym kod pod względem przejrzystości oraz stworzyłbym możliwości kilku zapisów. 






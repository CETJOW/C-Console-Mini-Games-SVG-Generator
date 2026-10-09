#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <string>

using namespace std;
const int ttt_size = 3;
const int w_size = 8;

void wypisz_menu();
void menu();
void pomoc();
void SVG_basic();
bool sprawdzenie(int lx1, int ly1, int lx2, int ly2, int cx, int cy, int cr, int rx, int ry, int rw, int rh);
void SVG_advanced();
void KolkoKrzyzyk();
void plansza_ASCII_ttt(char plansza[3][3]);
void plansza_SVG_ttt(char plansza[3][3]);
bool wygrana_ttt(char plansza[3][3], char gracz);
int trwanie_gry(char plansza[3][3]);
void komputer_ttt(char plansza[3][3]);
void plansza_ASCII_w(char szachownica[8][8]);
void plansza_SVG_w(char szachownica[8][8]);
void WarcabyGra();
bool wygrana_warcaby(char szachownica[8][8]);
void aktualizuj_plansze(char szachownica[8][8]);

int main() {
    srand(time(NULL));
    menu();
    return 0;
}


//====================FUNKCJE===========================
//Funkcje MENU
void wypisz_menu() {
    cout << "\n1 - generowanie podstawowego pliku SVG\n";
    cout << "2 - generowanie zaawansowanego pliku SVG z własnymi kształtami\n";
    cout << "3 - gra w kolko i krzyzyk\n";
    cout << "4 - gra warcaby\n";
    cout << "5 - pomoc\n";
    cout << "X - Wyjscie z programu\n";
    cout << "Wybierz opcje: \n";
}

void menu() {
    char wybor = '0';
    do {
        wypisz_menu();
        cin >> wybor;
        switch (wybor)
        {
        case '1': SVG_basic();
            break;
        case '2': SVG_advanced();
            break;
        case '3': KolkoKrzyzyk();
            break;
        case '4': WarcabyGra();
            break;
        case '5': pomoc();
            break;
        case 'x': cout << "Konczenie programu\n";
            break;
        case 'X': cout << "Konczenie programu\n";
            break;
        default:
            cout << "Wprowadzono bledny znak!!!\n";
            break;
        }
    } while (wybor != 'X' && wybor != 'x');
}

void pomoc() {
    cout << "\nJesli chcesz zakonczyc program nalezy wpisac X(lub x)i potwierdzic przyciskiem enter";
    cout << "\nOpcja numer 1 tworzy podstawowy, pusty plik SVG";
    cout << "\nOpcja numer 2 tworzy plik SVG w ktorym dodaje sie ksztalty o zadanych przez uzytkownika parametrach.";
    cout << "\nAby utworzyc taki plik trzeba dla kazdego z 3 ksztaltow podac parametry o ktore prosi program. Wspolrzedne tych elementow nie moga wychodzic poza wymiary pliku svg.";
    cout << "\nOpcja numer 3 pozwala uzytkownikowi zagrac w kolko i krzyzyk. Aby postawic swoj znak uzytkownik musi podac gdzie chce go postawic (miejsca sa ponumerowane od 1-3 i tak nalezy okreslac swoj ruch).";
    cout << "\nJesli zaden uzytkownik nie wygra i nie bedzie juz zadnych wolnych pol gra zakonczy sie remisem.";
    cout << "\nOpcja numer 4 pozwala uzytkownikowi zagrac w warcaby. Aby ruszyc swoim pionkiem gracz musi podac najpierw koordynaty swojego pionka a pozniej pole na ktorym chce go postawic.";
    cout << "\nAby zbic pionek przeciwnika trzeba podac pole na ktorym sie wyladuje po zbiciu przeciwnika";
}
//DLA SVG
//Funkcja ta tworzy podstawowy, pusty plik svg
void SVG_basic() {
    ofstream plik("basic.svg");
    if (plik.is_open()) {
        plik << "<?xml version=\"1.0\" encoding = \"UTF-8\"?>\n";
        plik << "<svg width =\"1000\" height = \"1000\" xmlns = \"http://www.w3.org/2000/svg\">\n";
        plik << "</svg>";
        cout << "Utworzono plik\n";
        plik.close();
    }
    else cout << "Nie utworzono pliku";
}
//Funkcja ta sprawdza czy koordynaty podane przez uzytkownika nie wykraczaja poza wymiary pliku svg
bool sprawdzenie(int lx1, int ly1, int lx2, int ly2, int cx, int cy, int cr, int rx, int ry, int rw, int rh) {
    if (lx1 > 1000 || ly1 > 1000 || lx2 > 1000 || ly2 > 1000 || cx > 1000 || cy > 1000 || rx > 1000 || ry > 1000) return false;
    return true;
}
//Funkcja ta odpowiada za tworzenie pliku SVG z kolem, prostokatem i linia o koordynatach i wymniarach podanych przez uzytkownika
void SVG_advanced() {
    ofstream plik("advanced.svg");
    int lx1, ly1, lx2, ly2, cx, cy, cr, rx, ry, rw, rh;
    if (plik.is_open()) {
        string kolorL;
        string kolorR;
        string kolorC;
        do {
            cout << "\nPodaj polozenie dwoch koncow linii(x1 y1 i x2 y2) oraz jej kolor (po angielsku) : ";
            cin >> lx1 >> ly1 >> lx2 >> ly2 >> kolorL;
            cout << "\nPodaj położenie srodka okregu, jego promien oraz kolor (po angielsku): ";
            cin >> cx >> cy >> cr >> kolorC;
            cout << "\nPodaj położenie prostokata, jego szerokosc, wysokosc oraz jego kolor (po angielsku): ";
            cin >> rx >> ry >> rw >> rh >> kolorR;
            if (sprawdzenie(lx1, ly1, lx2, ly2, cx, cy, cr, rx, ry, rw, rh) == false) cout << "\nWprowadzono niepoprawne wspolrzedne obiektow!!! Wprowadz ponownie\n";
        } while (sprawdzenie(lx1, ly1, lx2, ly2, cx, cy, cr, rx, ry, rw, rh) == false);
        plik << "<?xml version=\"1.0\" encoding = \"UTF-8\"?>\n";
        plik << "<svg width =\"1000\" height = \"1000\" xmlns = \"http://www.w3.org/2000/svg\">\n";
        plik << "<rect x=\"" << rx << "\" y=\"" << ry << "\" width=\"" << rw << "\" height=\"" << rh << "\" fill=\"" << kolorR << "\"/>\n";
        plik << "<circle cx=\"" << cx << "\" cy =\"" << cy << "\" r=\"" << cr << "\" fill=\"" << kolorC << "\"/>\n";
        plik << "<line x1=\"" << lx1 << "\" y1=\"" << ly1 << "\" x2=\"" << lx2 << "\" y2=\"" << ly2 << "\" stroke=\"" << kolorL << "\" stroke-width=\"5\"/>\n";
        plik << "</svg>";
        plik.close();
        cout << "Utworzono plik\n";
    }
    else cout << "Nie utworzono pliku\n";
}
//FUNKCJE DO GRY W WARCABY

//Funkcja tworzy plansze do kółka i krzyżyk w ASCII
void plansza_ASCII_ttt(char plansza[3][3]) {
    const int rozmiar = 3;
    for (int i = 0; i < rozmiar; i++) {
        cout << plansza[i][0] << " | " << plansza[i][1] << " | " << plansza[i][2] << endl;
        if (i < 2) cout << "--+---+---\n";
    }
}

//Funkcja tworzy plansze do kółka i krzyżyk w pliku SVG
void plansza_SVG_ttt(char plansza[3][3]) {
    ofstream plik("plansza_ttt.svg");
    if (plik.is_open()) {
        plik << "<?xml version=\"1.0\" encoding = \"UTF-8\"?>\n";
        plik << "<svg width =\"600\" height = \"600\" xmlns = \"http://www.w3.org/2000/svg\">\n";
        plik << "<line x1=\"0\" y1=\"200\" x2=\"600\" y2=\"200\" stroke=\"black\" stroke-width=\"5\"/>\n";
        plik << "<line x1=\"0\" y1=\"400\" x2=\"600\" y2=\"400\" stroke=\"black\" stroke-width=\"5\"/>\n";
        plik << "<line x1=\"200\" y1=\"0\" x2=\"200\" y2=\"600\" stroke=\"black\" stroke-width=\"5\"/>\n";
        plik << "<line x1=\"400\" y1=\"0\" x2=\"400\" y2=\"600\" stroke=\"black\" stroke-width=\"5\"/>\n";
        for (int i = 0; i < ttt_size; i++)
        {
            for (int j = 0; j < ttt_size; j++)
            {
                if (plansza[i][j] == 'O') plik << "<circle cx=\"" << 100 + (200 * j) << "\" cy =\"" << 100 + (200 * i) << "\" r=\"" << 80 << "\" fill=\"" << "none" << "\" stroke=\"blue\" stroke-width=\"5\"/>\n";
                else if (plansza[i][j] == 'X') {
                    plik << "<line x1=\"" << 0 + (200 * j) << "\" y1=\"" << 0 + (200 * i) << "\" x2=\"" << 200 + (200 * j) << "\" y2=\"" << 200 + (200 * i) << "\" stroke=\"" << "red" << "\" stroke-width=\"5\"/>\n";
                    plik << "<line x1=\"" << 0 + (200 * j) << "\" y1=\"" << 200 + (200 * i) << "\" x2=\"" << 200 + (200 * j) << "\" y2=\"" << 0 + (200 * i) << "\" stroke=\"" << "red" << "\" stroke-width=\"5\"/>\n";
                }
            }
        }
        plik << "</svg>";
        plik.close();
        cout << "utworzono plansze svg\n";
    }
    else cout << "nie udalo sie utworzyc pliku!\n";
}
//Funkcja sprawdza czy nie zajeto juz wszystkich mozliwych pol na planszy
int trwanie_gry(char plansza[3][3]) {
    int zajete_pola = 0;
    for (int i = 0; i < ttt_size; i++) {
        for (int j = 0; j < ttt_size; j++) {
            if (plansza[i][j] != ' ') zajete_pola++;
        }
    }
    if (zajete_pola == 9) return 1;
    return 0;
}
//Funkcja ta sprawdza czy zostal juz spelniony warunek wygranej przez jednego z graczy
bool wygrana_ttt(char plansza[3][3], char gracz) {
    for (int i = 0; i < ttt_size; i++) {
        if (plansza[0][i] == gracz && plansza[1][i] == gracz && plansza[2][i] == gracz) return true;
        else if (plansza[i][0] == gracz && plansza[i][1] == gracz && plansza[i][2] == gracz) return true;
    }
    if (plansza[0][0] == gracz && plansza[1][1] == gracz && plansza[2][2] == gracz) return true;
    else if (plansza[0][2] == gracz && plansza[1][1] == gracz && plansza[2][0] == gracz) return true;
    return false;
}
//Funkcja ta jest 'sercem' gry w kolko i krzyzyk i umozliwia graczom ruchy
void KolkoKrzyzyk() {
    int x, y;
    char pola[3][3]{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', };
    char Gracz = 'O';
    char komputer = '0';
    double time_1 = 0;
    double time_2 = 0;
    double time_end = 30.0;

    cout << "\nCzy chcesz grac na komputer?[t/n]";
    while (komputer != 't' && komputer != 'n') {
        cin >> komputer;
        if (komputer != 't' && komputer != 'n') cout << "\nWprowadzono nieprawidlowy znak. Sprobuj ponownie";
    }

    plansza_ASCII_ttt(pola);
    plansza_SVG_ttt(pola);
    while (trwanie_gry(pola) == 0) {
        auto start = chrono::steady_clock::now();
        if (komputer == 't' && Gracz == 'X') komputer_ttt(pola);
        else {
            cout << "\nRunda gracza " << Gracz << " Postaw swoj znak: ";
            cin >> x >> y;
            if (x <= 3 && x >= 1 && y <= 3 && y >= 1 && pola[x - 1][y - 1] == ' ') {
                pola[x - 1][y - 1] = Gracz;
            }
            else {
                cout << "\nNieprawidlowy ruch. Sprobuj ponownie";
                auto koniec = chrono::steady_clock::now();
                chrono::duration<double> czas = koniec - start;
                if (Gracz == 'O') time_1 += czas.count();
                else if (Gracz == 'X') time_2 += czas.count();
                continue;
            }
        }
        auto koniec = chrono::steady_clock::now();
        chrono::duration<double> czas = koniec - start;
        if (Gracz == 'O') time_1 += czas.count();
        else if (Gracz == 'X') time_2 += czas.count();
        if (time_1 >= time_end) {
            cout << "\nKoniec czasu!! Wygrał gracz X";
            break;
        }
        else if (time_2 >= time_end) {
            cout << "Koniec czasu!! Wygrał gracz O";
            break;
        }
        plansza_ASCII_ttt(pola);
        plansza_SVG_ttt(pola);
        cout << "\nWykonano ruch. Pozostaly czas: ";
        if (Gracz == 'O') cout << time_end - time_1 << " sekund\n";
        else if (Gracz == 'X') cout << time_end - time_2 << "sekund\n";
        if (wygrana_ttt(pola, Gracz) == true) {
            cout << "\nKoniec gry! Wygrał gracz " << Gracz << endl;
            break;
        }
        else if (trwanie_gry(pola) == 1) cout << "\nBrak wolnych miejsc, Remis";
        Gracz = (Gracz == 'O') ? 'X' : 'O';
    }
}
//Funkcja odpowiada za ruchy komputera w ttt 
void komputer_ttt(char plansza[3][3]) {
    int randomX = 0;
    int randomY = 0;
    //Sprawdzenie czy mozna wygrac
    for (int i = 0; i < ttt_size; i++) {
        for (int j = 0; j < ttt_size; j++) {
            if (plansza[i][j] == ' ') {
                plansza[i][j] = 'X';
                if (wygrana_ttt(plansza, 'X') == true) return;
                else plansza[i][j] = ' ';
            }
        }
    }
    //Sprawdzenie czy mozna zablokowac wygrywajacy ruch przeciwnika
    for (int i = 0; i < ttt_size; i++) {
        for (int j = 0; j < ttt_size; j++) {
            if (plansza[i][j] == ' ') {
                plansza[i][j] = 'O';
                if (wygrana_ttt(plansza, 'O') == true) {
                    plansza[i][j] = 'X';
                    return;
                }
                else plansza[i][j] = ' ';
            }
        }
    }
    //losowy ruch jesli nie mozna niczego innego zrobic
    while (1 == 1) {
        randomX = (rand() % 3);
        randomY = (rand() % 3);
        if (plansza[randomX][randomY] == ' ') {
            plansza[randomX][randomY] = 'X';
            return;
        }
    }

}
//===========================WARCABY=========================
void plansza_ASCII_w(char szachownica[8][8]) {
    cout << "   1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 \n";
    for (int i = 0; i < w_size; i++) {
        for (int j = 0; j < w_size; j++) {
            if (((i == 0 || i == 2) && (j + 1) % 2) || ((i == 1) && (j + 1) % 2 == 0)) szachownica[i][j] = 'c';
            else if ((i == 6 && (j + 1) % 2) || ((i == 7 || i == 5) && (j + 1) % 2 == 0)) szachownica[i][j] = 'b';
            else szachownica[i][j] = ' ';
        }
    }
    for (int i = 0; i < w_size; i++) {
        cout << i + 1 << "| ";
        for (int j = 0; j < w_size; j++) {
            cout << szachownica[i][j] << " | ";
        }
        cout << "\n  --------------------------------\n";
    }
}

void aktualizuj_plansze(char szachownica[8][8]) {
    cout << "   1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 \n";
    for (int i = 0; i < w_size; i++) {
        cout << i + 1 << "| ";
        for (int j = 0; j < w_size; j++) {
            cout << szachownica[i][j] << " | ";
        }
        cout << "\n  --------------------------------\n";
    }
}


void WarcabyGra() {
    char plansza[8][8] = {};
    char Gracz = 'b';
    char Przeciwnik = 'c';
    int bicie_x, bicie_y;
    int ruch_x1, ruch_y1, ruch_x2, ruch_y2, kierunek;
    plansza_ASCII_w(plansza);
    plansza_SVG_w(plansza);
    while (wygrana_warcaby(plansza) == false) {
        kierunek = (Gracz == 'b') ? 1 : -1;
        cout << "\nRunda gracza " << Gracz << " Wykonaj swoj ruch: ";
        cin >> ruch_x1 >> ruch_y1 >> ruch_x2 >> ruch_y2;
        bicie_x = (ruch_x1 + ruch_x2) / 2;
        bicie_y = (ruch_y1 + ruch_y2) / 2;
        if (plansza[ruch_x1 - 1][ruch_y1 - 1] == Gracz && plansza[ruch_x2 - 1][ruch_y2 - 1] == ' ' && (ruch_x1 - ruch_x2) == kierunek && abs(ruch_y1 - ruch_y2) == 1) {
            plansza[ruch_x1 - 1][ruch_y1 - 1] = ' ';
            plansza[ruch_x2 - 1][ruch_y2 - 1] = Gracz;
        }
        else if (plansza[ruch_x1 - 1][ruch_y1 - 1] == Gracz && plansza[ruch_x2 - 1][ruch_y2 - 1] == ' ' && plansza[bicie_x - 1][bicie_y - 1] == Przeciwnik) {
            plansza[ruch_x1 - 1][ruch_y1 - 1] = ' ';
            plansza[ruch_x2 - 1][ruch_y2 - 1] = Gracz;
            plansza[bicie_x - 1][bicie_y - 1] = ' ';
            continue;
        }
        else {
            cout << "\nZly ruch!! Sprobuj ponownie: \n";
            continue;
        }
        aktualizuj_plansze(plansza);
        plansza_SVG_w(plansza);
        Gracz = (Gracz == 'b') ? 'c' : 'b';
        Przeciwnik = (Przeciwnik == 'c') ? 'b' : 'c';
    }
    cout << "Koniec Gry! Wygraly pionki ";
    if (Gracz == 'b') cout << "czarne";
    else cout << "biale";
}

bool wygrana_warcaby(char szachownica[8][8]) {
    int pionki_b = 0;
    int pionki_c = 0;
    for (int i = 0; i < w_size; i++) {
        for (int j = 0; j < w_size; j++) {
            if (szachownica[i][j] != 'c') pionki_c++;
            if (szachownica[i][j] != 'b') pionki_b++;
        }
    }
    if (pionki_b == 64 || pionki_c == 64) return true;
    return false;
}
void plansza_SVG_w(char szachownica[8][8]) {
    ofstream plik("plansza_w.svg");
    if (plik.is_open()) {
        plik << "<?xml version=\"1.0\" encoding = \"UTF-8\"?>\n";
        plik << "<svg width =\"640\" height = \"640\" xmlns = \"http://www.w3.org/2000/svg\">\n";
        for (int i = 0; i < w_size; i++) {
            for (int j = 0; j < 4; j++) {
                if (i % 2) {
                    plik << "<rect x=\"" << 0 + (80 * 2 * j) << "\" y=\"" << 0 + (80 * i) << "\" width=\"" << 80 << "\" height=\"" << 80 << "\" fill=\"" << "beige" << "\"/>\n";
                    plik << "<rect x=\"" << 80 + (80 * 2 * j) << "\" y=\"" << 0 + (80 * i) << "\" width=\"" << 80 << "\" height=\"" << 80 << "\" fill=\"" << "gray" << "\"/>\n";
                }
                else {
                    plik << "<rect x=\"" << 0 + (80 * 2 * j) << "\" y=\"" << 0 + (80 * i) << "\" width=\"" << 80 << "\" height=\"" << 80 << "\" fill=\"" << "gray" << "\"/>\n";
                    plik << "<rect x=\"" << 80 + (80 * 2 * j) << "\" y=\"" << 0 + (80 * i) << "\" width=\"" << 80 << "\" height=\"" << 80 << "\" fill=\"" << "beige" << "\"/>\n";
                }
            }
        }
        for (int i = 0; i < w_size; i++) {
            for (int j = 0; j < w_size; j++) {
                if (szachownica[i][j] == 'c') {
                    plik << "<circle cx=\"" << 40 + (80 * j) << "\" cy =\"" << 40 + (80 * i) << "\" r=\"" << 35 << "\" fill=\"" << "black" << "\" stroke=\"blue\" stroke-width=\"5\"/>\n";
                }
                else if (szachownica[i][j] == 'b') {
                    plik << "<circle cx=\"" << 40 + (80 * j) << "\" cy =\"" << 40 + (80 * i) << "\" r=\"" << 35 << "\" fill=\"" << "White" << "\" stroke=\"blue\" stroke-width=\"5\"/>\n";
                }
            }
        }
        plik << "</svg>";
        plik.close();
        cout << "utworzono plansze svg\n";
    }
    else cout << "nie udalo sie utworzyc pliku!\n";
}

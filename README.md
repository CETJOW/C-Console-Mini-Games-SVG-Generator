# C++ Console Board Games & Dynamic SVG Exporter

Projekt konsolowy w języku C++ łączący klasyczne gry turowe z modułem generowania grafiki wektorowej w formacie `.svg`. Stan rozgrywki jest na bieżąco wizualizowany w terminalu (ASCII) oraz automatycznie eksportowany do plików graficznych.

---

## Główne Funkcjonalności

- **Kółko i Krzyżyk (Tic-Tac-Toe):**
  - Tryb dla 2 graczy lub gra przeciwko komputerowi.
  - Prosta sztuczna inteligencja z priorytetyzacją ruchów: wykrywanie szansy na wygraną, blokowanie ruchu przeciwnika oraz ruch losowy.
  - Pomiar czasu na ruch z limitem 30 sekund na gracza (`std::chrono`).
  - Eksport stanu planszy w czasie rzeczywistym do pliku `plansza_ttt.svg`.

- **Warcaby (Checkers):**
  - Rozgrywka na planszy 8×8 dla dwóch graczy.
  - Obsługa ruchu po przekątnych oraz mechanika bicia pionków przeciwnika.
  - Równoległe odświeżanie widoku w konsoli oraz zapis stanu szachownicy do pliku `plansza_w.svg`.

- **Generator Grafiki SVG:**
  - **Podstawowy SVG:** Tworzenie czystego szablonu wektorowego (`basic.svg`).
  - **Zaawansowany SVG:** Rysowanie zdefiniowanych przez użytkownika prymitywów geometrycznych (linie, okręgi, prostokąty) z walidacją współrzędnych i wyborem kolorów (`advanced.svg`).

---

## Użyte Technologie

- **Język:** C++ (standard C++11 lub nowszy)
- **Biblioteka standardowa:**
  - `<fstream>` – zapis i formatowanie struktury XML plików `.svg`
  - `<chrono>` – precyzyjny pomiar czasu tur graczy
  - `<iostream>`, `<cstdlib>`, `<ctime>`, `<string>`

---

## Instrukcja Uruchomienia

### Wymagania
Dowolny kompilator C++ obsługujący standard C++11 (np. `g++`, `clang++`, MSVC).

### Kompilacja

W terminalu wykonaj polecenie:

```bash
g++ -std=c++11 -O2 main.cpp -o board_games_svg

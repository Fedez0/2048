## Descrizione

Implementazione del gioco 2048 in C++ utilizzando la libreria SFML per la grafica.

## Requisiti di Sistema

- Compilatore C++ compatibile con C++11
- [Simple and Fast Multimedia Library (SFML)](https://www.sfml-dev.org/)

## Compilazione

Assicurati di aver installato SFML. Puoi seguire le [istruzioni di installazione ufficiali](https://www.sfml-dev.org/tutorials/2.5/start-linux.php) sul sito SFML.

```bash
# Clona il repository
git clone https://github.com/tuonome/2048-sfml.git

# Entra nella directory del progetto
cd 2048-sfml

# compila gli oggetti
g++ -std=c++11 -o 2048_game main.cpp -lsfml-graphics -lsfml-window -lsfml-system



# Compila il progetto
./2048_game

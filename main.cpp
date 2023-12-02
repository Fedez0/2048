#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib> // Per la dichiarazione di calloc
#include <cstring> // Per la dichiarazione di memset

using namespace std;
using namespace sf;

void initWindow(RenderWindow &window);

#define FRAME_RATE 60
#define AREAGIOCO 5


const char rootFont[] = "./res/ClearSans.ttf"; 
const Color QuadratoVuoto(205,193,180);
//colore del background
const Color BackGroundColor(187,173,160);
const Vector2f dimFinestra(800, 600);

class Game{
    private:
        int **areaGioco;
        RectangleShape quadrato[AREAGIOCO][AREAGIOCO];

    public:
        Game(){
            cout<<"Inizializzazione campo di gioco:\n";
            areaGioco = reinterpret_cast<int**>(calloc(AREAGIOCO, sizeof(int*)));
            for (int i = 0; i < AREAGIOCO; ++i) {
                areaGioco[i] = reinterpret_cast<int*>(calloc(AREAGIOCO, sizeof(int)));
            }

        }  
        bool setValore(int riga,int colonna,int valore){
            if(riga<0||riga>=AREAGIOCO||colonna<0||colonna>=AREAGIOCO){
                return false;
            }else{
                areaGioco[riga][colonna]=valore;
                return true;
            }
        }
        void disegnaQuadrati(RenderWindow &window){//INIZIALIZZAZIONE DEI QUADRATI
            Vector2f dimQuadrato(100.0f,100.0f);
            quadrato[AREAGIOCO][AREAGIOCO];
            Text titoloGioco;
    
            Font font;
            font.loadFromFile(rootFont);
            titoloGioco.setString("2048");
            titoloGioco.setCharacterSize(24);
            titoloGioco.setFont(font);
            titoloGioco.setStyle(Text::Bold);
            titoloGioco.setFillColor(Color(119,110,101));
            titoloGioco.setPosition(800/2-30,30);
            window.draw(titoloGioco);
            
            for(int i=0;i<AREAGIOCO;i++){
                for(int j=0;j<AREAGIOCO;j++){
                    quadrato[i][j].setSize(dimQuadrato);
                    quadrato[i][j].setFillColor(QuadratoVuoto);
                    quadrato[i][j].setOutlineColor(BackGroundColor);
                    quadrato[i][j].setOutlineThickness(6.0f);
                    quadrato[i][j].setPosition(j * dimQuadrato.x+150, i * dimQuadrato.y+70);
                    window.draw(quadrato[i][j]);
                }
            }
        }
        


    
};

int main(){
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "2048");
    Game game;

    
    initWindow(window);

    // run the program as long as the window is open    
    while (window.isOpen())
    {
        window.clear(BackGroundColor);
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized) {
                // Reimposta le dimensioni della finestra alle dimensioni originali
                window.setSize(dimFinestra);
            }
        }

        // clear the window with black color
        

        // draw everything here...
        // window.draw(...);
        game.disegnaQuadrati(window);

        // end the current frame
        window.display();
    }

    return 0;
}
void initWindow(RenderWindow &window){
    window.setFramerateLimit(FRAME_RATE);
}



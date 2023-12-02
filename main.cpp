#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib> // Per la dichiarazione di calloc
#include <cstring> // Per la dichiarazione di memset
#include <fstream>


using namespace std;
using namespace sf;

void initWindow(RenderWindow &window);

#define FRAME_RATE 60
#define AREAGIOCO 5
#define BUFFERSTR 10000

//roots
const char rootFont[] = "./res/ClearSans.ttf"; 
const char rootHighScore[] = "./res/data.txt";

//colore del background
const Vector2u dimFinestra(800, 600);

//const color

const Color QuadratoVuoto(205,193,180);
//colore del background
const Color BackGroundColor(187,173,160);

const Color stage2(238,228,218);
const Color stage4();
const Color stage8();
const Color stage16();
const Color stage32();
const Color stage64();
const Color stage128();
const Color stage256();
const Color stage512();
const Color stage1024();
const Color stage2048();


//const size
const Vector2f dimQuadrato(100.0f,100.0f);

class Game{
    private:
        int **areaGioco;
        int highScore;
        int currentScore;
        RectangleShape quadrato[AREAGIOCO][AREAGIOCO];
        Text txtValori[AREAGIOCO][AREAGIOCO];
        Font font;
        Text txtHighScore;
        Text titoloGioco;

    public:
        Game(RenderWindow &window){
            cout<<"Inizializzazione campo di gioco:\n";

            
            font.loadFromFile(rootFont);

            areaGioco = reinterpret_cast<int**>(calloc(AREAGIOCO, sizeof(int*)));
            
            for (int i = 0; i < AREAGIOCO; ++i) {
                areaGioco[i] = reinterpret_cast<int*>(calloc(AREAGIOCO, sizeof(int)));
            }
            ifstream leggiFile(rootHighScore);
            char highScoreStr[BUFFERSTR];
            leggiFile >> highScoreStr;
            leggiFile.close();
            highScore=atoi(highScoreStr);

            for(int i=0;i<AREAGIOCO;i++){
                for(int j =0 ;j<AREAGIOCO;j++){
                    txtValori[i][j].setString("0");
                    txtValori[i][j].setCharacterSize(20);
                    txtValori[i][j].setFont(font);
                    txtValori[i][j].setStyle(Text::Bold);
                    txtValori[i][j].setFillColor(Color(119,110,101));
                    txtValori[i][j].setPosition(j * dimQuadrato.x+150+dimQuadrato.x/2, i * dimQuadrato.y+70+dimQuadrato.x/2);
                    window.draw(txtValori[i][j]);
                }
            }
            
            

        }  
        void setNewHighScore(int score){
            highScore=score;
            ofstream fileHighScore(rootHighScore);
            char temp[BUFFERSTR];
            sprintf(temp,"%d",score);
            fileHighScore<<temp;
            fileHighScore.close();

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
            
            quadrato[AREAGIOCO][AREAGIOCO];
            
    
            
            titoloGioco.setString("2048");
            titoloGioco.setCharacterSize(24);
            titoloGioco.setFont(font);
            titoloGioco.setStyle(Text::Bold);
            titoloGioco.setFillColor(Color(119,110,101));
            titoloGioco.setPosition(800/2-30,30);
            window.draw(titoloGioco);
            

            
            char highScoreStr[BUFFERSTR];
            sprintf(highScoreStr,"Highscore: %d",highScore);
            txtHighScore.setString(highScoreStr);
            txtHighScore.setCharacterSize(24);
            txtHighScore.setFont(font);
            txtHighScore.setStyle(Text::Bold);
            txtHighScore.setFillColor(Color(119,110,101));
            txtHighScore.setPosition(30,30);
            window.draw(txtHighScore);



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
            start();
        }
        void start(){
            srand(time(NULL));
            int x1,x2,y1,y2;
            x1=rand()%AREAGIOCO;
            x2=rand()%AREAGIOCO;
            y1=rand()%AREAGIOCO;
            y2=rand()%AREAGIOCO;

            quadrato[x1][y1].setFillColor(stage2);
            quadrato[x2][y2].setFillColor(stage2);

            areaGioco[x1][y1]=2;
            areaGioco[x2][y2]=2;
        }
        void update(RenderWindow &window){
            window.draw(txtHighScore);
            window.draw(titoloGioco);


            char temp[BUFFERSTR];

            for(int i=0;i<AREAGIOCO;i++){
                for(int j=0;j<AREAGIOCO;j++){
                    //aggiornamento valori gioco
                    sprintf(temp,"%d",areaGioco[i][j]);
                    txtValori[i][j].setString(temp);


                    window.draw(quadrato[i][j]);
                    if(areaGioco[i][j]!=0){
                        window.draw(txtValori[i][j]);
                    }
                }
            }
        }
        void toLeft(RenderWindow &window){
            
        }
        void toUp(RenderWindow &window){
            
        }
        void toRight(RenderWindow &window){
            
        }
        void toDown(RenderWindow &window){
            
        }
        


    
};

int main(){
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "2048");
    Game game(window);

    
    initWindow(window);
    game.disegnaQuadrati(window);
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
        
        if (sf::Keyboard::isKeyPressed(Keyboard::Left))
        {
            game.toLeft(window);
        }
        if (sf::Keyboard::isKeyPressed(Keyboard::Right))
        {
            game.toRight(window);
        }
        if (sf::Keyboard::isKeyPressed(Keyboard::Up))
        {
            game.toUp(window);
        }
        if (sf::Keyboard::isKeyPressed(Keyboard::Down))
        {
            game.toDown(window);
        }
        


        // draw everything here...
        // window.draw(...);
        game.update(window);

        // end the current frame
        window.display();
    }

    return 0;
}
void initWindow(RenderWindow &window){
    window.setFramerateLimit(FRAME_RATE);
}



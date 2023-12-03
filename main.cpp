#include <SFML/Graphics.hpp>

//compile command
// g++ -std=c++11 -o 2048_game main.cpp -lsfml-graphics -lsfml-window -lsfml-system
#include <iostream>
#include <cstdlib> // Per la dichiarazione di calloc
#include <cstring> // Per la dichiarazione di memset
#include <fstream>
#include <unistd.h>


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
const Color stage4(238,225,201);
const Color stage8(243,178,122);
const Color stage16(246,150,100);
const Color stage32(247,124,95);
const Color stage64(246,94,56);
const Color stage128(237,207,144);
const Color stage256(237,204,97);
const Color stage512(237,200,80);
const Color stage1024(237,197,63);
const Color stage2048(237,194,46);


//const size
const Vector2f dimQuadrato(100.0f,100.0f);

class Game{
    private:
        int **areaGioco;
        int a;
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

            a=0;
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
                    switch (areaGioco[i][j])
                    {
                    case 2:
                        quadrato[i][j].setFillColor(stage2);
                        break;
                    case 4:
                        quadrato[i][j].setFillColor(stage4);
                        break;
                    case 8:
                        quadrato[i][j].setFillColor(stage8);
                        break;
                    case 16:
                        quadrato[i][j].setFillColor(stage16);
                        break;
                    case 32:
                        quadrato[i][j].setFillColor(stage32);
                        break;
                    case 64:
                        quadrato[i][j].setFillColor(stage64);
                        break;
                    case 128:
                        quadrato[i][j].setFillColor(stage128);
                        break;
                    case 256:
                        quadrato[i][j].setFillColor(stage256);
                        break;
                    case 512:
                        quadrato[i][j].setFillColor(stage512);
                        break;
                    case 1024:
                        quadrato[i][j].setFillColor(stage1024);
                        break;
                    case 2048:
                        quadrato[i][j].setFillColor(stage2048);
                        break;
                    default:
                        quadrato[i][j].setFillColor(QuadratoVuoto);
                        break;
                    }
                    

                    window.draw(quadrato[i][j]);
                    if(areaGioco[i][j]!=0){
                        window.draw(txtValori[i][j]);
                    }
                }
            }
        }
        
        bool toLeft(RenderWindow &window){
            bool changed=false;
            for(int i=AREAGIOCO-1;i>=0;i--){
                for(int j=AREAGIOCO-1;j>=0;j--){
                    if(areaGioco[i][j] && j>0){
                        if(areaGioco[i][j-1]==0){
                            areaGioco[i][j-1]=areaGioco[i][j];
                            areaGioco[i][j]=0;
                            changed=true;

                        }else if(areaGioco[i][j-1]==areaGioco[i][j]){
                            areaGioco[i][j-1]*=2;
                            areaGioco[i][j]=0;
                            changed=true;
                        }
                    }
                }
            }
            for(int i=AREAGIOCO-1;i>=0;i--){
                for(int j=AREAGIOCO-1;j>=0;j--){
                    if(areaGioco[i][j] && j>0){
                        if(areaGioco[i][j-1]==0){
                            areaGioco[i][j-1]=areaGioco[i][j];
                            areaGioco[i][j]=0;
                            changed=true;

                        }
                    }
                }
            }
            

            return changed;
           
        }
        bool toUp(RenderWindow &window){
            bool changed=false;
            for(int i=AREAGIOCO-1;i>=0;i--){
                for(int j=AREAGIOCO-1;j>=0;j--){
                    if(areaGioco[j][i] && j>0){
                        
                        if(areaGioco[j-1][i]==areaGioco[j][i]){
                            areaGioco[j-1][i]*=2;
                            areaGioco[j][i]=0;
                            changed=true;
                        }
                        if(areaGioco[j-1][i]==0){
                            areaGioco[j-1][i]=areaGioco[j][i];
                            areaGioco[j][i]=0;
                            changed=true;
                        }
                    }
                }
            }
            for(int i=AREAGIOCO-1;i>=0;i--){
                for(int j=AREAGIOCO-1;j>=0;j--){
                    if(areaGioco[j][i] && j>0){
                        
                        if(areaGioco[j-1][i]==0){
                            areaGioco[j-1][i]=areaGioco[j][i];
                            areaGioco[j][i]=0;
                            changed=true;
                        }
                    }
                }
            }
            return changed;
           
            
        }
        bool toRight(RenderWindow &window){
            bool changed=false;
            for(int i=0;i<AREAGIOCO;i++){
                for(int j=0;j<AREAGIOCO;j++){
                    if(areaGioco[i][j] && (j+1)!=AREAGIOCO){
                        
                        if(areaGioco[i][j+1]==areaGioco[i][j]){
                            areaGioco[i][j+1]*=2;
                            areaGioco[i][j]=0;
                            changed=true;
                        }
                        if(areaGioco[i][j+1]==0){
                            areaGioco[i][j+1]=areaGioco[i][j];
                            areaGioco[i][j]=0;
                            changed=true;

                        }
                    }
                }
            }
            for(int i=0;i<AREAGIOCO;i++){
                for(int j=0;j<AREAGIOCO;j++){
                    if(areaGioco[i][j] && (j+1)!=AREAGIOCO){
                        
                        if(areaGioco[i][j+1]==0){
                            areaGioco[i][j+1]=areaGioco[i][j];
                            areaGioco[i][j]=0;
                            changed=true;

                        }
                    }
                }
            }
            return changed;
            
            
        }
        bool toDown(RenderWindow &window){
            bool changed=false;
            for(int i=0;i<AREAGIOCO;i++){
                for(int j=0;j<AREAGIOCO;j++){
                    if(areaGioco[j][i] && (j+1)!=AREAGIOCO){
                        
                        if(areaGioco[j+1][i]==areaGioco[j][i]){
                            areaGioco[j+1][i]*=2;
                            areaGioco[j][i]=0;
                            changed=true;
                        }
                        if(areaGioco[j+1][i]==0){
                            areaGioco[j+1][i]=areaGioco[j][i];
                            areaGioco[i][j]=0;
                            changed=true;

                        }
                    }
                }
            }
            for(int i=0;i<AREAGIOCO;i++){
                for(int j=0;j<AREAGIOCO;j++){
                    if(areaGioco[j][i] && (j+1)!=AREAGIOCO){
                        
                        if(areaGioco[j+1][i]==0){
                            areaGioco[j+1][i]=areaGioco[j][i];
                            areaGioco[i][j]=0;
                            changed=true;

                        }
                    }
                }
            }
            return changed;
            
            
        }
        void newBlock(RenderWindow &window){
            if(a==0){
                srand(time(NULL));
                int x;
                int y;
                do{
                    x=rand()%AREAGIOCO;
                    y=rand()%AREAGIOCO;
                }while(areaGioco[x][y]!=0);

                int num=rand()%100;
                if(num<75){
                    areaGioco[x][y]=2;
                }else{
                    areaGioco[x][y]=4;
                }
                a++;
            }else{
                a--;
            }
            

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
            }else if(event.type==Event::KeyReleased){
                bool changed=false;
                bool temp=false;
                if(event.key.code==Keyboard::Up){
                    temp=game.toUp(window);
                    if(temp){
                        changed=true;
                    }
                }
                if(event.key.code==Keyboard::Down){
                    temp=game.toDown(window);
                    if(temp){
                        changed=true;
                    }
                }
                if(event.key.code==Keyboard::Right){
                    temp=game.toRight(window);
                    if(temp){
                        changed=true;
                    }
                }
                if(event.key.code==Keyboard::Left){
                    temp=game.toLeft(window);
                    if(temp){
                        changed=true;
                    }
                }
                    
                if(changed){
                    game.newBlock(window);
                }
            }
        }

        // clear the window with black color
        
        
        
        


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



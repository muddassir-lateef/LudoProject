#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include "../classes/dice.h"
#include "../classes/logging.h"
#include"../classes/Board.h"
#include"../classes/Token.h"

using namespace sf;
using namespace std;
int x=1;
int turn=1;


int main()
{
    RenderWindow app(VideoMode(1280,720), "Ludo");
    app.setFramerateLimit(60);
    sf::Music music;
    if (!music.openFromFile("audio/mainmenu/strongandstrike.wav"))
      return -1; // error
    Texture dice_texture;
    dice_texture.loadFromFile("images/dice/dices6.png");
    dice Dice(750,600,dice_texture);
    music.play();
    music.setVolume(10);
    
    // Loading textures
    Texture t[5];
    t[0].loadFromFile("images/background/board.png");
    t[1].loadFromFile("images/tokens/token1.png");
    t[2].loadFromFile("images/tokens/token2.png");
    t[3].loadFromFile("images/tokens/token3.png");
    t[4].loadFromFile("images/tokens/token4.png");
    //Making sprites from textures
    Sprite boardS(t[0]);
    Sprite tokensS[4]={Sprite(t[1]),Sprite(t[2]),Sprite(t[3]),Sprite(t[4])};
    //initializing classes with sprites
    Board board(0,0,&boardS,&app);
    board.initTokens(tokensS);
    int nx=0;
    while (app.isOpen())
    {
      app.clear();
      Event e;
      while (app.pollEvent(e))
      {

          if (e.type == Event::Closed)
            app.close();
                   
          if (e.type == Event::MouseButtonPressed)
            if (e.key.code == Mouse::Left)
            {
                std::cout<<"x:"<<Mouse::getPosition().x<<" "<<"y:"<<Mouse::getPosition().y<<std::endl;
            }
          if (e.type == Event::KeyPressed)
          { if (e.key.code == Keyboard::Escape){
             app.close();
            }
            if (e.key.code == Keyboard::Space){
              if(Dice.endturn(1))
              { 
                  //if wasted
                  if (Dice.turn_wasted(1)){  //checking for player 1
                    cout<<"Player turn was wasted\n";
                  }
              }
              else
              {
                  vector<int> roll = Dice.complete_roll(1,app); 
                  for (int i=0; i<roll.size(); i++){cout<<roll[i]<<" ";}
                  cout<<endl;

              }
            }  
          }

        
      }
      if (Dice.isRolling()) {x = (rand()%6)+1;} //give a new x to display
      Dice.animate_roll(x,app);
      Dice.drawDice(x,app);
      board.draw();
      app.display();
    }
  
    return 0;
}
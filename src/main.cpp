#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include<iostream>
#include"../classes/Board.h"
#include"../classes/Token.h"

using namespace sf;


int main()
{
    RenderWindow app(VideoMode(1280,720), "Ludo");
    app.setFramerateLimit(60);
    
    
    sf::Music music;
    if (!music.openFromFile("audio/mainmenu/strongandstrike.wav"))
      return -1; // error
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
   // int nx=0;
    while (app.isOpen())
    {
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
          {
            if(e.key.code == Keyboard::Escape)
              app.close();
            if(e.key.code == Keyboard::F)
            {
              //nx++;
             // board.move(1,8,13,nx);
            //  board.move(2,1,8,nx);
              //board.move(3,6,1,nx);
             // board.move(4,13,6,nx);

            }

              
          }  
      }
      board.draw();
      app.display();
    }
    return 0;
}

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include<iostream>
#include <ctime>
#include<unistd.h>
#include "dice.h"
using namespace sf;
using namespace std;
int x=1;

int main()
{
    RenderWindow app(VideoMode(1280,720), "Ludo");
    app.setFramerateLimit(60);
    sf::Music music;
    if (!music.openFromFile("audio/mainmenu/strongandstrike.wav"))
      return -1; // error
    music.play();
    music.setVolume(20);
    Texture bg;
    bg.loadFromFile("images/background/board.png");
    Sprite background(bg);
    Texture dice_texture;
    dice_texture.loadFromFile("images/dice/dices6.png");
    dice Dice(750,600,dice_texture);
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
          
            }
          if (e.type == Event::KeyPressed){
            if(e.key.code == Keyboard::Escape)
              app.close();
            if (e.key.code == Keyboard::Space)
              Dice.roll_Dice(123,app);
          }
      }
      if (Dice.isRolling()) x = (rand()%6)+1; //give a new x to display
      Dice.animate_roll(x,app);
      Dice.drawDice(x,app);
      app.draw(background);
      app.display();
    }
    return 0;
}





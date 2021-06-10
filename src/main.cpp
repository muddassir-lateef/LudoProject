#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include<iostream>
using namespace sf;

Vector2i offset(48,24);

void rocket()
{

  char x='r';

}
void racoon()
{
  char c='c';
}
int main()
{
    std::cout<<"Muddassir2 merger setting"<<std::endl;
    std::cout<<"Muddassir2 main setting"<<std::endl;
    std::cout<<"Muddassir1 from meld"<<std::endl;
    std::cout<<"Hello world by Shayan\n";
    RenderWindow app(VideoMode(1280,720), "Ludo");
    app.setFramerateLimit(60);
    sf::Music music;
    if (!music.openFromFile("audio/mainmenu/strongandstrike.wav"))
      return -1; // error
    music.play();
    music.setVolume(50);
    Texture bg;
    bg.loadFromFile("images/background/board.png");
    Sprite background(bg);
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

            }
          if (e.type == Event::KeyPressed){
            if(e.key.code == Keyboard::Escape)
              app.close();
          }  
      }

      app.draw(background);
      app.display();
    }
    return 0;
}

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
using namespace sf;

Vector2i offset(48,24);


int main()
{

    RenderWindow app(VideoMode(1280,720), "Ludo",sf::Style::Fullscreen);
    app.setFramerateLimit(60);//asdf
    sf::Music music;
    if (!music.openFromFile("audio/mainmenu/strongandstrike.wav"))
      return -1; // error
    music.play();
    music.setVolume(50);
    Texture t1;
    t1.loadFromFile("images/mainmenu/menuboard.jpg");
    Sprite background(t1);
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
      }

      app.draw(background);
      app.display();
    }
    return 0;
}
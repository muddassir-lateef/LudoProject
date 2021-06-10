#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include<iostream>
#include <vector>
#include <ctime>
using namespace sf;
using namespace std;

Vector2i offset(48,24);
vector<int> roll_Dice(int type, Sprite& dice, RenderWindow& app);  //roll dice functionality
void animate_roll(int result, Sprite& dice, RenderWindow& app); //animate single role with showing result at the end 
void drawDice(int x, int y, Sprite& dice, int face, RenderWindow& app);  //draw dice at given coordinates
int dice_x = 750;
int dice_y = 650;

int main()
{
    std::cout<<"Changes in Dice roll\n";
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
    Texture dice_texture;
    dice_texture.loadFromFile("images/dice/dices3.png");
    Sprite dice(dice_texture);
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
      //drawDice(dice_x,dice_y,6,app);
      animate_roll(6, dice, app);

      app.draw(background);
      app.display();
    }
    return 0;
}

void drawDice(int x, int y, Sprite& dice, int face, RenderWindow& app){  //only for drawing dice of any face Value at given coordinates
  if (face < 0 || face > 6) return;
  dice.setPosition(x,y);
  if (face<4)
    dice.setTextureRect(IntRect((face-1)*50,0,50,50));  //each dice is 50x50
  else
    dice.setTextureRect(IntRect((face-4)*50,50,50,50));
  app.draw(dice);
}

void animate_roll(int result, Sprite& dice, RenderWindow& app){
  for (int i=1; i<7; i++){
    drawDice(dice_x, dice_y, dice, i, app);
  }
  drawDice(dice_x, dice_y, dice, result, app);
}

vector<int> roll_Dice(int type, Sprite& dice, RenderWindow& app){
  srand(time(0)); //seeding
  vector<int> roll_values;  //return list 
  int value = (rand()%6)+1;
  roll_values.push_back(value); //adding to the list of generated values
  animate_roll(value, dice, app);  //animating roll with the value
  return roll_values;
}
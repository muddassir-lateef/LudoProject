#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <vector>
#include <iostream>
using namespace sf;
using namespace std;

class dice{
    int x;
    int y;
    Sprite Dice;
    sf::SoundBuffer sound;
    int opacity;
    bool rolling;
    int face=6;
public:
    dice(int x, int y);
    dice(int x, int y, Texture& texture);
    void drawDice(int face, RenderWindow& app); //only for drawing dice of any face Value at given coordinates    
    vector<int> roll_Dice(int type, RenderWindow& app);
    void animate_roll(int result, RenderWindow& app);
    void setTexture(Texture& texture);
    Sprite& getDice();
    void setx(int x);
    void sety(int y);
    bool isRolling();
};

dice::dice(int x, int y){
    this->x = x;
    this->y = y;
    opacity = 255;
    Dice.setPosition(this->x,this->y);
    rolling = false;
    sound.loadFromFile("audio/Dice_Roll/dice_roll.wav");;
}

dice::dice(int x, int y, Texture& texture){
    this->x = x;
    this->y = y;
    opacity = 255;
    rolling = false;
    Dice.setPosition(this->x,this->y);
    Dice.setTexture(texture);
    sound.loadFromFile("audio/Dice_Roll/dice_roll.wav");
}

bool dice::isRolling(){
    return rolling;
}

Sprite& dice::getDice(){
    return Dice;
}

void dice::setx(int x){
    this->x = x;
}
void dice::sety(int y){
    this->y = y;
}

void dice::setTexture(Texture& texture){
    this->Dice.setTexture(texture);
}

void dice::drawDice(int faceValue, RenderWindow& app){  //only for drawing dice of any face Value at given coordinates
  Dice.setPosition(x,y);
  if (!rolling) faceValue = face;
  if (faceValue < 0 || faceValue > 6) return;
  IntRect obj((faceValue-1)*50,0,50,50);
  Dice.setTextureRect(obj);
  app.draw(Dice);
}

vector<int> dice::roll_Dice(int type, RenderWindow& app){
  rolling = true;
  Sound rolling_sound;
  rolling_sound.setBuffer(sound);
  rolling_sound.setVolume(100);
  rolling_sound.play();
  srand(time(0)); //seeding
  vector<int> roll_values;  //return list 
  int value = (rand()%6)+1;
  cout<<value<<endl;
  face = value;
  roll_values.push_back(value); //adding to the list of generated values
  //animate_roll(value, app);  //animating roll with the value
  return roll_values;
}

void dice::animate_roll(int result, RenderWindow& app){
  if (rolling == true){ 
    Clock clock;
    clock.restart();
    opacity -= 10;
    Dice.setColor(Color(255,255,255,opacity));
   // Dice.setScale(1.01f,1.01f);
    if (opacity < 0){
        rolling = false;
        opacity = 255;
       // Dice.setScale(1.00f,1.00f);
        this->drawDice(face,app);
    }
  }
}
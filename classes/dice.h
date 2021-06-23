#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <vector>
#include <iostream>
#include"../classes/right_tokens.h"
using namespace sf;
using namespace std;

class dice{
    int x;
    int y;
    int player_turn;
    Sprite Dice;
    int allplayed[4]={0,0,0,0};
    int wasted[4]={0,0,0,0};
    int opacity;
    bool rolling;
    int face=6;
    int random = 6;  //random variable 
    right_tokens right_tok;
public:
        vector<int> player[4];
    dice(int x, int y);
    dice(int x, int y, Texture& texture);
    void drawDice(int face, RenderWindow& app); //only for drawing dice of any face Value at given coordinates    
    int roll_Dice(int type, RenderWindow& app);
    void animate_roll(int result, RenderWindow& app);
    vector<int> complete_roll(int player, RenderWindow& app);
    void setTexture(Texture& texture);
    Sprite& getDice();
    bool endturn(int player);
    void set_player_turn(int);
    void setx(int x);
    void sety(int y);
    bool isRolling();
    void clear_players();
    bool turn_wasted(int player);
};

dice::dice(int x, int y){
    this->x = x;
    this->y = y;
    opacity = 255;
    Dice.setPosition(this->x,this->y);
    rolling = false;
    int player_turn = 1;
    //sound.loadFromFile("audio/Dice_Roll/sample.wav");
    right_tok.set_all(700,230,750,625);
}

dice::dice(int x, int y, Texture& texture){
    this->x = x;
    this->y = y;
    opacity = 255;
    rolling = false;
    Dice.setPosition(this->x,this->y);
    Dice.setTexture(texture);  
    int player_turn = 1; 
    right_tok.set_all(700,230,750,625);
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

void dice::set_player_turn(int val){
    player_turn = val;
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
  right_tok.drawTokens(app);
  right_tok.drawSmallDice(app);
  app.draw(Dice);
}

int dice::roll_Dice(int type, RenderWindow& app){
  rolling = true;
  srand(time(0)); //seeding
  //vector<int> roll_values;  //return list 
  int value = (rand()%6)+1; //value=6;
sf::SoundBuffer* buffer=new SoundBuffer;
// load something into the sound buffer...
if (!buffer->loadFromFile("audio/Dice_Roll/dice roll.wav"))
{
    cout<<"was not loaded!"<<endl;
}
sf::Sound* sound=new Sound;;
sound->setBuffer(*buffer);
sound->setVolume(100);
sound->play();
  //cout<<value<<endl;
  face = value;
  //roll_values.push_back(value); //adding to the list of generated values
  //animate_roll(value, app);  //animating roll with the value
  return value;
}

void dice::animate_roll(int result, RenderWindow& app){
  if (rolling == true){ 
    opacity -= 5;
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

bool dice::endturn(int player)
{
    return allplayed[player-1]==1;
}

bool dice::turn_wasted(int player){
    return (wasted[player-1] == 1);
}

void dice::clear_players(){
    for(int i=0;i<4;i++){
     allplayed[i]=0;
     wasted[i]=0;
     player[i].clear();

    }
        right_tok.clearDie();

}
vector<int> dice::complete_roll(int p, RenderWindow& app){
    int value = roll_Dice(p,app);
    vector<int> temp;
    right_tok.setDicePosition(p);
    if (value == 6){
        if(player[p-1].size() == 0 ){
            player[p-1].push_back(value);
            right_tok.drawSmallDice(value, app);
        }
        else{
            if (player[p-1].size() == 2){
                player[p-1].clear();
                wasted[p-1] = 1;
                right_tok.drawSmallDice(value, app);
            }
            else{
                player[p-1].push_back(value);
                right_tok.drawSmallDice(value, app);
            }
        }
    }
    else
    {
        player[p-1].push_back(value);
        right_tok.drawSmallDice(value, app);

    }
    if (! (value == 6 && wasted[p-1]==0) ){    // ! (value is 6 and player is not wasted)
        allplayed[p-1] = 1;
    }
    //right_tok.clearDie();
    return player[p-1];
}
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <vector>
#include <iostream>
using namespace sf;
using namespace std;

class right_tokens{
    int x;
    int y;
    int x_die;
    int y_die;
    Sprite token_sprite;
    vector<Sprite> dice;    //store multiple die
    Texture tokens;
    Texture dice_texture;
    int tok_y[4];
    IntRect tok_rects[4];
    public:
    right_tokens();
    right_tokens(int x, int y);
    right_tokens(int x, int y, int x2, int y2);
    void drawTokens(RenderWindow& app);
    void drawSmallDice(int result, RenderWindow& app);
    void drawSmallDice(RenderWindow& app);
    void set_all(int x, int y, int x2, int y2);
    void clearDie();
    void setDicePosition(int player);
};

right_tokens::right_tokens(){
    tokens.loadFromFile("images/tokens/token_sheet.png");
    dice_texture.loadFromFile("images/dice/dices6.png");
    token_sprite.setTexture(tokens);
    tok_rects[0] = IntRect(0,0,60,50);
    tok_rects[1] = IntRect(0,50,60,50);
    tok_rects[2] = IntRect(60,0,60,50);
    tok_rects[3] = IntRect(60,50,60,50);
}

right_tokens::right_tokens(int x, int y){
    tokens.loadFromFile("images/tokens/token_sheet.png");
    dice_texture.loadFromFile("images/dice/dices6.png");
    token_sprite.setTexture(tokens);
    this->x = x;
    this->y = y;
    tok_y[0]=y+0;
    tok_y[1]=y+70;
    tok_y[2]=y+140;
    tok_y[3]=y+210;
    tok_rects[0] = IntRect(0,0,60,50);
    tok_rects[1] = IntRect(0,50,60,50);
    tok_rects[2] = IntRect(60,0,60,50);
    tok_rects[3] = IntRect(60,50,60,50);
}

right_tokens::right_tokens(int x, int y, int x2, int y2){
    tokens.loadFromFile("images/tokens/token_sheet.png");
    dice_texture.loadFromFile("images/dice/dices6.png");
    token_sprite.setTexture(tokens);
    this->x = x;
    this->y = y;
    this->x_die = x2;
    this->y_die = y2;
    tok_y[0]=y+0;
    tok_y[1]=y+70;
    tok_y[2]=y+140;
    tok_y[3]=y+210;
    tok_rects[0] = IntRect(0,0,60,50);
    tok_rects[1] = IntRect(0,50,60,50);
    tok_rects[2] = IntRect(60,0,60,50);
    tok_rects[3] = IntRect(60,50,60,50);
}

void right_tokens::drawTokens(RenderWindow& app){
    for (int i=0; i<4; i++){
        token_sprite.setPosition(x,tok_y[i]);
        token_sprite.setTextureRect(tok_rects[i]);   //eash token is 60x50
        app.draw(token_sprite);
    }
}

void right_tokens::drawSmallDice(int result, RenderWindow& app){  //only for drawing dice of any face Value at given coordinates
  Sprite newDie(dice_texture);
  IntRect obj((result-1)*50,0,50,50);
  newDie.setTextureRect(obj);
  newDie.setPosition(x_die + (dice.size()*30),y_die);
  newDie.setScale(0.5f,0.5f);
  dice.push_back(newDie);

  for (int i=0; i<dice.size() ; i++){
    app.draw(dice[i]);
  }
}

void right_tokens::drawSmallDice(RenderWindow& app){  //only for drawing dice of any face Value at given coordinates
  for (int i=0; i<dice.size() ; i++){
    app.draw(dice[i]);
  }
}

void right_tokens:: clearDie(){
    dice.clear();
}

void right_tokens::set_all(int x, int y, int x2, int y2){
    this->x = x;
    this->y = y;
    this->x_die = x2;
    this->y_die = y2;
    tok_y[0]=y+0;
    tok_y[1]=y+70;
    tok_y[2]=y+140;
    tok_y[3]=y+210;
}

void right_tokens::setDicePosition(int player){
    if (player == 1){
        y_die = 245;
    }
    else if (player == 2){
        y_die = 315;
    }
    else if (player == 3){
        y_die = 385;
    }
    else if (player == 4){
        y_die = 455;
    }
    

}
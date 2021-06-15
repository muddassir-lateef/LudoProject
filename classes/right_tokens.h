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
    Sprite token_sprite;
    Texture tokens;
    int tok_y[4];
    IntRect tok_rects[4];
    public:
    right_tokens(int x, int y);

    void draw(RenderWindow& app);
};

right_tokens::right_tokens(int x, int y){
    tokens.loadFromFile("images/tokens/token_sheet.png");
    token_sprite.setTexture(tokens);
    this->x = x;
    this->y = y;
    tok_y[0]=y;
    tok_y[1]=y+70;
    tok_y[2]=y+140;
    tok_y[3]=y+210;
    tok_rects[0] = IntRect(0,0,60,50);
    tok_rects[1] = IntRect(0,50,60,50);
    tok_rects[2] = IntRect(60,0,60,50);
    tok_rects[3] = IntRect(60,50,60,50);
}

void right_tokens::draw(RenderWindow& app){
    for (int i=0; i<4; i++){
        token_sprite.setPosition(x,tok_y[i]);
        token_sprite.setTextureRect(tok_rects[i]);   //eash token is 60x50
        app.draw(token_sprite);
    }
}
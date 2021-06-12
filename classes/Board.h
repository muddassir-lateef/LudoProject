#ifndef BOARD_H
#define BOARD_H
#include <SFML/Graphics.hpp>
#include "./Token.h"
class Board
{
    int x;
    int y;
    sf::Sprite* board;
    sf::RenderWindow* app;
    Token tokens[4];
    
public:
    Board()
    {
        x=0;
        y=0;
        board=NULL;
        app=NULL;
    }
    Board(int x,int y,sf::Sprite* board,sf::RenderWindow* rw)    
    {
        this->board=board;
        this->set(x,y);
        app=rw;
     
    }
    void initTokens(sf::Sprite* t)
    {
        tokens[0].initToken(&t[0],app);
        tokens[1].initToken(&t[1],app);
        tokens[2].initToken(&t[2],app);
        tokens[3].initToken(&t[3],app);

    }
    void draw()
    {
        app->draw(*board);
        for(int i=0;i<4;i++)
        {
      //      tokens[i].draw(10,10);
        }
    }
    void set(int xi,int yi)
    {
        this->x=xi;
        this->y=yi;
        board->setPosition(xi, yi);
    }
    void movet(int x,int y)
    {
        this->draw();
        tokens[3].move(x,y);
        tokens[3].draw();
        tokens[0].draw(590,370);
        tokens[1].draw(365,55);
        tokens[2].draw(49,280);
        tokens[3].draw(275,596);

    }



};


#endif
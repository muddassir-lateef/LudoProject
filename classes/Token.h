#ifndef TOKEN_H
#define TOKEN_H
#include <SFML/Graphics.hpp>
#include<iostream>
class Token
{
    sf::Sprite* token;
    sf::RenderWindow* app;
public:
    Token()
    {
        token=NULL;
    }
    void initToken(sf::Sprite* token,sf::RenderWindow* rw)    
    {
        this->token=token;
        this->app=rw;
    }
    void draw(int xi,int yi)
    {
        token->setPosition(xi, yi);
        app->draw(*token);
    }
    void draw()
    {
        app->draw(*token);
    }

    void move(int xf,int yf)
    {
        token->move(xf,yf);
        int x=token->getPosition().x;
        int y=token->getPosition().y;
       std::cout<<"Moved to x:"<<x<<" y:"<<y<<std::endl;
    }



};


#endif
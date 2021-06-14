#ifndef BOARD_H
#define BOARD_H
#include <SFML/Graphics.hpp>
#include "./Token.h"
#include "../Utilities/strutils.cpp"

class Board
{
    int x;
    int y;
    sf::Sprite* board;
    sf::RenderWindow* app;
    int hits[4]={0,1,1,1};
    Token tokensprites[4];
    string grid[15][15]={
          "#","#","#","#","#","#","_","_","_","#","#","#","#","#","#",
         "#","#","#3","#","#","#","_","-","*1234","#","#","#2","#","#","#",
        "#","#3","#","#3","#","#","_","-","_","#","#2","#","#2","#","#",
         "#","#","#3","#","#","#","_","-","_","#","#","#2","#","#","#",
          "#","#","#","#","#","#","_","-","_","#","#","#","#","#","#",
          "#","#","#","#","#","#","_","-","_","#","#","#","#","#","#",
          "_","*3","_","_","_","_","&","&","&","_","_","_","_","_","_",
          "_","-","-","-","-","-","&","&","&","-","-","-","-","-","_",
          "_","_","_","_","_","_","&","&","&","_","_","_","_","*11","_",
          "#","#","#","#","#","#","_","-","_","#","#","#","#","#","#",
          "#","#","#","#","#","#","_","-","_","#","#","#","#","#","#",
         "#","#","#4","#","#","#","_","-","_","#","#","#1","#","#","#",
        "#","#4","#","#4","#","#","_","-","_","#","#1","#","#","#","#",
         "#","#","#4","#","#","#","*4","-","_","#","#","#1","#","#","#",
          "#","#","#","#","#","#","_","_","_","#","#","#","#","#","#"

    };
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
        tokensprites[0].initToken(&t[0],app);
        tokensprites[1].initToken(&t[1],app);
        tokensprites[2].initToken(&t[2],app);
        tokensprites[3].initToken(&t[3],app);

    }
    void draw()
    {
        int padding[2]={9,5};
        app->draw(*board);
        for(int i=0;i<15;i++)
        {
            for(int j=0;j<15;j++)
            {
                if(grid[i][j].length()>1)
                {
                    int s=grid[i][j].length();
                    int off=0;
                    for(int k=1;k<s;k++)
                    {
                        int player=grid[i][j][k]-49;
                        if(grid[i][j][0]=='#')
                        {
                            if(player==0 || player==3 )
                            {
                                tokensprites[player].draw(x-27+9+((j+1)*45),y-61+5+((i+1)*45)-off);
                            }
                            else if(player==1 || player ==2)

                            {
                                tokensprites[player].draw(x-27+9+((j+1)*45),y-18+5+((i+1)*45)-off);
                            }
                        }
                        else
                        {
                            tokensprites[player].draw(x+padding[1]+((j)*45),y+padding[0]+((i)*45)-off);
                        }
                        off+=5;
                    }

                }
            }
        }

    }
    void set(int xi,int yi)
    {
        this->x=xi;
        this->y=yi;
        board->setPosition(xi, yi);
    }
    void move(int p,int i,int j,int steps)
    {
        for(int k=0;k<steps;k++)
        {
            this->draw();
            if(!((i==6 && j==7)||(i==7 && j==6)||(i==7 && j==8)||(i==8 && j==7)))
            {
                string temp=grid[i][j];
                grid[i][j]=strremove(p+48,temp);
                int h=0;
                int v=0;
                //i is the y axis from top to bottom
                //j is the x axis from left to right
                if(j==6)
                {
                    if(i==0)
                    {
                        h=1;
                    }
                    else if (i==9)
                    {
                        v=1;
                        h=-1;
                    }
                    else
                    {
                        v=1;
                    }
                }
                else if(j==7)
                {
                    if(i>-1 && i<6 && p==2 && hits[p-1]>0)
                    {
                        v=-1;
                    }
                    else if(i>8 && i<15 && p==4 && hits[p-1]>0)
                    {
                        v=1;
                    }
                    else
                    {
                        if(i==0)
                        {
                            h=1;
                        }
                        else if(i==14)
                        {
                            h=-1;
                        }

                    }
                }
                else if(j==8)
                {
                    if(i==14)
                    {
                        h=-1;
                    }
                    else if (i==5)
                    {
                        h=1;
                        v=-1;
                    }
                    else
                    {
                        v=-1;
                    }
                }
                if(i==6)
                {
                    if(j==14)
                    {
                        v=-1;
                    }
                    else if (j==5)
                    {
                        v=1;
                        h=1;
                    }
                    else
                    {
                        h=1;
                    }
                }
                else if(i==7)
                {
                    if(j>-1 && j<6 && p==3 && hits[p-1]>0)
                    {
                        h=1;
                    }
                    else if(j>8 && j<15 && p==1 && hits[p-1]>0)
                    {
                        h=-1;
                    }
                    else
                    {
                        if(j==0)
                        {
                            v=1;
                        }
                        else if(j==14)
                        {
                            v=-1;
                        }

                    }
                }
                else if(i==8)
                {
                    if(j==0)
                    {
                        v=1;
                    }
                    else if (j==9)
                    {
                        h=-1;
                        v=-1;
                    }
                    else
                    {
                        h=-1;
                    }
                }
                grid[i-v][j+h]+=char(p+48);
                i=i-v;
                j=j+h;

            }
        }

    }



};


#endif
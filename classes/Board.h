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
         "#","#","#3","#","#","#","_","-","*2","#","#","#2","#","#","#",
        "#","#3","#","#3","#","#","_","-","_","#","#2","#","#2","#","#",
         "#","#","#3","#","#","#","_","-","_1","#","#","#2","#","#","#",
          "#","#","#","#","#","#","_","-","_1","#","#","#","#","#","#",
          "#","#","#","#","#","#","_","-","_1","#","#","#","#","#","#",
          "_","*3","_","_","_","_","&","&","&","_1","_","_","_","_","_",
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
    int hit()
    {
        for(int i=0;i<15;i++)
        {
            for(int j=0;j<15;j++)
            {
                int gl=grid[i][j].length();
                if(gl>2)
                {
                    int prev=0;
                    for(int k=0;k<gl;k++)
                    {
                        int gc=grid[i][j][k];
                        if(gc=='1' || gc=='2' || gc=='3' || gc=='4')
                        {
                            if(prev==0)
                            {
                                prev=gc-48;
                            }
                            else if(prev!=gc-48)
                            {
                                string temp=grid[i][j];
                                grid[i][j]=strremove(prev+48,temp);
                                this->hits[gc-48]++;
                                cout<<prev<<"was hit!"<<endl;
                                //prev(int) got hit!
                            }
                        }
                    }   
                }                
            }

        }
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
    int* selectgrid(int x,int y)
    {
        int xs=0;
        int xe=0;
        int ys=0;
        int ye=0;

        for(int i=0;i<15;i++)
        {
            for(int j=0;j<15;j++)
            {
                int xoff=96;
                int yoff=75;
                int off=45;
                xs=xoff+this->x+j*off;
                xe=xoff+this->x+(j+1)*off;
                ys=yoff+this->y+i*off;
                ye=yoff+this->y+(i+1)*off;
           //     cout<<"x:"<<x<<" y:"<<y<<endl;
             //   cout<<"xs:"<<xs<<" xe:"<<xe<<endl;
               // cout<<"ys:"<<ys<<" ye:"<<ye<<endl;
                 //   cout<<"i:"<<i<<"  j:"<<j<<endl;

                if(x<=xe &&x>=xs && y<=ye &&y>=ys)
                {
                 //   cout<<"ffi:"<<i<<"  ffj:"<<j<<endl;

                    int * corr=new int[2];
                    corr[0]=i;
                    corr[1]=j;
                    if(corr[0]>14 || corr[1]>14)
                    {
                        return NULL;
                    }
                    return corr;

                }

            }
        }
        return NULL;

    }
    bool move(int p,int i,int j,int steps)
    {
        if(grid[i][j].find(char(p+48),0)!= String::InvalidPos &&(grid[i][j][0]=='_' || grid[i][j][0]=='*' ||grid[i][j][0]=='-'))
        {
            for(int k=0;k<steps;k++)
            {
                //this->draw();
               // cout<<"fidning "<<p<<" from "<<grid[i][j]<<endl;
                if(!((i==6 && j==7)||(i==7 && j==6)||(i==7 && j==8)||(i==8 && j==7)))
                {
                 //   cout<<"inside"<<endl;
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
          //  cout<<"moved"<<endl;
            return true;
        }
        else
        {
            return false;
        }

    }



};


#endif
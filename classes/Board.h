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
    sf::Sprite* border;
    sf::RenderWindow* app;
    int hits[4]={0,0,0,0};
    Token tokensprites[4];
    string grid[15][15]={
          "#","#","#","#","#","#","_","_","_","#","#","#","#","#","#",
         "#","#","#3","#","#","#","_","-","*","#","#","#2","#","#","#",
        "#","#3","#","#3","#","#","_","-","_","#","#2","#","#2","#","#",
         "#","#","#3","#","#","#","_","-","_","#","#","#2","#","#","#",
          "#","#","#","#","#","#","_","-","_","#","#","#","#","#","#",
          "#","#","#","#","#","#","_","-","_","#","#","#","#","#","#",
         "_","*","_","_","_","_","&","&","&","_","_","_","_","_","_",
          "_","-","-","-","-","-","&","&","&","-","-","-","-","-","_",
          "_","_","_","_","_","_","&","&","&","_","_","_","_","*","_",
          "#","#","#","#","#","#","_","-","_","#","#","#","#","#","#",
          "#","#","#","#","#","#","_","-","_","#","#","#","#","#","#",
         "#","#","#4","#","#","#","_","-","_","#","#","#1","#","#","#",
        "#","#4","#","#4","#","#","_","-","_","#","#1","#","#1","#","#",
         "#","#","#4","#","#","#","*","-","_","#","#","#1","#","#","#",
          "#","#","#","#","#","#","_","_","_","#","#","#","#","#","#"

    };
public:
    bool egrid[15][15];

    Board()
    {
        x=0;
        y=0;
        board=NULL;
        app=NULL;
    }
    void clearw()
    {
        for(int i=0;i<15;i++)
        {
            for(int j=0;j<15;j++)
            {
                egrid[i][j]=false;
            }

        }

    }
    Board(int x,int y,sf::Sprite* board,sf::Sprite* bord,sf::RenderWindow* rw)    
    {
        clearw();
        this->board=board;
        this->set(x,y);
        app=rw;
        border=bord;
     
    }
    void trace(int p,int i,int j,int steps)
    {

        int* arr=predict(p,i,j,steps);
        if(arr!=NULL)
        {

            egrid[arr[1]][arr[2]]=true;
        }
        
    }
    bool addtoken(int player,int check=0)
    {
    //    cout<<"checking tokens of"<<player<<endl;
        int closedtokens[4][4][2]={11,11,12,10,13,11,12,12,1,11,2,10,3,11,2,12,1,2,2,1,3,2,2,3,12,1,13,2,11,2,12,3};
        for(int k=0;k<4;k++)
        {
            int i=closedtokens[player-1][k][0];
            int j=closedtokens[player-1][k][1];
//            cout<<"checking i:"<<i<<"j:"<<j<<endl;
            if(grid[i][j].length()==1)
            {
                if(check==0)
                grid[i][j]+=char(player+48);
  //                      cout<<"truee!!"<<endl;

                return true;

            }
        }
     //   cout<<"false!!"<<endl;
        return false;
    }
    int won()
    {
        int win[4][2]={7,8,6,7,7,6,8,7};
        for(int i=0;i<4;i++)
        {
            if(grid[win[i][0]][win[i][1]].length()>4)
            {
                return grid[win[i][0]][win[i][1]][1]-48;
            }
        }
        return 0;
    }    
    bool opentoken(int player)
    {
        int starting[4][2]={8,13,1,8,6,1,13,6};
        int closedtokens[4][4][2]={11,11,12,10,13,11,12,12,1,11,2,10,3,11,2,12,1,2,2,1,3,2,2,3,12,1,13,2,11,2,12,3};
        for(int k=0;k<4;k++)
        {   
            int i=closedtokens[player-1][k][0];
            int j=closedtokens[player-1][k][1];
        //    cout<<"for k:"<<k<<" i:"<<i<<" j:"<<j<<endl;
            if (grid[i][j].length()>1)
            {
                
                //cout<<"in to remove from i:"<<i<<" j:"<<j<<endl;
                string temp=grid[i][j];
                grid[i][j]=strremove(player+48,temp);
                i=starting[player-1][0];
                j=starting[player-1][1];
               // cout<<"placed to i:"<<i<<" j:"<<j<<endl;

                grid[i][j]+=char(player+48);
                return true;
            }
        }
        return false;

    }
    void initTokens(sf::Sprite* t)
    {
        tokensprites[0].initToken(&t[0],app);
        tokensprites[1].initToken(&t[1],app);
        tokensprites[2].initToken(&t[2],app);
        tokensprites[3].initToken(&t[3],app);
    }
    int* predict(int p,int i,int j,int steps)
    {
        string tgrid[15][15];
        for(int x1=0;x1<15;x1++)
        {
            for(int x2=0;x2<15;x2++)
            {
                tgrid[x1][x2]=grid[x1][x2];
                
            }
        }
        int* arr=new int[3];
        arr[0]=-1;
        arr[1]=-1;
        arr[2]=-1;

        int* mv=move(p,i,j,steps);
        if(mv!=NULL)
        {
          //  cout<<"mov sent "<<mv[0]<<" "<<mv[1]<<" "<<mv[2]<<" "<<endl;
            if(mv[0]==0)
            {
                arr[0]=hit(1);
                hits[p-1]--;
                arr[1]=mv[1];
                arr[2]=mv[2];
            }
            else
            {
                arr=NULL;
            }

        }
        else
        {
          //  cout<<"can never be moved"<<endl;
            arr=NULL;
        }
        for(int x1=0;x1<15;x1++)
        {
            for(int x2=0;x2<15;x2++)
            {
                grid[x1][x2]=tgrid[x1][x2];
                
            }
        }
        return arr;
        
    }
    int hit(int cntrl=0)
    {
        for(int i=0;i<15;i++)
        {
            for(int j=0;j<15;j++)
            {
                int gl=grid[i][j].length();
                if(gl>2 && grid[i][j][0]!='*')
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
                                if(cntrl==0)
                                {
                                    string temp=grid[i][j];
                                    grid[i][j]=strremove(prev+48,temp);
                                    this->hits[gc-48]++;
                                    addtoken(prev);
                                }
                            //    cout<<prev<<"was hit!"<<endl;

                                return prev;
                                //prev(int) got hit!
                            }
                        }
                    }   
                }                
            }

        }
        return -1;
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
    int* move(int p,int i,int j,int steps)
    {
        int* arr=new int[3];
        arr[0]=-1;
        arr[1]=-1;
        arr[2]=-1;

        if(grid[i][j].find(char(p+48),0)!= String::InvalidPos &&(grid[i][j][0]=='_' || grid[i][j][0]=='*' ||grid[i][j][0]=='-'))
        {
            int left=steps;
            for(int k=0;k<steps;k++)
            {
                //this->draw();
               // cout<<"fidning "<<p<<" from "<<grid[i][j]<<endl;
                if(!((i==6 && j==7)||(i==7 && j==6)||(i==7 && j==8)||(i==8 && j==7)))
                {
                 //   cout<<"inside"<<endl;
                    left--;
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
            int* arr=new int[3];
            arr[0]=left;
            arr[1]=i;
            arr[2]=j;
            return arr;
        }
        else
        {
            return NULL;
        }

    }



};


#endif
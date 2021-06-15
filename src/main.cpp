#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>
#include <unistd.h>
//#include <signal.h>
#include <semaphore.h>
#include <pthread.h>
#include "../classes/dice.h"
#include "../classes/logging.h"
#include "../classes/Board.h"
using namespace sf;
using namespace std;
int x=1;
int d=1;
int currp=0;
int currdp=0;
sem_t sdie ;
sem_t sdieroll ;
sem_t sdieused ;
sem_t sboard ;
sem_t assisstant ;

int won=0;


struct threadDesc
{
  RenderWindow* app;
  Board* board;
  dice* die;
  int player;
  threadDesc()
  {
    app=NULL;
    board=NULL;
    die=NULL;
    player=0;

  }
  threadDesc(RenderWindow* rw,Board* b,dice* d)
  {
    app=rw;
    board=b;
    die=d;
    player=0;

  }
};

void*player(void*arg)
{
  threadDesc* p=((threadDesc*)arg);
  sem_wait (&sdie) ;

// in button of die roll if(roll finsihed) {sdierollpost}else {roll}
// cout<<"waitign for diece roll player :"<<p->player<<endl;
  currdp=p->player;
 
  sem_wait (&sdieroll) ;
  currdp=0;
 // cout<<"die rolled confirmed"<<endl;
	sem_post(&sdie);

  sem_wait(&sboard);
  // all die used;
 // cout<<"set player to:"<<p->player<<endl;
  currp=p->player;
  sem_wait(&sdieused);
  currp=0;
  sem_post(&sboard);



}
void*mantain(void *arg)
{

    threadDesc* td=(threadDesc*)arg;

  while(td->app->isOpen())
  {
        won= td->board->won();
    sem_wait (&assisstant) ;
    td->board->hit();
        won= td->board->won();

  }
}

void*master(void *arg)
{
  sem_init(&sboard,0,1);
  sem_init(&sdie,0,1);
  sem_init(&sdieroll,0,0);
  sem_init(&sdieused,0,0);
  sem_init(&assisstant,0,1);

  pthread_t assisstant;
  threadDesc* td=(threadDesc*)arg;

  pthread_create(&assisstant,NULL,&mantain ,td);		

  threadDesc* tds=new threadDesc[4];
  for(int i=0;i<4;i++)
  {
    tds[i].app=td->app;
    tds[i].board=td->board;
    tds[i].die=td->die;
    tds[i].player=i+1;

  }
  pthread_t tok[4];
  while(td->app->isOpen())
  {
    
    for(int i=0;i<4;i++)
    {
      pthread_create(&tok[i],NULL,&player ,&tds[i]);		
    }
    for(int i=0;i<4;i++)
    {
      pthread_join(tok[i],NULL);		
      if(won!=0){cout<<"He won!"<<endl;tds->app->close();}
 
    }
    tds->die->clear_players();
  }
	pthread_exit(NULL);
}


void status(int player, RenderWindow& app){
  Sprite token;
  Texture token_texture;
  token_texture.loadFromFile("images/tokens/token_sheet.png");
  token.setTexture(token_texture);
  IntRect tok_rects[4];
  tok_rects[0] = IntRect(0,0,60,50);
  tok_rects[1] = IntRect(0,50,60,50);
  tok_rects[2] = IntRect(60,0,60,50);
  tok_rects[3] = IntRect(60,50,60,50);
  token.setTextureRect(tok_rects[player-1]);
  token.setPosition(800,600);
  app.draw(token);
}
int main()
{
    srand(time(0));
    RenderWindow app(VideoMode(1280,720), "Ludo");
    app.setFramerateLimit(60);
    sf::Music music;
    if (!music.openFromFile("audio/mainmenu/strongandstrike.wav"))
      return -1; // error
    Texture dice_texture;
    dice_texture.loadFromFile("images/dice/dices6.png");
    Texture border;
    border.loadFromFile("images/tokens/border.jpeg");
    Sprite borders(border);
    dice Dice(750,600,dice_texture);
    music.play();
    music.setVolume(1);
    
    // Loading textures
    Texture t[5];
   Texture right_bg;     
   right_bg.loadFromFile("images/background/right_bg.jpg");
      Sprite right_background;
    right_background.setTexture(right_bg);
    right_background.setPosition(700,22);
    right_background.setScale(1.7f,2.0f);
    t[0].loadFromFile("images/background/board.png");
    t[1].loadFromFile("images/tokens/token1.png");
    t[2].loadFromFile("images/tokens/token2.png");
    t[3].loadFromFile("images/tokens/token3.png");
    t[4].loadFromFile("images/tokens/token4.png");
    //Making sprites from textures
    Sprite boardS(t[0]);
    Sprite tokensS[4]={Sprite(t[1]),Sprite(t[2]),Sprite(t[3]),Sprite(t[4])};
    //initializing classes with sprites
    Board board(0,0,&boardS,&borders,&app);
    board.initTokens(tokensS);
    threadDesc tinfo(&app,&board,&Dice);
    pthread_t mastert;
    pthread_create(&mastert ,NULL,&master ,&tinfo);		
   // int nx=0;
    while (app.isOpen())
    {
      app.clear();
      Event e;
      while (app.pollEvent(e))
      {
          if (e.type == Event::Closed)
            app.close();
                   
          if (e.type == Event::MouseButtonPressed)
            if (e.key.code == Mouse::Left)
            {
                int* arr=board.selectgrid(Mouse::getPosition().x,Mouse::getPosition().y);
            //    cout<<"curr p:"<<currp<<" i:"<<arr[0]<<" j:"<<arr[1]<<endl;
                  if(currp!=0 && arr!=NULL && !Dice.player[currp-1].empty() )
                  {

                      for (int i=0; i<Dice.player[currp-1].size(); i++){cout<<Dice.player[currp-1][i]<<" ";}
                      cout<<endl;

//                    cout<<"at least got in"<<endl;
                    int s=Dice.player[currp-1].size();
  //                                    cout<<"at least got in1"<<endl;
    //                cout<<"s:"<<s<<endl;
                    int roller=Dice.player[currp-1][s-1];
              //      Dice.player[currp-1].pop_back();
      //                                cout<<"at least got in2"<<endl;

                    int* pre=board.predict(currp,arr[0],arr[1],roller);
        //            cout<<"currp:"<<currp<<" coor i:"<<arr[0]<<" j:"<<arr[1]<<endl; 
                    if(pre==NULL)
                    {
                      cout<<"It wont move"<<endl;
                    }
                    else
                    {
                      Dice.player[currp-1].pop_back();
                      board.move(currp,arr[0],arr[1],roller);
                      cout<<"It will move to i:"<<pre[1]<<" j:"<<pre[2]<<" and hit:"<<pre[0]<<endl;
                    }
                  }
                  if(Dice.player[currp-1].empty())
                  {
                    sem_post(&sdieused);
                  }
                  sem_post(&assisstant);
                
          //      std::cout<<"x:"<<Mouse::getPosition().x<<" "<<"y:"<<Mouse::getPosition().y<<std::endl;
            }
          if (e.type == Event::KeyPressed)
          {
            if(e.key.code == Keyboard::Escape)
              app.close();
            if (e.key.code == Keyboard::Space)
            {
              if(currdp!=0)
              {
                if(!Dice.endturn(currdp))
                {
                    Dice.complete_roll(currdp,app); 
//                    for (int i=0; i<roll.size(); i++){cout<<roll[i]<<" ";}
  //                  cout<<endl;

                }

                if(Dice.endturn(currdp))
                { 
                    //if wasted
                    if (Dice.turn_wasted(currdp)){  //checking for player 1
                      cout<<"Player turn was wasted\n";

                    }
                      sem_post(&sdieroll);

                }
                
              }


            }
             // Dice.roll_Dice(123,app);
            if(e.key.code == Keyboard::P)
            {

                if(currp!=0 && !Dice.player[currp-1].empty() )
                {
                    bool six=false;
                    vector<int> temp;
                    for (int i=0; i<Dice.player[currp-1].size(); i++)
                    {
                      if(Dice.player[currp-1][i]==6 && !six)
                      {
                        six=true;
                      }
                      else
                      {
                        temp.push_back(Dice.player[currp-1][i]);
                      }

                    }
                    if(six)
                    if(board.opentoken(currp))
                    {
                      Dice.player[currp-1]=temp;
                    }
                }
            //  nx++;
             // board.move(1,8,13,17);
            //  board.move(2,1,8,nx);
              //board.move(3,6,1,nx);
             // board.move(4,13,6,nx);

            }
            if(e.key.code == Keyboard::S)
            {
              

                if(currp!=0 )
                {
                    if(Dice.turn_wasted(currp))
                    {
                      cout<<"skipping since 19999"<<endl;
                      sem_post(&sdieused);
                    }
                    else if(!Dice.player[currp-1].empty())
                    {
                      bool six=false;
                      for (int i=0; i<Dice.player[currp-1].size(); i++)
                      {
                        if(Dice.player[currp-1][i]==6 && !six)
                        {
                          six=true;
                        }
                      }
                      if(six)
                      {
                 //       cout<<"sixeeer!"<<endl;
                        
                      }
                      else
                      {

                      //    cout<<"yeeeaah!"<<endl;
                      }
                      if(!six && !board.addtoken(currp,1))
                      {
                        
                                            sem_post(&sdieused);
                       //     cout<<"skipped!"<<endl;
                      }
                    }
                }
            //  nx++;
             // board.move(1,8,13,17);
            //  board.move(2,1,8,nx);
              //board.move(3,6,1,nx);
             // board.move(4,13,6,nx);

            }

          }
      }
      //cout<<board.won()<<"has won the game!"<<endl;
      if (Dice.isRolling()) {x = (rand()%6)+1;} //give a new x to display
      Dice.animate_roll(x,app);
      app.draw(right_background);
      Dice.drawDice(x,app);
      board.draw();
            if(currp!=0)
      status(currp,app);

      app.display();
    }
    return 0;
}
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
sem_t sdie ;
sem_t sdieroll ;
sem_t sdieused ;
sem_t sboard ;


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
 cout<<"waitign for diece roll player :"<<p->player<<endl;
 
  sem_wait (&sdieroll) ;
  cout<<"die rolled confirmed"<<endl;
	sem_post(&sdie);
  sem_wait(&sboard);
  // all die used;
  cout<<"set player to:"<<p->player<<endl;
  currp=p->player;
  sem_wait(&sdieused);
  currp=0;
  sem_post(&sboard);



}
void*master(void *arg)
{
  sem_init(&sboard,0,1);
  sem_init(&sdie,0,1);
  sem_init(&sdieroll,0,0);
  sem_init(&sdieused,0,0);

  threadDesc* td=(threadDesc*)arg;
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
    }

  }
	pthread_exit(NULL);
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
    dice Dice(750,600,dice_texture);
    music.play();
    music.setVolume(10);
    
    // Loading textures
    Texture t[5];
    t[0].loadFromFile("images/background/board.png");
    t[1].loadFromFile("images/tokens/token1.png");
    t[2].loadFromFile("images/tokens/token2.png");
    t[3].loadFromFile("images/tokens/token3.png");
    t[4].loadFromFile("images/tokens/token4.png");
    //Making sprites from textures
    Sprite boardS(t[0]);
    Sprite tokensS[4]={Sprite(t[1]),Sprite(t[2]),Sprite(t[3]),Sprite(t[4])};
    //initializing classes with sprites
    Board board(0,0,&boardS,&app);
    board.initTokens(tokensS);
    threadDesc tinfo(&app,&board,&Dice);
    pthread_t mastert;
    pthread_create(&mastert ,NULL,&master ,&tinfo);		
   // int nx=0;
    while (app.isOpen())
    {
      board.hit();
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
                if(arr!=NULL)
                if(board.move(currp,arr[0],arr[1],d))
  	            sem_post(&sdieused);
          //      std::cout<<"x:"<<Mouse::getPosition().x<<" "<<"y:"<<Mouse::getPosition().y<<std::endl;
            }
          if (e.type == Event::KeyPressed)
          {
            if(e.key.code == Keyboard::Escape)
              app.close();
            if (e.key.code == Keyboard::Space)
            {
                d=(rand()%6)+1;
                sleep(2);
                cout<<"rolled "<<d<<endl;
                sem_post(&sdieroll);


            }
             // Dice.roll_Dice(123,app);
            if(e.key.code == Keyboard::F)
            {
            //  nx++;
             // board.move(1,8,13,17);
            //  board.move(2,1,8,nx);
              //board.move(3,6,1,nx);
             // board.move(4,13,6,nx);

            }

          }
      }
      if (Dice.isRolling()) {x = (rand()%6)+1;} //give a new x to display
      Dice.animate_roll(x,app);
      Dice.drawDice(x,app);
      board.draw();
      app.display();
    }
    return 0;
}
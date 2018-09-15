#include "game.h"
#include "qdebug.h"
#include "qtimer.h"
#include "mainwindow.h"

#define NBCANS 16



game::game(QWidget *parent, QString filename, QString PATH):QLabel(parent),filename(filename),PATH(PATH)
{


    this->hide();


    background = new QPixmap(filename); //preload image
    this->resize(1920,1080);
    this->setPixmap(*background);



}


void game::start(int nb)
{

    this -> show();
    leftToPop = nb;
    prewon = false;
   QTimer::singleShot(1000,this,SLOT(enableGame()));
}



void game::enableGame()
{


    generateCans(NBCANS);

}





void game::generateCans(int nbCans)
{

    double xspeed,yspeed;
    double x0,y0,size;

    double deltax = WIDTH/(nbCans/2+2);

    can *b;

    for (int i = 0; i<nbCans;i++)
    {
        //let's distribute balloons horizontally:
        if (i<nbCans/2)
        {
            x0 = deltax *((double)1+(double)i);
            y0 = -HEIGHT ;//+qrand()%400;
        }
        else
        {
            x0 = deltax*(1+(double)i-(double)nbCans/2);
            y0 = -0.5*HEIGHT;// +qrand()%400;
        }




        xspeed = (100+qrand()%100)*SPEED;
        yspeed = (250+qrand() % (250))*SPEED;
        size = ((double)20+qrand() % (20))/35;


        b = new can(this,x0,y0,size,i,100,xspeed,yspeed,PATH);

        cans.push_back(b);
        connect(b,SIGNAL(popped(int)),this,SLOT(getPopped(int)));
    }
}


void game::getPopped(int id)
{

    if(prewon)
    {

        won();
        return;
    }

    leftToPop--;
    if (leftToPop<=0)
    {


        for (auto can:cans)
        {
            if (can->id!= id)
                can->hide();
            else
                can->animateWin();

        }

        prewon = true;




    }
    else
    {
        qDebug()<<"left to pop: "<<leftToPop;

    }

}



void game::won()
{


    for (auto can:cans)
    {
        can->deleteLater();

    }

    cans.clear();
    emit gameWon();

}




game::~game()
{


}



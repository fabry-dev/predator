#include "keyboard.h"
#include "qdebug.h"
#include "qtimer.h"
#include "mainwindow.h"




keyboard::keyboard(QWidget *parent,int x,int y,int w,int h):QFrame(parent)
{

QStringList items = QStringList() <<"a"<<"b"<<"c"<<"d"<<"e"<<"f"<<"g"<<"h"<<"i"<<"j"<<"k"<<"l"<<"m"<<"n"<<"o"<<"p"<<"q"<<"r"<<"s"<<"t"<<"u"<<"v"<<"w"<<"x"<<"y"<<"z"<<"@"<<"."<<"-"<<"_"<<"0"<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9";




    setGeometry(x,y,w,h);



   // qDebug()<<items[0];


    int nb = items.size();
    int nx = 10;
    int ny = nb/nx+1;

    int i = 0;
    int dx,dy,hb,wb;

    dx = 10;


    wb = (w-(nx+1)*dx)/nx;
    hb = 50;

    qDebug()<<ny;
    dy=(h-hb*ny)/(ny+1);

    setStyleSheet("background-color: rgba(105, 105, 255, 100);border: 3px solid black; border-radius: 10px;");


    for (auto c:items)
    {

        QPushButton *b = new QPushButton(this);
        b->setCheckable(false);

        b->setText(c);
        b->setGeometry((i%nx+1)*dx+i%nx*wb,(i/nx+1)*dy+i/nx*hb,wb,hb);
        b->setStyleSheet("background-color: rgba(105, 105, 255, 255);border: 3px solid black; border-radius: 10px;");

        b->show();
        i++;

    }






    show();




    //


}



keyboard::~keyboard()
{


}



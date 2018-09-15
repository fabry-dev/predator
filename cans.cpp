#include "cans.h"
#include "mainwindow.h"
#include "QHBoxLayout"

cEventFilter::cEventFilter():QObject()
{}

cEventFilter::~cEventFilter()
{}

bool cEventFilter::eventFilter(QObject* object, QEvent* event)
{


    if(event->type()==QEvent::MouseButtonPress)
    {


        ((can*)object)->pop();
    }

    else
        if(event->type()==QEvent::Resize)
        {

            ((can*)object)->updResize();

        }

    return false;
}




void can::updResize()
{

    setPixmap(activeImage->scaled(this->width(),this->height()));

}





can::can(QWidget *parent, double x, double y, double size, int id, int fps, double xspeed, double yspeed,QString PATH):QLabel(parent),x0(x),y0(y),size(size),id(id),fps(fps),xspeed(xspeed),yspeed(yspeed)
{


    QString balloonFileName;
    balloonFileName = PATH+"can"+QString::number(qrand()%3+1)+".png";
    QString voucherFileName;
    voucherFileName = PATH+"voucher.png";

    QTransform transform;
    QTransform trans = transform.rotate(qrand()%20*(1-2*(qrand()%2)));




    //canImage = new QPixmap(QPixmap(balloonFileName).transformed(trans));
    canImage = QPixmap(balloonFileName).transformed(trans);
    voucherImage = QPixmap(voucherFileName);




    activeImage = &canImage;
    phase = qrand()%6;


    this->resize(canImage.width()*size,canImage.height()*size);
    this->y = y0-height();

    canImage = canImage.scaled(width(),height());
    setPixmap(canImage);




    x1=x;
    y1=y;
    move(x,y);
    show();
    t = 0;
    tsign = new QTimer();
    connect(tsign,SIGNAL(timeout()),this,SLOT(moveCan()));
    tsign->start(1000/fps);

    installEventFilter(new cEventFilter());

    stopped = false;
    clickable = true;

    animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);



     connect(this,SIGNAL(destroyed(QObject*)),animation,SLOT(deleteLater()));
    connect(this,SIGNAL(destroyed(QObject*)),tsign,SLOT(deleteLater()));

}





void can::animateWin()
{

    stopped = true;
    clickable = false;
    move(x1,y1);
    tsign->stop();

    activeImage = &voucherImage;


    setPixmap(activeImage->scaled(width(),height()));



    animation->setStartValue(geometry());
    int w = voucherImage.width();
    int h = voucherImage.height();



    animation->setEndValue(QRect((WIDTH-w)/2-10,(HEIGHT-h)/2,w,h));

    animation->start();

    QTimer::singleShot(1000,this,SLOT(stopAnimate()));


}


void can::stopAnimate()
{

    clickable = true;


}



void can::moveCan()
{



    if (stopped)
        return;

    double deltaY = yspeed/fps;
    y+=deltaY;
    double T0 = t/(10*fps);
    x=x0+cos(T0+phase)*xspeed;
    if (y>height()+((game*)parent())->height())
    {

        y = 0-height();
    }

    if(x<-0)
        x = 0;
    if(x>WIDTH-width())
        x=WIDTH-width();


    if ((x!=x)||(y!=y))
    {
        x=y=0;
        qDebug()<<"BUG"<<x0<<"-"<<y0<<"-"<<phase<<"-"<<T0<<"-"<<xspeed<<"-"<<yspeed<<"-"<<t;
    }


    move(x,y);

    t+= 1000/fps;

}

void can::pop()
{
    if (!clickable)
        return;
    // qDebug()<<"pop "<<id;


    x1 = x;
    y1 = y;
    y = 0-height();
    move(x,y);
    emit popped(id);


}
















can::~can()
{

}

#include "tap.h"
#include "qdebug.h"
#include "qtimer.h"
#include "mainwindow.h"





tap::tap(QWidget *parent, QString filename):QLabel(parent),filename(filename)
{


    this->hide();


    background = new QPixmap(filename); //preload image
    this->resize(1920,1080);
    this->setPixmap(*background);




}

void tap::mousePressEvent( QMouseEvent* ev )
{

    emit startGame();





}


tap::~tap()
{


}



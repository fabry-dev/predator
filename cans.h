#ifndef BALLOON_H
#define BALLOON_H
#include "QWidget"
#include "qobject.h"
#include "qlabel.h"
#include "QString"
#include "qpainter.h"
#include "QTimer"
#include "qdebug.h"
#include <math.h>
#include "qevent.h"
#include "QPropertyAnimation"



class cEventFilter: public QObject
{
    Q_OBJECT
public:
  cEventFilter();
  ~cEventFilter();

protected:
  bool eventFilter(QObject* object,QEvent* event);
};





class can:public QLabel
{
        Q_OBJECT
public:
    can(QWidget *parent, double x, double y, double size,  int id, int fps, double xspeed, double yspeed, QString PATH);
     ~can();
    void pop(void);
    int id;
    void animateWin();
    void updResize();
    void reset();

private:
        double x0,y0,size;
        int fps;
        double xspeed,yspeed;

        double x,y;
        QPainter *painter;
        double phase;
        QTimer *tsign;
        QPixmap canImage;
        QPixmap voucherImage;
        QPixmap *activeImage;
        double t;
        int xSpeed;
        bool stopped;
        bool clickable;
        int x1,y1;
         QPropertyAnimation *animation;



private slots:
    void moveCan();
    void stopAnimate();


signals:
    void gameWon();
    void popped(int);


};

#endif // BALLOON_H

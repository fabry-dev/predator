#ifndef EMAIL_H
#define EMAIL_H


#include "qobject.h"
#include "qpainter.h"
#include "qlabel.h"
#include "qthread.h"
#include "qevent.h"
#include <QMouseEvent>
#include "qstringlist.h"
#include "keyboard.h"
#include "QPropertyAnimation"





struct button {
   int x1,y1,x2,y2;
   QString txt;
};





class email:public QLabel
{
    Q_OBJECT

public:
    email(QWidget *parent = 0, QString filename="/home/fred/bg.bmp", QString fontname="");
    ~email();
    void mousePressEvent( QMouseEvent* ev );
    void keyPressEvent(QKeyEvent *ev);
    void start();

private:
    void addButton(int x1,int y1,int x2,int y2,QString txt);
    void initButtons();
    std::vector<button> buttonList;
    bool clickable,keyboardactive;
    QString filename;
    QPixmap* background;
    QString fontname;
    QString emailAddress;
    void updEmail();
    void updEmailDone();
    void sendEmail();
    QLabel *txt;
    QFont font;
    bool done;
    keyboard *keys;
    void animation();
    QPropertyAnimation *propanimation;
signals:
    void sendEmail(QString emailAd);

private slots:
    void transmitEmail();


};








#endif

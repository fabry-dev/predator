#ifndef KEYBOARD_H
#define KEYBOARD_H


#include "qobject.h"
#include "qpainter.h"
#include "qlabel.h"
#include "qthread.h"
#include "qevent.h"
#include <QMouseEvent>
#include "qstringlist.h"
#include "QPushButton"




class keyboard:public QFrame
{
    Q_OBJECT

public:
    keyboard(QWidget *parent = 0, int x=0, int y=0, int w=100, int h=100);
    ~keyboard();
private:
    std::vector<QPushButton*> keys;


};








#endif // SPLASH_H

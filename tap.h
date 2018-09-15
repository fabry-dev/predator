#ifndef TAP_H
#define TAP_H


#include "qobject.h"
#include "qpainter.h"
#include "qlabel.h"
#include "qthread.h"
#include "qevent.h"
#include <QMouseEvent>
#include "qstringlist.h"





class tap:public QLabel
{
    Q_OBJECT

public:
    tap(QWidget *parent = 0,QString filename="/home/fred/bg.bmp");
    ~tap();
    void mousePressEvent( QMouseEvent* ev );

private:
    QString filename;
    QPixmap* background;

signals:
    void startGame();

};








#endif // SPLASH_H

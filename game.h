#ifndef GAME_H
#define GAME_H


#include "qobject.h"
#include "qpainter.h"
#include "qlabel.h"
#include "qthread.h"
#include "qevent.h"
#include <QMouseEvent>
#include "qstringlist.h"
#include "cans.h"




class game:public QLabel
{
    Q_OBJECT

public:
    game(QWidget *parent = 0,QString filename="/home/fred/bg.bmp",QString PATH="");
    ~game();
    void start(int nb);

private:
    void generateCans(int nbCans);
    QString filename;
    QString PATH;
    QPixmap* background;
    std::vector<can*> cans;
    int leftToPop;
    bool prewon;

private slots:
    void getPopped(int id);
    void enableGame();
    void won();
signals:
    void gameWon();

};








#endif

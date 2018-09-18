#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cans.h"
#include <QTime>
#include "qstring.h"
#include "qmessagebox.h"
#include "qevent.h"
#include "qthread.h"
#include "tap.h"
#include "game.h"
#include "email.h"


class game;

#define WIDTH 1920
#define HEIGHT 1080
#define SPEED 1.5
#define PATH_DEFAULT QString("/home/fred/predatorData/")

struct upload_status {
  int lines_read;
};



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool getGameWon() ;
    void setGameWon(bool value);
    void resetTimer();

private:
    int activeCoupon;
    void getParams(QStringList params);

    QString PATH;
    bool HIDE_CURSOR;

    Ui::MainWindow *ui;

    void generateBalloons(int nbrBalloons);
    bool gameWon;
    tap *tp;
    game *gm;
    email *em;
    void keyPressEvent( QKeyEvent* ev );
    void initCurl();
    void sendEmail(QString);
    QString emailPayload;

private slots:
    void onGameWon();
    void startGame();
    void onEmailReceived(QString email);


};

#endif // MAINWINDOW_H

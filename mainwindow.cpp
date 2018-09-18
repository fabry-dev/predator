#include "qcoreapplication.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdatetime.h"
#include <memory>

#include "quickmail.h"
#include <stdio.h>


#include <QGuiApplication>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);

    getParams(QCoreApplication::arguments());


    if (HIDE_CURSOR)
    {
        QCursor cursor(Qt::BlankCursor);
        QApplication::setOverrideCursor(cursor);
        QApplication::changeOverrideCursor(cursor);
    }


    setWindowState(Qt::WindowFullScreen);






    tp = new tap(this,PATH+"tap.png");
    connect(tp,SIGNAL(startGame()),this,SLOT(startGame()));
    gm = new game(this,PATH+"gamebg.png",PATH);
    connect(gm,SIGNAL(gameWon()),this,SLOT(onGameWon()));
    em = new email(this,PATH+"emailbg2.png",PATH+"Futura.ttc");
    connect(em,SIGNAL(sendEmail(QString)),this,SLOT(onEmailReceived(QString)));

    tp->show();
    //sendEmail("frederic.abry@gmail.com");
}




void MainWindow::getParams(QStringList params)
{
    qDebug()<<params;
    if(params.size()>1)
        PATH = params[1];
    else
        PATH=PATH_DEFAULT;

    if(params.size()>2)
        HIDE_CURSOR = (params[2]=="true");
    else
        HIDE_CURSOR = false;

}




//mountaindew@voxbuyandwin.com

#define FROM        "mountaindew@voxbuyandwin.com"



#define SMTPSERVER  "auth.smtp.1and1.fr"
#define SMTPPORT    465
#define SMTPUSER    "mountaindew@voxbuyandwin.com"
#define SMTPPASS    "cE%g&uJ4*W23"







void list_attachment_callback (quickmail mailobj, const char* filename, quickmail_attachment_open_fn email_info_attachment_open, quickmail_attachment_read_fn email_info_attachment_read, quickmail_attachment_close_fn email_info_attachment_close, void* callbackdata)
{
    printf("[%i]: %s\n", ++*(int*)callbackdata, filename);
}







void MainWindow::sendEmail(QString email)
{



    quickmail_initialize();
    quickmail mailobj = quickmail_create(FROM, "Here's your Virgin Radio 4DX Exclusive Offer!");

    quickmail_add_to(mailobj, email.toStdString().c_str());

    quickmail_add_header(mailobj, "Importance: Low");
    quickmail_add_header(mailobj, "X-Priority: 5");
    quickmail_add_header(mailobj, "X-MSMail-Priority: Low");



    QString body =  "<img src='http://voxbuyandwin.com/images/email_image.jpeg'>";



    QByteArray body1 = body.toLatin1();
    char *body2 = body1.data();
    qDebug()<<body;

    quickmail_add_body_memory(mailobj, "text/html", body2, body.size(), 0);


    QString at = PATH+"ticket.pdf";
    QByteArray at1 = at.toLatin1();
    char *at2  = at1.data();

    quickmail_add_attachment_file(mailobj, at2, NULL);






    const char* errmsg;
    quickmail_set_debug_log(mailobj, stderr);
    qDebug()<<"test send";

    if ((errmsg = quickmail_send_secure(mailobj, SMTPSERVER, SMTPPORT, SMTPUSER, SMTPPASS)) != NULL)



    {

        qDebug()<< "Error sending e-mail: "<<stderr ;

        QString filename=PATH+"EmailsFailure.txt";
        qDebug()<<filename;
        QFile file( filename );
        if ( file.open(QIODevice::ReadWrite) )
        {
            QTextStream stream( &file );
            stream << email << endl;
        }
        file.close();


    }
    else
    {
        QString filename=PATH+"EmailsOK.txt";
        QFile file( filename );
        if ( file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text) )
        {
            QTextStream stream( &file );
            stream << email << endl;
        }
        file.close();
        qDebug()<<"Email sent.";


    }



    quickmail_destroy(mailobj);
    quickmail_cleanup();


}







void MainWindow::startGame()
{

    tp->hide();
    gm->start(qrand()%15+12);
    qDebug()<<"start game";

}





void MainWindow::onGameWon()
{

    qDebug()<<"game won!";
    gm->hide();
    tp->hide();
    em->start();
    //startGame();

}


void MainWindow::onEmailReceived(QString email)
{

    qDebug()<<"send: "<<email;
    tp->show();
    gm->hide();
    em->hide();

    sendEmail(email);

}





void MainWindow::keyPressEvent( QKeyEvent* ev )
{

    //ugly pass key event from mainwindow to email panelquickmail_add_body_memory(mailobj, "text/html", "This is a <b>test</b> e-mail.<br/>\nThis mail was sent using <u>libquickmail</u>.", 80, 0);
    em->keyPressEvent(ev);

}



bool MainWindow::getGameWon()
{
    return gameWon;
}


void MainWindow::setGameWon(bool value)
{
    gameWon = value;

}



MainWindow::~MainWindow()
{



    delete ui;
}

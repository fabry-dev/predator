#include "mainwindow.h"
#include "ui_mainwindow.h"












MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qsrand(QTime::currentTime().msec());

    initCurl();

    if (false)
    {
        QCursor cursor(Qt::BlankCursor);
        QApplication::setOverrideCursor(cursor);
        QApplication::changeOverrideCursor(cursor);
    }


    setWindowState(Qt::WindowFullScreen);


    tp = new tap(this,PATH+"tap.png");
    connect(tp,SIGNAL(startGame()),this,SLOT(startGame()));
    gm = new game(this,PATH+"gamebg.png");
    connect(gm,SIGNAL(gameWon()),this,SLOT(onGameWon()));
    em = new email(this,PATH+"emailbg.png",PATH+"Futura.ttc");
    connect(em,SIGNAL(sendEmail(QString)),this,SLOT(onEmailReceived(QString)));


    //tp->show();

    sendEmail("frederic.abry@gmail.com");

}


void MainWindow::initCurl()
{



    curl = curl_easy_init();

}





#define FROM_ADDR    "<mountaindew@voxbuyandwin.com>"
#define TO_ADDR      "<frederic.abry@gmail.com>"
#define CC_ADDR      ""

#define FROM_MAIL "Moutain Dew " FROM_ADDR
#define TO_MAIL   "A Receiver " TO_ADDR
#define CC_MAIL   "" CC_ADDR








static const char *payload_text[] = {
    "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n",
    "To: " TO_MAIL "\r\n",
    "From: " FROM_MAIL "\r\n",
    "Cc: " CC_MAIL "\r\n",
    "Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@"
    "rfcpedant.example.org>\r\n",
    "Subject: SMTP example message\r\n",
    "\r\n", /* empty line to divide headers from body, see RFC5322 */
    "The body of the message starts here.\r\n",
    "\r\n",
    "It could be a lot of lines, could be MIME encoded, whatever.\r\n",
    "Check RFC5322.\r\n",
    NULL
};







static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
    struct upload_status *upload_ctx = (struct upload_status *)userp;
    const char *data;

    if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
        return 0;
    }

    data = payload_text[upload_ctx->lines_read];

    if(data) {
        size_t len = strlen(data);
        memcpy(ptr, data, len);
        upload_ctx->lines_read++;

        return len;
    }

    return 0;
}




void MainWindow::sendEmail(QString email)
{

    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;
    struct upload_status upload_ctx;

    upload_ctx.lines_read = 0;


    if(curl) {
        qDebug()<<"start";
        /* This is the URL for your mailserver */
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.1and1.com");
        curl_easy_setopt(curl, CURLOPT_USERNAME,     "mountaindew@paristokyolive.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD,     "Mountaindew@paristokyo18");


//        curl_easy_setopt(curl, CURLOPT_USE_SSL,      (long)CURLUSESSL_ALL);



        /* Note that this option isn't strictly required, omitting it will result
           * in libcurl sending the MAIL FROM command with empty sender data. All
           * autoresponses should have an empty reverse-path, and should be directed
           * to the address in the reverse-path which triggered them. Otherwise,
           * they could cause an endless loop. See RFC 5321 Section 4.5.5 for more
           * details.
           */
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM_ADDR);

        /* Add two recipients, in this particular case they correspond to the
           * To: and Cc: addressees in the header, but they could be any kind of
           * recipient. */
        recipients = curl_slist_append(recipients, TO_ADDR);
        //recipients = curl_slist_append(recipients, CC_ADDR);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        /* We're using a callback function to specify the payload (the headers and
           * body of the message). You could just use the CURLOPT_READDATA option to
           * specify a FILE pointer to read from. */
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        /* Send the message */
        res = curl_easy_perform(curl);

        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* Free the list of recipients */
        curl_slist_free_all(recipients);

        /* curl won't send the QUIT command until you call cleanup, so you should
           * be able to re-use this connection for additional messages (setting
           * CURLOPT_MAIL_FROM and CURLOPT_MAIL_RCPT as required, and calling
           * curl_easy_perform() again. It may not be a good idea to keep the
           * connection open for a very long time though (more than a few minutes
           * may result in the server timing out the connection), and you do want to
           * clean up in the end.
           */
        curl_easy_cleanup(curl);

        qDebug()<<"sent";
    }

}







void MainWindow::startGame()
{

    tp->hide();
    gm->start(qrand()%15+5);
    qDebug()<<"start game";

}





void MainWindow::onGameWon()
{

    qDebug()<<"game won!";
    gm->hide();
    tp->hide();
    em->start();

}


void MainWindow::onEmailReceived(QString email)
{

    qDebug()<<"send: "<<email;
    tp->show();
    gm->hide();
    em->hide();

}





void MainWindow::keyPressEvent( QKeyEvent* ev )
{

    //ugly pass key event from mainwindow to email panel
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

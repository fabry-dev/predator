#include "screensaver.h"
#include "qdebug.h"
#include "mainwindow.h"




myEventFilter::myEventFilter():QObject()
{}

myEventFilter::~myEventFilter()
{}

bool myEventFilter::eventFilter(QObject* object, QEvent* event)
{
    if(event->type() == QEvent::MouseMove)
    {


        ((screenSaver*)object)->stop();

    }
    else if(event->type()==QEvent::MouseButtonPress)
    {

        ((screenSaver*)object)->stop();
    }



    return object->eventFilter(object, event);
}




screenSaver::screenSaver( QWidget *parent , const char *name ):QWidget(parent)
{

    resize(QSize(1920,1080));
    // Load the VLC engine
    videoInst = libvlc_new(0, NULL);

    // Create a new item

    QString videoFile;
    videoFile = PATH+"video3.avi";
    //videoFile = PATH+"video.mov";
    videoM = libvlc_media_new_path (videoInst,videoFile.toStdString().c_str());
    //libvlc_media_add_option(videoM, "input-repeat=-1");
    //libvlc_media_add_option(videoM, ":no-audio");

    // Create a media player playing environement
    videoMp = libvlc_media_player_new_from_media (videoM);





    //    libvlc_media_player_event_manager()
    libvlc_video_set_mouse_input(videoMp, false);
    libvlc_media_player_set_xwindow(videoMp, this->winId());

    setWindowState(Qt::WindowFullScreen);
 // setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->installEventFilter(new myEventFilter());

    //QWidget::show()
    play();

}





void screenSaver::play()
{
    this->show();
    this->raise();
    resize(QSize(1920,1080));
    libvlc_media_player_play (videoMp);
}




void screenSaver::stop()
{
    libvlc_media_player_stop(videoMp);


    this->deleteLater();

}


screenSaver::~screenSaver()
{

    libvlc_media_release (videoM);
    libvlc_media_player_release (videoMp);
    libvlc_release (videoInst);
    qDebug()<<"video player stopped";


}

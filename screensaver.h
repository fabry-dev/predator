#ifndef SCREENSAVER_H
#define SCREENSAVER_H


#include "qwidget.h"
#include <vlc/vlc.h>
#include "qevent.h"
#include <QObject>
#include <QMouseEvent>

class myEventFilter: public QObject
{
    Q_OBJECT
public:
  myEventFilter();
  ~myEventFilter();

protected:
  bool eventFilter(QObject* object,QEvent* event);
};


class screenSaver : public QWidget
   {
       Q_OBJECT
   public:
       screenSaver( QWidget *parent = 0, const char *name = 0 );
       ~screenSaver() ;
       void play();
       void stop();
       void loop();
       // event manager
       libvlc_event_manager_t *m_eventMgr;

       // event handler callback
       static void vlcEvent(const libvlc_event_t* event, void* vlcvideo_object);

   private:
       libvlc_instance_t * videoInst;
       libvlc_media_player_t *videoMp;
       libvlc_media_t *videoM;
   signals:
       void hasStopped();
   };



#endif // SCREENSAVER_H

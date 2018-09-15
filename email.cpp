#include "email.h"
#include "qdebug.h"
#include "qtimer.h"
#include "mainwindow.h"
#include "QRegularExpression"
#include "QRegularExpressionMatch"
#include "qfontdatabase.h"


#define sendX0 798
#define sendY0 896
#define sendX1 928
#define sendY1 954


#define borderX 10

#define textX0 (567)
#define textY0 773
#define textX1 (1159)
#define textY1 839



#define emailMaxLength 30










email::email(QWidget *parent, QString filename,QString fontname):QLabel(parent),filename(filename),fontname(fontname)
{


    this->hide();
    background = new QPixmap(filename); //preload image


    this->resize(1920,1760);



    this->setPixmap(*background);
    emailAddress = "";



    propanimation = new QPropertyAnimation(this, "geometry");
    propanimation->setDuration(500);

    int id = QFontDatabase::addApplicationFont(fontname);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(family,50);


    txt = new QLabel(this);
    txt->setText("");
    txt->setFont(font);

    //txt->setFont(font);
    txt->setAlignment(Qt::AlignCenter);
    txt->resize(textX1-textX0,textY1-textY0);
    txt->move(textX0,textY0);


    int x,y,w,h;

    w = width()/3;
    h = height()/3;

    x = (width()-w)/2;
    y = (height()-h)/2;

    initButtons();

}



void email::addButton(int x1,int y1,int x2,int y2,QString txt)
{
    button b;
    b.x1 = x1;     b.y1 = y1;     b.x2 = x2;     b.y2 = y2;    b.txt = txt;    buttonList.push_back(b);
}

void email::initButtons()
{

    addButton(19,1091,157,1150,"1");
    addButton(190,1091,328,1150,"2");
    addButton(366,1091,509,1150,"3");
    addButton(540,1091,681,1150,"4");
    addButton(713,1091,857,1150,"5");
    addButton(888,1091,1028,1150,"6");
    addButton(1065,1091,1203,1150,"7");
    addButton(1238,1091,1375,1150,"8");
    addButton(1405,1091,1556,1150,"9");
    addButton(1584,1091,1731,1150,"0");

    addButton(1760,1092,1901,1299,"back");

    addButton(19,1177,157,1294,"q");
    addButton(190,1177,328,1294,"w");
    addButton(366,1177,509,1294,"e");
    addButton(540,1177,681,1294,"r");
    addButton(713,1177,857,1294,"t");
    addButton(888,1177,1028,1294,"y");
    addButton(1065,1177,1203,1294,"u");
    addButton(1238,1177,1375,1294,"i");
    addButton(1405,1177,1556,1294,"o");
    addButton(1584,1177,1731,1294,"p");

    addButton(89,1325,226,1445,"a");
    addButton(261,1325,401,1445,"s");
    addButton(434,1325,573,1445,"d");
    addButton(608,1325,745,1445,"f");
    addButton(780,1325,917,1445,"g");

    addButton(950,1325,1092,1445,"h");
    addButton(1122,1325,1262,1445,"j");
    addButton(1295,1325,1433,1445,"k");
    addButton(1466,1325,1606,1445,"l");
    addButton(1639,1325,1900,1445,"done");


    addButton(188,1477,323,1590,"z");
    addButton(360,1477,489,1590,"x");
    addButton(525,1477,659,1590,"c");
    addButton(698,1477,829,1590,"v");
    addButton(867,1477,1003,1590,"b");

    addButton(1029,1477,1170,1590,"n");
    addButton(1205,1477,1340,1590,"m");
    addButton(1546,1477,1680,1590,".");

    addButton(20,1622,147,1744,"_");
    addButton(189,1622,318,1744,"@");
    addButton(1545,1622,1730,1744,"-");
}




void email::animation()
{

    clickable = true;
    keyboardactive= false;




    propanimation->setStartValue(geometry());
    int w = width();
    int h = height();

    qDebug()<<w<<h;

    propanimation->setEndValue(QRect(0,1080-1760,w,h));

    propanimation->start();

    keyboardactive = true;
    //QTimer::singleShot(1000,this,SLOT(stopAnimate()));


}





void email::mousePressEvent( QMouseEvent* ev )
{
    QPoint pt = ev->pos();




    if (done)
        return;



    QRegularExpression regExp("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");

    for (auto b:buttonList)
    {
        if((pt.x()>b.x1)&&(pt.x()<b.x2)&&(pt.y()>b.y1)&(pt.y()<b.y2))
        {

            if(b.txt=="back")
            {
                if (emailAddress.size()>0)
                {
                    emailAddress = emailAddress.remove(emailAddress.size()-1,1);
                    updEmail();
                }

            }
            else if (b.txt == "done")
            {

                QRegularExpressionMatch match = regExp.match(emailAddress, 0, QRegularExpression::PartialPreferCompleteMatch);
                if( match.hasMatch() )
                {

                    done = true;
                    updEmailDone();
                    QTimer::singleShot(500,this,SLOT(transmitEmail()));
                    //transmitEmail();
                }



            }
            else
            {

                QString buf;


                buf = emailAddress+b.txt;


                QRegularExpressionMatch match = regExp.match(buf, 0, QRegularExpression::PartialPreferCompleteMatch);


                if( ((match.hasPartialMatch())||(match.hasMatch()))&&(emailAddress.size()<emailMaxLength) )
                {

                    emailAddress.append(b.txt);
                    updEmail();
                }







            }


            return;
        }

    }













}




void email::transmitEmail()
{

    emit sendEmail(emailAddress);

}






void email::keyPressEvent( QKeyEvent* ev )
{



    QRegularExpression regExp("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");


    if (done)
        return;



}








void email::updEmail()
{
    emailAddress = emailAddress.toLower();

    //qDebug()<<emailAddress;

    QFontMetrics metrics(font);
    QSize size = metrics.size(0, emailAddress); //Get size of text
    float factorw = (textX1-textX0-2*borderX) / (float)size.width(); //Get the width factor
    float factorh = (textY1-textY0) / (float)size.height(); //Get the height factor
    float factor = qMin(factorw, factorh); //To fit contents in the screen select as factor
    //the minimum factor between width and height

    font.setPointSizeF(font.pointSizeF() * factor); //Set font size

    txt->setFont(font);
    txt->setText(emailAddress);
}





void email::updEmailDone()
{



    QFontMetrics metrics(font);
    QSize size = metrics.size(0, "Email sent!"); //Get size of text
    float factorw = (textX1-textX0-2*borderX) / (float)size.width(); //Get the width factor
    float factorh = (textY1-textY0) / (float)size.height(); //Get the height factor
    float factor = qMin(factorw, factorh); //To fit contents in the screen select as factor
    //the minimum factor between width and height

    font.setPointSizeF(font.pointSizeF() * factor); //Set font size

    txt->setFont(font);
    txt->setText("Email sent!");
}









void email::start()
{
    emailAddress = "";
    updEmail();
    this->show();
    done = false;

    clickable = true;

    animation();
}




email::~email()
{


}



#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

enemy::enemy() : QObject(), QGraphicsRectItem()
{
    //dessiner l'ennemi
    setRect(0,0,100,50);

    //connect
    QTimer * Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()),this,SLOT(move()));

    Timer->start(50);
};

enemy::~enemy(){

};

void enemy::move(){

};

#include "birdattack.h"
#include "scene.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>


birdattack::birdattack() : QObject(), QGraphicsRectItem()
{
    //dessiner l'ennemi
    setRect(0,0,100,50);

    //connect
    QTimer * Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()),this,SLOT(move()));

    Timer->start(50);
}

/*
birdattack::~birdattack()
{

}*/

qreal birdattack::getX()
{
    return xPos;
}

void birdattack::freezeInPlace()
{
    //xAnimation->stop();
}

void birdattack::setX(qreal x)
{
    xPos = x;
}

bool birdattack::collidesWithEnemy()
{
    return 0;
}

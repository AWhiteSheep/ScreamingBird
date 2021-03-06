#include "BirdAttack.h"
#include "scene.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>


BirdAttack::BirdAttack()
{
    //dessiner l'ennemi
    setRect(0,0,100,50);

    //connect
    QTimer * Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()),this,SLOT(move()));

    Timer->start(50);
}

BirdAttack::~BirdAttack()
{

}

qreal BirdAttack::getX()
{
    return xPos;
}

void BirdAttack::freezeInPlace()
{
    //xAnimation->stop();
}

void BirdAttack::setX(qreal x)
{
    xPos = x;
}

bool BirdAttack::collidesWithEnemy()
{
    return 0;
}

#include "BirdAttack.h"
#include "scene.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include <QPixmap>

BirdAttack::BirdAttack() : feu(new QGraphicsPixmapItem(QPixmap(":/images/pixel-fire-ball.png")))
{
    qDebug() << "constructeur du feu";

    feu->setPos(QPointF(0,0));// - QPointF(feu->boundingRect().width()/2, feu->boundingRect().height()/2));

};

BirdAttack::~BirdAttack()
{

}

qreal BirdAttack::getX()
{
    return xPos;
}

qreal BirdAttack::getY()
{
    return yPos;
}

void BirdAttack::freezeInPlace()
{
    //xAnimation->stop();
}

void BirdAttack::setX(qreal x)
{
    xPos = x;
}

void BirdAttack::setY(qreal y)
{
    yPos = y;
}

bool BirdAttack::collidesWithEnemy()
{
    return 0;
}

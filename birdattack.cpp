#include "BirdAttack.h"
#include "scene.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include <QPixmap>

BirdAttack::BirdAttack(qreal birdPosX, qreal birdPosY)
{
    // set position
    setPixmap(QPixmap(":/images/pixel-fire-ball.png"));
    setPos(QPoint(-60,birdPosY-103));

    // animation
    // connect to signal
    QTimer * timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    // set timer
    timer->start(30); //every 30 ms the fireball will move
}

BirdAttack::~BirdAttack()
{
    delete xAnimation;
}

void BirdAttack::move()
{
    // bouger la boule de feu
    setPos(x()+5, y());

    // delete if off the screan
    //if (pos().x() < );
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
    xAnimation->stop();
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

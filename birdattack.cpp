#include "BirdAttack.h"
#include "scene.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include <QPixmap>

BirdAttack::BirdAttack(qreal birdPosY, qreal limiteScreen)
{
    freeze = 0;

    // determiner la limite de l'écran pour être en mesure de détecter quand la boule sort du jeu
    rightLimiteScreen = limiteScreen;

    // set position
    setPixmap(QPixmap(":/images/pixel-fire-ball.png"));
    setPos(QPoint(10,birdPosY-20));

    // animation
    // connect to signal
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    // set timer
    timer->start(30); //every 30 ms the fireball will move
}

BirdAttack::~BirdAttack()
{
    //delete xAnimation;
    scene()->removeItem(this);
    delete timer;
}

void BirdAttack::move()
{
    // bouger la boule de feu
    if (freeze)
    {
        // don't move
    }
    else
    {
        //move
        setPos(x()+VITESSE_BOULE, y());
    }

    // delete if off the screan
    if (pos().x() + 20 > rightLimiteScreen)
    {
        delete this;
    }
}

/*
qreal BirdAttack::getX()
{
    //return xPos;
}

qreal BirdAttack::getY()
{
    //return yPos;
}

void BirdAttack::setX(qreal x)
{
    //xPos = x;
}

void BirdAttack::setY(qreal y)
{
    //yPos = y;
}
*/

void BirdAttack::freezeInPlace()
{
    freeze = 1;
}

bool BirdAttack::collidesWithEnemy()
{
    return 0;
}

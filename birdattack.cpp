#include "BirdAttack.h"
#include "scene.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include <QPixmap>

BirdAttack::BirdAttack(qreal birdPosY, qreal limiteScreen)
{
    // determiner la limite de l'écran pour être en mesure de détecter quand la boule sort du jeu
    rightLimiteScreen = limiteScreen;

    // set position
    setPixmap(QPixmap(":/images/pixel-fire-ball.png"));
    setPos(QPoint(-60,birdPosY-103));

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
    delete timer;
}

void BirdAttack::move()
{
    // bouger la boule de feu
    setPos(x()+VITESSE_BOULE, y());

    // delete if off the screan
    if (pos().x() + 20 > rightLimiteScreen)
    {

        qDebug() << "flamme trop loin";
        scene()->removeItem(this);
        qDebug() << "flamme retiree";
        delete this;
        qDebug() << "flamme deleted";
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
    xAnimation->stop();
}

bool BirdAttack::collidesWithEnemy()
{
    return 0;
}

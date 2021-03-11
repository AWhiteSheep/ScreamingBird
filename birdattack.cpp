#include "BirdAttack.h"
#include "scene.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include <QPixmap>

BirdAttack::BirdAttack(qreal birdPosY, qreal limiteScreen) : fireball(Frame1)
{
    // determiner la limite de l'écran pour être en mesure de détecter quand la boule sort du jeu
    rightLimiteScreen = limiteScreen;

    // set position
    setPixmap(QPixmap(":/images/Fireball/Frame-1.png"));
    setPos(QPoint(-60,birdPosY-15));

    //animation de la boule de feu
    animationFireball = new QTimer();
    connect(animationFireball, &QTimer::timeout, [=](){
        updatePixmap();
    });

    animationFireball->start(100);
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
    delete animationFireball;
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

int BirdAttack::updatePixmap()
{
    if(fireball == Fireball::Frame1)
    {
        setPixmap(QPixmap(":/images/Fireball/Frame-1.png"));
        fireball = Fireball::Frame2;
        return 0;
    }else if(fireball == Fireball::Frame2){
        setPixmap(QPixmap(":/images/Fireball/Frame-2.png"));
        fireball = Fireball::Frame3;
        return 0;
    }else if(fireball == Fireball::Frame3){
        setPixmap(QPixmap(":/images/Fireball/Frame-3.png"));
        fireball = Fireball::Frame4;
        return 0;
    }else if(fireball == Fireball::Frame4){
        setPixmap(QPixmap(":/images/Fireball/Frame-4.png"));
        fireball = Fireball::Frame5;
        return 0;
    }else if(fireball == Fireball::Frame5){
        setPixmap(QPixmap(":/images/Fireball/Frame-5.png"));
        fireball = Fireball::Frame6;
        return 0;
    }else if(fireball == Fireball::Frame6){
        setPixmap(QPixmap(":/images/Fireball/Frame-6.png"));
        fireball = Fireball::Frame1;
        return 0;
    }
    return 0;
}

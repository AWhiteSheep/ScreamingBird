#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

enemy::enemy() : Enemy(new QGraphicsPixmapItem(QPixmap(":/images/Flying-Koopa.png"))), pastBird(false)
{
    Enemy->setPos(QPointF(0,0) - QPointF(Enemy->boundingRect().width()/2,
                                                       Enemy->boundingRect().height()/2));
    addToGroup(Enemy);

    yPos = QRandomGenerator::global()->bounded(150);
    setPos(QPoint(0,0) + QPoint(260, yPos));

    qDebug()<<"enemy created";

    // création de l'animation de droite à gauche
    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(900);
    xAnimation->setEndValue(-600);
    xAnimation->setEasingCurve(QEasingCurve::Linear); // la function utiliser pour atteindre la position final
    xAnimation->setDuration(5500);
    connect(xAnimation, &QPropertyAnimation::finished, [=](){
        scene()->removeItem(this);
        delete this;
    });
    xAnimation->start();

};

enemy::~enemy()
{
    delete Enemy;
    delete xAnimation;
};

qreal enemy::x() const
{
    return m_x;
};

void enemy::freezeInPlace()
{
    xAnimation->stop();
};

void enemy::setX(qreal x)
{
    m_x = x;
    if(x < 0 && !pastBird) {
        pastBird = true;
    }

    if(collidesWithBird())
    {
        emit collideFail();
    }
    setPos(QPointF(0,0) + QPointF(x,yPos));

};

bool enemy::collidesWithBird()
{
    // list des items qui touche l'objet
    QList<QGraphicsItem*> collidingItems = Enemy->collidingItems();

    foreach(QGraphicsItem * item, collidingItems)
    {
        BirdItem * birdItem = dynamic_cast<BirdItem*>(item);
        if(birdItem)
            return true;
    }
    return false;
};


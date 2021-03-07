#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

enemy::enemy():
   WingDirection(0), pastBird(false)
{
    //set l'ennemi dans l'espace

    yPos = QRandomGenerator::global()->bounded(200);
    setPos(QPoint(0,0) + QPoint(260, yPos));

    //Commence l'animation des ailes
        EnemyWingsTimer = new QTimer(this);
        // listener pour le timer fait une appel à chaque fois le timer complêté
        connect(EnemyWingsTimer, &QTimer::timeout, [=](){
            updatePixmap();
        });

        EnemyWingsTimer->start(100);

    //Commence l'animation d'avancement

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
    delete xAnimation;
    delete EnemyWingsTimer;
};

qreal enemy::x() const
{
    return m_x;
};

void enemy::freezeInPlace()
{
    xAnimation->stop();
    EnemyWingsTimer->stop();

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
     QList<QGraphicsItem*> collidingItems = this->collidingItems();

   foreach(QGraphicsItem * item, collidingItems)
    {
        BirdItem * birdItem = dynamic_cast<BirdItem*>(item);
        if(birdItem)
            return true;
    }
    return false;
};

int enemy::updatePixmap()
{
    if(WingDirection == 0)
    {
        setPixmap(QPixmap(":/images/koopa/Koopa-1.png"));
        WingDirection++;
        return 0;
    }else if(WingDirection == 1){
        setPixmap(QPixmap(":/images/koopa/Koopa-2.png"));
        WingDirection++;
        return 0;
    }else if(WingDirection == 2){
        setPixmap(QPixmap(":/images/koopa/Koopa-1.png"));
        WingDirection++;
        return 0;
    }else if(WingDirection == 3){
        setPixmap(QPixmap(":/images/koopa/Koopa-2.png"));
        WingDirection++;
        return 0;
    }else if(WingDirection == 4){
        setPixmap(QPixmap(":/images/koopa/Koopa-3.png"));
        WingDirection++;
        return 0;
    }else if(WingDirection == 5){
        setPixmap(QPixmap(":/images/koopa/Koopa-4.png"));
        WingDirection++;
        return 0;
    }else if(WingDirection == 6){
        setPixmap(QPixmap(":/images/koopa/Koopa-3.png"));
        WingDirection++;
        return 0;
    }else if(WingDirection == 7){
        setPixmap(QPixmap(":/images/koopa/Koopa-4.png"));
        WingDirection = 0;
        return 0;
    }
    return 0;
}

#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

enemy::enemy():
   wingPosition(WingPosition::Frame1), pastBird(false)
{
    //set l'ennemi dans l'espace

    m_y = QRandomGenerator::global()->bounded(150);
    setPos(QPoint(0,0) + QPoint(260, m_y));

    //Commence l'animation des ailes
    EnemyWingsTimer = new QTimer(this);
    // listener pour le timer fait une appel à chaque fois le timer complêté
    connect(EnemyWingsTimer, &QTimer::timeout, [=](){
        updatePixmap();
    });

    EnemyWingsTimer->start(100);

    yAnimation = new QPropertyAnimation(this, "y", this);
    yAnimationTimer = new QTimer(this);
    connect(yAnimationTimer, &QTimer::timeout, [=](){
        isGoingUp = !isGoingUp;
        if(yAnimation->state() == QPropertyAnimation::Running)
            yAnimation->stop();
        if(isGoingUp)
        {
            yAnimation->setStartValue(m_y);
            yAnimation->setEndValue(m_y - 300);
        }
        else
        {
            yAnimation->setStartValue(m_y);
            yAnimation->setEndValue(m_y + 300);
        }
        yAnimation->setEasingCurve(QEasingCurve::Linear); // la function utiliser pour atteindre la position final
        yAnimation->setDuration(ENEMY_SPEED);
        yAnimation->setEasingCurve(QEasingCurve::Linear); // la function utiliser pour atteindre la position final
        yAnimation->start();
    });
    yAnimationTimer->start(ENEMY_SPEED);

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
    delete yAnimation;
    delete yAnimationTimer;
    delete EnemyWingsTimer;
};

qreal enemy::x() const
{
    return m_x;
};

qreal enemy::y() const
{
    return m_y;
};

void enemy::freezeInPlace()
{
    yAnimation->stop();
    xAnimation->stop();
    yAnimationTimer->stop();
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
    setPos(QPointF(0,0) + QPointF(x,m_y));

};

void enemy::setY(qreal y)
{
    m_y = y;
    setPos(QPointF(0,0) + QPointF(m_x,y));
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
    if(wingPosition == WingPosition::Frame1)
    {
        setPixmap(QPixmap(":/images/koopa/Koopa-1.png"));
        wingPosition = WingPosition::Frame2;
        return 0;
    }else if(wingPosition == WingPosition::Frame2){
        setPixmap(QPixmap(":/images/koopa/Koopa-2.png"));
        wingPosition = WingPosition::Frame3;
        return 0;
    }else if(wingPosition == WingPosition::Frame3){
        setPixmap(QPixmap(":/images/koopa/Koopa-1.png"));
        wingPosition = WingPosition::Frame4;
        return 0;
    }else if(wingPosition == WingPosition::Frame4){
        setPixmap(QPixmap(":/images/koopa/Koopa-2.png"));
        wingPosition = WingPosition::Frame5;
        return 0;
    }else if(wingPosition == WingPosition::Frame5){
        setPixmap(QPixmap(":/images/koopa/Koopa-3.png"));
        wingPosition = WingPosition::Frame6;
        return 0;
    }else if(wingPosition == WingPosition::Frame6){
        setPixmap(QPixmap(":/images/koopa/Koopa-4.png"));
        wingPosition = WingPosition::Frame7;
        return 0;
    }else if(wingPosition == WingPosition::Frame7){
        setPixmap(QPixmap(":/images/koopa/Koopa-3.png"));
        wingPosition = WingPosition::Frame8;
        return 0;
    }else if(wingPosition == WingPosition::Frame8){
        setPixmap(QPixmap(":/images/koopa/Koopa-4.png"));
        wingPosition = WingPosition::Frame1;
        return 0;
    }
    return 0;
};

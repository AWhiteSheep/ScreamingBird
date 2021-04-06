#include "Boss.h"
#include "scene.h"

Boss::Boss():lifeCount(2),
    groundPosition(1000),
    DeathFrame(deathFrame::Frame1),
    bossAlive(true)
{
    //set l'ennemi dans l'espace
    qDebug() << "Boss creer";

    updatePixmap();
    setY(0);
    setPos(QPoint(0,0) + QPoint(260, m_y));
    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(900);
    xAnimation->setEndValue(275);
    xAnimation->setEasingCurve(QEasingCurve::Linear); // la function utiliser pour atteindre la position final
    xAnimation->setDuration(5500);
    connect(xAnimation, &QPropertyAnimation::finished, [=](){
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
            yAnimation->setDuration(BOSS_SPEED);
            yAnimation->setEasingCurve(QEasingCurve::Linear); // la function utiliser pour atteindre la position final
            yAnimation->start();
        });
        yAnimationTimer->start(BOSS_SPEED);
    });
    xAnimation->start();

};

Boss::~Boss()
{
    delete xAnimation;
    delete yAnimation;
    delete yAnimationTimer;
};

qreal Boss::x() const
{
    return m_x;
};

qreal Boss::y() const
{
    return m_y;
};

void Boss::freezeInPlace()
{
    yAnimation->stop();
    xAnimation->stop();
    yAnimationTimer->stop();
};

void Boss::setX(qreal x)
{
    m_x = x;
    setPos(QPointF(0,0) + QPointF(x,m_y));

};

void Boss::setY(qreal y)
{
    m_y = y;
    if(collidesWithBirdAttack())
    {
        lifeDown();
    }
    setPos(QPointF(0,0) + QPointF(m_x,y));
};

bool Boss::collidesWithBirdAttack()
{
    // list des items qui touche l'objet
    QList<QGraphicsItem*> collidingItems = this->collidingItems();

   foreach(QGraphicsItem * item, collidingItems)
    {
        BirdAttack * birdItem = dynamic_cast<BirdAttack*>(item);
        if(birdItem)
        {
            QGraphicsScene * mScene = scene();
            mScene->removeItem(birdItem);
            return true;
        }
    }
    return false;
};

int Boss::updatePixmap()
{
 setPixmap(QPixmap(":/images/Boss/Boss-Frame-1.png"));
};

void Boss::lifeDown()
{
    if(bossAlive == true)
    {
        lifeCount--;
        qDebug() << "Life count :"<<lifeCount;
        if(lifeCount <= 0)
        {
            BossDeath();
        }
    }
};

int Boss::getLife()
{
    return lifeCount;
}

void Boss::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);
    rotationAnimation->start();
}

void Boss::BossDeath()
{
    bossAlive = false;
    yAnimation->stop();
    yAnimationTimer->stop();
    //Commence l'animation de mort
    deathTimer = new QTimer(this);
    // listener pour le timer fait une appel à chaque fois le timer complêté
    connect(deathTimer, &QTimer::timeout, [=](){
        deathAnimation = deathPixmap();
        if(deathAnimation == true)
        {
            yAnimation->start();
            deathTimer->stop();
        }
    });
    deathTimer->start(100);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(2000);
    // initialisation de l'animation donnant la rotation
    rotationAnimation = new QPropertyAnimation(this, "rotation", this);
    rotateTo(90, 1200, QEasingCurve::InQuad);
    connect(yAnimation, &QPropertyAnimation::finished, [=](){
        emit Bossdead();
        scene()->removeItem(this);
        delete this;

    });
}

bool Boss::deathPixmap()
{
    if(DeathFrame == deathFrame::Frame1)
    {
        setPixmap(QPixmap(":/images/Boss/Boss-Frame-14.png"));
        DeathFrame = deathFrame::Frame2;
        return false;
    }else if(DeathFrame == deathFrame::Frame2){
        setPixmap(QPixmap(":/images/Boss/Boss-Frame-15.png"));
        DeathFrame = deathFrame::Frame3;
        return false;
    }else if(DeathFrame == deathFrame::Frame3){
        setPixmap(QPixmap(":/images/Boss/Boss-Frame-16.png"));
        DeathFrame = deathFrame::Frame4;
        return false;
    }else if(DeathFrame == deathFrame::Frame4){
        setPixmap(QPixmap(":/images/Boss/Boss-Frame-17.png"));
        DeathFrame = deathFrame::Frame5;
        return false;
    }else if(DeathFrame == deathFrame::Frame5){
        setPixmap(QPixmap(":/images/Boss/Boss-Frame-18.png"));
        DeathFrame = deathFrame::Frame6;
        return false;
    }else if(DeathFrame == deathFrame::Frame6){
        setPixmap(QPixmap(":/images/Boss/Boss-Frame-19.png"));
        DeathFrame = deathFrame::Frame1;
        return true;
    }
}

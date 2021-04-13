/*
*
*   Author: jara2502, pera3307, rouy2404, veic1101
*   Date: 2021-04-13 (mar., 13 avril. 2021)
*
*/
#include "Boss.h"
#include "scene.h"

Boss::Boss():lifeCount(20),
    groundPosition(1000),
    DeathFrame(deathFrame::Frame1),
    BossAnimation(bossAnimation::Frame_1),
    bossAlive(true),
    hitIndex(0)
{
    qDebug() << "Boss creer";
    //debut de l'animation du boss
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, [=](){
        updatePixmap();
    });
    animationTimer->start(100);
    //animation hit
    hitTimer = new QTimer(this);
    connect(hitTimer, &QTimer::timeout, [=](){
        animationTimer->stop();
        deathPixmap();
        hitIndex++;
        if(hitIndex >= 5)
        {
            hitTimer->stop();
            hitIndex = 0;
            animationTimer->start(100);
            DeathFrame = deathFrame::Frame1;
        }
    });
    //set l'ennemi dans l'espace
    setY(75);
    setPos(QPoint(260, m_y));
    //animation x
    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(900);
    xAnimation->setEndValue(275);
    xAnimation->setEasingCurve(QEasingCurve::Linear); // la function utiliser pour atteindre la position final
    xAnimation->setDuration(5500);
    connect(xAnimation, &QPropertyAnimation::finished, [=](){
        //animation y + commancement du combat
        emit BeginAttack();
        yAnimation = new QPropertyAnimation(this, "y", this);
        yAnimationTimer = new QTimer(this);
        connect(yAnimationTimer, &QTimer::timeout, [=](){
            isGoingUp = !isGoingUp;
            if(yAnimation->state() == QPropertyAnimation::Running)
                yAnimation->stop();
            if(isGoingUp)
            {
                yAnimation->setStartValue(m_y);
                yAnimation->setEndValue(m_y - 350);
            }
            else
            {
                yAnimation->setStartValue(m_y);
                yAnimation->setEndValue(m_y + 350);
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
        hitTimer->start(100);
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

void Boss::updatePixmap()
{
    if(BossAnimation == bossAnimation::Frame_1)
    {
        setPixmap(QPixmap(":/images/Boss/Boss-Frame-1.png"));
        BossAnimation = bossAnimation::Frame_2;
    }else if(BossAnimation == bossAnimation::Frame_2){
        setPixmap(QPixmap(":/images/Boss/Boss-Frame-2.png"));
        BossAnimation = bossAnimation::Frame_3;
    }else if(BossAnimation == bossAnimation::Frame_3){
        setPixmap(QPixmap(":/images/Boss/Boss-Frame-3.png"));
        BossAnimation = bossAnimation::Frame_4;
    }else if(BossAnimation == bossAnimation::Frame_4){
        setPixmap(QPixmap(":/images/Boss/Boss-Frame-4.png"));
        BossAnimation = bossAnimation::Frame_5;
    }else if(BossAnimation == bossAnimation::Frame_5){
        setPixmap(QPixmap(":/images/Boss/Boss-Frame-5.png"));
        BossAnimation = bossAnimation::Frame_6;
    }else if(BossAnimation == bossAnimation::Frame_6){
        setPixmap(QPixmap(":/images/Boss/Boss-Frame-6.png"));
        BossAnimation = bossAnimation::Frame_7;
    }else if(BossAnimation == bossAnimation::Frame_7){
        setPixmap(QPixmap(":/images/Boss/Boss-Frame-7.png"));
        BossAnimation = bossAnimation::Frame_8;
    }else if(BossAnimation == bossAnimation::Frame_8){
        setPixmap(QPixmap(":/images/Boss/Boss-Frame-8.png"));
        BossAnimation = bossAnimation::Frame_9;
    }else if(BossAnimation == bossAnimation::Frame_9){
        setPixmap(QPixmap(":/images/Boss/Boss-Frame-9.png"));
        BossAnimation = bossAnimation::Frame_10;
    }else if(BossAnimation == bossAnimation::Frame_10){
        setPixmap(QPixmap(":/images/Boss/Boss-Frame-10.png"));
        BossAnimation = bossAnimation::Frame_11;
    }else if(BossAnimation == bossAnimation::Frame_11){
        setPixmap(QPixmap(":/images/Boss/Boss-Frame_11.png"));
        BossAnimation = bossAnimation::Frame_12;
    }else if(BossAnimation == bossAnimation::Frame_12){
        setPixmap(QPixmap(":/images/Boss/Boss-Frame-12.png"));
        BossAnimation = bossAnimation::Frame_13;
    }else if(BossAnimation == bossAnimation::Frame_13){
        setPixmap(QPixmap(":/images/Boss/Boss-Frame-13.png"));
        BossAnimation = bossAnimation::Frame_1;
    }
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
    animationTimer->stop();
    hitTimer->stop();
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
    deathTimer->start(200);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(2000);
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

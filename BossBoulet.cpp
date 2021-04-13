/*
*
*   Author: jara2502, pera3307, rouy2404, veic1101
*   Date: 2021-04-13 (mar., 13 avril. 2021)
*
*/
#include "BossBoulet.h"

BossBoulet::BossBoulet(qreal BossPosY, qreal limiteScreen) :boulet(Frame_1)
{

    freeze = 0;
    // determiner la limite de l'écran pour être en mesure de détecter quand la boule sort du jeu
    rightLimiteScreen = limiteScreen;

    // set position
    setPos(QPoint(275,BossPosY));
        qDebug() << "Boulet creer";
        animationBoulet = new QTimer();
        connect(animationBoulet, &QTimer::timeout,[=](){
            updatePixmapBoulet();
        });
        animationBoulet->start(100);
    // connect to signal
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    // set timer
    timer->start(30); //every 30 ms the fireball will move
}

BossBoulet::~BossBoulet()
{
    delete timer;
    delete animationBoulet;
}

void BossBoulet::move()
{
    // if fireball collides with enemy, destroy both
    // colliding_items contient tous les items qui entre en collision avec la boule de feu

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i=0, n=colliding_items.size(); i<n; i++)
    {
        // si l'objet qui est en collision avec la boule de feu est un enemy,
        if (typeid(*(colliding_items[i])) == typeid(BirdItem))
        {
            // remove them both
            emit collideFail();
            delete this;
            return; // sort de la fonction
        };

    };

    // bouger la boule de feu
    if (freeze)
    {
        // don't move
    }
    else
    {
       setPos(x()-VITESSE_BOULET,y());
    }

    // delete if off the screan
    if (pos().x() + 20 > rightLimiteScreen)
    {
      //  delete this;
    }
}

void BossBoulet::freezeInPlace()
{
    freeze = 1;
}

bool BossBoulet::collidesWithEnemy()
{
    return 0;
}

void BossBoulet::updatePixmapBoulet()
{
    if(boulet == Boulet::Frame_1)
    {
        setPixmap(QPixmap(":/images/BossAttack/Boulet-1.png"));
        boulet = Boulet::Frame_2;
    }else if(boulet == Boulet::Frame_2){
        setPixmap(QPixmap(":/images/BossAttack/Boulet-2.png"));
        boulet = Boulet::Frame_3;
    }else if(boulet == Boulet::Frame_3){
        setPixmap(QPixmap(":/images/BossAttack/Boulet-3.png"));
        boulet = Boulet::Frame_4;
    }else if(boulet == Boulet::Frame_4){
        setPixmap(QPixmap(":/images/BossAttack/Boulet-4.png"));
        boulet = Boulet::Frame_5;
    }else if(boulet == Boulet::Frame_5){
        setPixmap(QPixmap(":/images/BossAttack/Boulet-5.png"));
        boulet = Boulet::Frame_6;
    }else if(boulet == Boulet::Frame_6){
        setPixmap(QPixmap(":/images/BossAttack/Boulet-6.png"));
        boulet = Boulet::Frame_7;
    }else if(boulet == Boulet::Frame_7){
        setPixmap(QPixmap(":/images/BossAttack/Boulet-7.png"));
        boulet = Boulet::Frame_8;
    }else if(boulet == Boulet::Frame_8){
        setPixmap(QPixmap(":/images/BossAttack/Boulet-8.png"));
        boulet = Boulet::Frame_1;
    }
}

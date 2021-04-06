#include "BossAttack.h"

BossAttack::BossAttack(qreal BossPosY, qreal limiteScreen) : fireball(Frame1)
{

    freeze = 0;

    // determiner la limite de l'écran pour être en mesure de détecter quand la boule sort du jeu
    rightLimiteScreen = limiteScreen;

    // set position
    setPos(QPoint(275,BossPosY));

        //animation de la boule de feu
        animationFireball = new QTimer();
        connect(animationFireball, &QTimer::timeout, [=](){
            updatePixmapFireball();
        });
        animationFireball->start(100);

    // connect to signal
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    // set timer
    timer->start(30); //every 30 ms the fireball will move
}

BossAttack::~BossAttack()
{
    delete timer;
    delete animationFireball;
}

void BossAttack::move()
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
        //move
        setPos(x()-VITESSE_BOULE,y());
    }

    // delete if off the screan
    if (pos().x() + 20 > rightLimiteScreen)
    {
      //  delete this;
    }
}

void BossAttack::freezeInPlace()
{
    freeze = 1;
}

bool BossAttack::collidesWithEnemy()
{
    return 0;
}

void BossAttack::updatePixmapFireball()
{
    if(fireball == Fireball::Frame1)
    {
        setPixmap(QPixmap(":/images/BossAttack/Frame-1.png"));
        fireball = Fireball::Frame2;
    }else if(fireball == Fireball::Frame2){
        setPixmap(QPixmap(":/images/BossAttack/Frame-2.png"));
        fireball = Fireball::Frame3;
    }else if(fireball == Fireball::Frame3){
        setPixmap(QPixmap(":/images/BossAttack/Frame-3.png"));
        fireball = Fireball::Frame4;
    }else if(fireball == Fireball::Frame4){
        setPixmap(QPixmap(":/images/BossAttack/Frame-4.png"));
        fireball = Fireball::Frame5;
    }else if(fireball == Fireball::Frame5){
        setPixmap(QPixmap(":/images/BossAttack/Frame-5.png"));
        fireball = Fireball::Frame6;
    }else if(fireball == Fireball::Frame6){
        setPixmap(QPixmap(":/images/BossAttack/Frame-6.png"));
        fireball = Fireball::Frame1;
    }
}

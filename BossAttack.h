#ifndef BOSSATTACK_H
#define BOSSATTACK_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QGraphicsItemGroup>
#include <QPropertyAnimation>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include <QList>
#include <QDebug>
#include <QPixmap>


#include "birditem.h"
#include "Boss.h"

class BossAttack : public QObject, public QGraphicsPixmapItem
{
private:
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX )

    // variables
    const qreal VITESSE_BOULE = 5;    //valeur à ajuster
    //qreal yPos;
    //qreal xPos;
    qreal rightLimiteScreen;
    QTimer * timer;
    bool freeze;
    //QGraphicsPixmapItem * feu;
    //QPropertyAnimation * xAnimation;
    //QMediaPlayer * feuMedia;

    //animation boule de feu
    enum Fireball{
        Frame1,
        Frame2,
        Frame3,
        Frame4,
        Frame5,
        Frame6,
    };


    Fireball fireball;
    QTimer * animationFireball;

    void updatePixmapFireball();

public slots:
    void move();

signals:
    void collideFail(); // fonction qui n'est pas défini elle est émise

public:
    // constructeur
    explicit BossAttack(qreal bossPosY, qreal limiteScreen);

    // destructeur
    ~BossAttack();

    void freezeInPlace();
    bool collidesWithEnemy();
};
#endif // BOSSATTACK_H

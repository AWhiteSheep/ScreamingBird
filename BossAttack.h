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

    enum Boulet{
        Frame_1,
        Frame_2,
        Frame_3,
        Frame_4,
        Frame_5,
        Frame_6,
        Frame_7,
        Frame_8
    };

    Fireball fireball;
    Boulet boulet;
    QTimer * animationFireball;
    QTimer * animationBoulet;

    void updatePixmapFireball();
    void updatePixmapBoulet();

public slots:
    void move();

signals:
    void collideFail(); // fonction qui n'est pas défini elle est émise

public:
    // constructeur
    explicit BossAttack(qreal bossPosY, qreal limiteScreen, bool attack);

    // destructeur
    ~BossAttack();

    // fonctions
    //qreal getX();
    //qreal getY();
    //void setX(qreal x);
    //void setY(qreal x);
    void freezeInPlace();
    bool collidesWithEnemy();
};
#endif // BOSSATTACK_H

#ifndef BIRDATTACK_H
#define BIRDATTACK_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QGraphicsItemGroup>
#include <QPropertyAnimation>
#include <QGraphicsScene>
#include "birditem.h"
#include <QDebug>
#include "freezable.h"

class BirdAttack : public QObject, public QGraphicsPixmapItem, public Freezable
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

    int updatePixmap();
public slots:
    void move();

public:
    // constructeur
    explicit BirdAttack(qreal birdPosY, qreal limiteScreen);

    // destructeur
    ~BirdAttack();

    // fonctions
    //qreal getX();
    //qreal getY();
    //void setX(qreal x);
    //void setY(qreal x);

    // ABSTRACT IMPLEMENTATION
    void freezeInPlace();
    bool collidesWithEnemy();
};

#endif // BIRDATTACK_H

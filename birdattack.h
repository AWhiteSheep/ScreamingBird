/*
*  
*   Author: jara2502, pera3307, rouy2404, veic1101 
*   Date: 2021-04-13 (mar., 13 avril. 2021) 
*   Description: Attaque de l'oiseau instanciée par la scene
* 
*/
#ifndef BIRDATTACK_H
#define BIRDATTACK_H

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
#include "freezable.h"
#include "birditem.h"
#include "enemy.h"

class BirdAttack : public QObject, public QGraphicsPixmapItem, public Freezable
{
private:
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX )

    // variables
    const qreal VITESSE_BOULE = 5;    //valeur à ajuster
    qreal rightLimiteScreen;
    QTimer * timer;
    bool freeze;

    // animation boule de feu
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
signals:
    void enemyKilled();
public:
    // constructeur
    explicit BirdAttack(qreal birdPosY, qreal limiteScreen);

    // destructeur
    ~BirdAttack();

    // fonctions
    void freezeInPlace();
    bool collidesWithEnemy();
};

#endif // BIRDATTACK_H

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

class birdattack : public QObject, public QGraphicsRectItem
{
private:
    Q_OBJECT
    //Q_PROPERTY(qreal x READ x WRITE setX )

    // variables
    const qreal VITESSE_BOULE = 90;    //valeur à ajuster
    qreal yPos;
    qreal xPos;


    //QGraphicsPixmapItem * feu;
    //QPropertyAnimation * xAnimation;
    //QMediaPlayer * feuMedia;

public:
    // constructeur
    birdattack();

    // destructeur
    //~birdattack();

    // fonctions
    qreal getX();
    void setX(qreal x);
    void freezeInPlace();
    bool collidesWithEnemy();
};

#endif // BIRDATTACK_H

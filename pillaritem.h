/*
*
*   Author: jara2502, pera3307, rouy2404, veic1101
*   Date: 2021-04-13 (mar., 13 avril. 2021)
*   Description: Classe qui est instancié chaque x milliseconde par la scene pour créer les obstracles que le joueur doit contourner.
*
*/
#ifndef PILLARITEM_H
#define PILLARITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QDebug>
#include <QMediaPlayer>
#include "freezable.h"
#include "birditem.h"

// nous utilison QGraphicsItemGroup afin de manipuler un group d'entité comme un seul
class PillarItem : public QObject, public QGraphicsItemGroup, public Freezable
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX ) // QProperty est essentiel afin d'utiliser les animation QT sur un objet.
public:
    explicit PillarItem();
    ~PillarItem();

    qreal x() const;
    void freezeInPlace();

signals:
    void collideFail(); // fonction qui n'est pas défini elle est émise
public slots:

    void setX(qreal x);
private:
    bool collidesWithBird();
    QGraphicsPixmapItem * topPillar;
    QGraphicsPixmapItem * bottomPillar;
    QPropertyAnimation * xAnimation;
    QMediaPlayer * pillarMedia;
    int yPos;
    qreal m_x;
    bool pastBird;

};

#endif // PILLARITEM_H

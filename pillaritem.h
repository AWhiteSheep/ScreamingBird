#ifndef PILLARITEM_H
#define PILLARITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QDebug>
#include <QMediaPlayer>

#include "birditem.h"

// nous utilison QGraphicsItemGroup afin de manipuler un group d'entité comme un seul
class PillarItem : public QObject, public QGraphicsItemGroup
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

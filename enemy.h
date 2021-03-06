#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QGraphicsPixmapItem>

#include "birditem.h"
#include "scene.h"

class enemy:public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX ) // QProperty est essentiel afin d'utiliser les animation QT sur un objet.
public:
    explicit enemy();
    ~enemy();

    void freezeInPlace();
    qreal x() const;
public slots:
    void setX(qreal x);
signals:
    void collideFail(); // fonction qui n'est pas défini elle est émise

private:
    bool collidesWithBird();
    QGraphicsPixmapItem * Enemy;
    QPropertyAnimation * xAnimation;
    QPropertyAnimation * yAnimation;

   int yPos;
   int xPos;
   qreal m_x;
   bool pastBird;
};

#endif // ENEMY_H

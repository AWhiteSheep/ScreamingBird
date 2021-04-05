#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItemGroup>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QRandomGenerator>

#include "birditem.h"


class enemy:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX) // QProperty est essentiel afin d'utiliser les animation QT sur un objet.
    Q_PROPERTY(qreal y READ y WRITE setY)
    qreal ENEMY_SPEED = 1200;      // 1000 - 3000
public:
    explicit enemy();
    ~enemy();

    void freezeInPlace();
    qreal x() const;
    qreal y() const;

public slots:
    void setX(qreal x);
    void setY(qreal y);
signals:
    void collideFail(); // fonction qui n'est pas défini elle est émise

private:
    enum WingPosition{
        Frame1,
        Frame2,
        Frame3,
        Frame4,
        Frame5,
        Frame6,
        Frame7,
        Frame8
    };

    int updatePixmap();
    bool collidesWithBird();

    WingPosition  wingPosition;
    QGraphicsPixmapItem * Enemy;
    QPropertyAnimation * xAnimation;
    QPropertyAnimation * yAnimation;
    QTimer * yAnimationTimer;
    QTimer * EnemyWingsTimer;

   int xPos;
   int yPos;
   qreal m_x;
   qreal m_y;
   bool isGoingUp = false;
   bool pastBird;
};

#endif // ENEMY_H

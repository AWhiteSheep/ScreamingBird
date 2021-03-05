#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include "birditem.h"
#include "pillaritem.h"
#include <QGraphicsRectItem>
class enemy:public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    qreal y();
    qreal x();

     enemy();
    ~enemy();

    void move();
};

#endif // ENEMY_H

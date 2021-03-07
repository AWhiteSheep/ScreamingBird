#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItemGroup>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>


#include "birditem.h"
#include "scene.h"

class enemy:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX ) // QProperty est essentiel afin d'utiliser les animation QT sur un objet.
public:
    explicit enemy();
    ~enemy();

    void freezeInPlace();
    qreal x() const;
    int yPos;
public slots:
    void setX(qreal x);
signals:
    void collideFail(); // fonction qui n'est pas défini elle est émise

private:
    enum WingPosition{
        upMouthClose,
        downMouthClose,
        upMouthOpen,
        downMouthOpen
    };
    WingPosition  wingPosition;
    int updatePixmap();
    bool collidesWithBird();
    QGraphicsPixmapItem * Enemy;
    QPropertyAnimation * xAnimation;
    QPropertyAnimation * yAnimation;

    QTimer * EnemyWingsTimer;

   int xPos;
   int WingDirection;
   qreal m_x;
   bool pastBird;
};

#endif // ENEMY_H

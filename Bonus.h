#ifndef BONUS_H
#define BONUS_H

#include <QGraphicsItemGroup>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QRandomGenerator>

#include "birditem.h"

class Bonus:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX) // QProperty est essentiel afin d'utiliser les animation QT sur un objet.

public:
    explicit Bonus();
    ~Bonus();

    void bonusEffect();
    void freezeInPlace();
    qreal x() const;


public slots:
    void setX(qreal x);

signals:
    void collideFail(); // fonction qui n'est pas défini elle est émise

private:

    void updatePixmap();
    bool collidesWithBird();

    QGraphicsPixmapItem * bonus;
    QPropertyAnimation * xAnimation;
    QTimer * xAnimationTimer;

   int xPos;
   qreal m_x;
   qreal m_y;
};

#endif // BONUS_H
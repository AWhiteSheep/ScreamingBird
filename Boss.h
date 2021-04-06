#ifndef BOSS_H
#define BOSS_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QRandomGenerator>
#include <QPropertyAnimation>
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

#include "birdattack.h"

class Boss:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX) // QProperty est essentiel afin d'utiliser les animation QT sur un objet.
    Q_PROPERTY(qreal y READ y WRITE setY)
    qreal BOSS_SPEED = 1200;      // 1000 - 3000
public:
    explicit Boss();
    ~Boss();

    void freezeInPlace();
    void lifeDown();
    int getLife();
    qreal x() const;
    qreal y() const;

public slots:
    void setX(qreal x);
    void setY(qreal y);
signals:
    void Bossdead();
    void BeginAttack();

private:
    enum deathFrame{
        Frame1,
        Frame2,
        Frame3,
        Frame4,
        Frame5,
        Frame6,
    };
    deathFrame DeathFrame;

    int updatePixmap();
    bool deathPixmap();
    bool collidesWithBirdAttack();

    void BossDeath();
    void rotateTo(const qreal &end, const int& duration, const QEasingCurve& curve);

    QGraphicsPixmapItem * boss;
    QPropertyAnimation * xAnimation;
    QPropertyAnimation * yAnimation;
    QPropertyAnimation * rotationAnimation;
    QTimer * yAnimationTimer;
    QTimer * deathTimer;

   int xPos;
   int yPos;
   int lifeCount;
   qreal m_x;
   qreal m_y;
   qreal groundPosition;
   bool isGoingUp = false;
   bool deathAnimation;
   bool bossAlive;
};
#endif // BOSS_H

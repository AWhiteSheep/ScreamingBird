#ifndef BIRDITEM_H
#define BIRDITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimer>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include "birdattack.h"

enum BirdColor
{
    RED,
    BLUE,
    YELLOW
};

class BirdAttack; // let the compiler know such a class will be defined

class BirdItem : public QObject, public QGraphicsPixmapItem
{    
    const qreal JUMP_HEIGHT = 80;       // 30 - 120
    const qreal JUMP_DURATION = 285;    // 200 - 300
    const qreal FALL_SPEED = 1700;      // 800 - 2000
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    BirdAttack *flamme;

    void pause();
    void start();
    explicit BirdItem(QPixmap pixmap);
    ~BirdItem();
    qreal rotation() const;
    qreal y() const;

    void shootUp();
    void attack();
    void startFlying();

    void freezeInPlace();
    BirdColor color;
signals:
public slots:
    void setRotation(qreal rotation);

    void setY(qreal y);

    void rotateTo(const qreal &end, const int& duration, const QEasingCurve& curve);
    void fallToGroundIfNecessary();
private:
    enum WingPosition{
        Up,
        Middle,
        Down
    };
    void updatePixmap();
    WingPosition  wingPosition;
    bool wingDirection; // 0 : down, 1 : wing up
    qreal m_rotation;
    qreal m_y;
    QPropertyAnimation * yAnimation;
    QPropertyAnimation * rotationAnimation;
    QMediaPlayer * birdMedia;
    qreal groundPosition;
};

#endif // BIRDITEM_H

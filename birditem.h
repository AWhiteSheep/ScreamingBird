/*
*
*   Author: jara2502, pera3307, rouy2404, veic1101
*   Date: 2021-04-13 (mar., 13 avril. 2021)
*   Description: Classe de l'oiseau (personnage du joueur)
*
*/
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

class BirdItem : public QObject, public QGraphicsPixmapItem
{    
    const qreal JUMP_HEIGHT = 60;       // 30 - 120
    const qreal JUMP_DURATION = 285;    // 200 - 300
    const qreal FALL_SPEED = 1700;      // 800 - 2000
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    void pause();
    void start();
    explicit BirdItem(QPixmap pixmap, qreal sky, qreal ground);
    ~BirdItem();
    qreal rotation() const;
    qreal y() const;

    void shootUp();
    void shootDown();
    void die();
    void freezeInPlace();
    void setPowerUp(bool bonus);
    BirdColor color;
signals:
public slots:
    void setRotation(qreal rotation);

    void setY(qreal y);

    void rotateTo(const qreal &end, const int& duration, const QEasingCurve& curve);
private:
    enum WingPosition{
        Up,
        Middle,
        Down
    };
    void updatePixmap();
    WingPosition  wingPosition;
    bool wingDirection; // 0 : down, 1 : wing up
    bool PowerUp;
    qreal m_rotation;
    qreal m_y;
    QPropertyAnimation * yAnimation;
    QPropertyAnimation * rotationAnimation;
    QMediaPlayer * birdMedia;
    QTimer * birdWingsTimer;
    qreal groundPosition;
    qreal skyPosition;
};

#endif // BIRDITEM_H

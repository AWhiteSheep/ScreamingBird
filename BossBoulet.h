#ifndef BOSSBOULET_H
#define BOSSBOULET_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QGraphicsItemGroup>
#include <QPropertyAnimation>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include <QList>
#include <QDebug>
#include <QPixmap>


#include "birditem.h"
#include "Boss.h"

class BossBoulet : public QObject, public QGraphicsPixmapItem
{
private:
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX )

    // variables
    const qreal VITESSE_BOULET = 3;    //valeur à ajuster
    //qreal yPos;
    //qreal xPos;
    qreal rightLimiteScreen;
    QTimer * timer;
    bool freeze;
    //QGraphicsPixmapItem * feu;
    //QPropertyAnimation * xAnimation;
    //QMediaPlayer * feuMedia;

    enum Boulet{
        Frame_1,
        Frame_2,
        Frame_3,
        Frame_4,
        Frame_5,
        Frame_6,
        Frame_7,
        Frame_8
    };

    Boulet boulet;
    QTimer * animationBoulet;

    void updatePixmapBoulet();

public slots:
    void move();

signals:
    void collideFail(); // fonction qui n'est pas défini elle est émise

public:
    // constructeur
    explicit BossBoulet(qreal bossPosY, qreal limiteScreen);

    // destructeur
    ~BossBoulet();

    void freezeInPlace();
    bool collidesWithEnemy();
};
#endif // BOSSBOULET_H

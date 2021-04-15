/*
*
*   Author: jara2502, pera3307, rouy2404, veic1101
*   Date: 2021-04-13 (mar., 13 avril. 2021)
*   Description: Classe pour l'attaque du boss lui aussi instancié par la scene qui une fois touche le joueur le met hors combat.
*
*/
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
#include "freezable.h"
#include "birditem.h"
#include "Boss.h"

class BossBoulet : public QObject, public QGraphicsPixmapItem, public Freezable
{
public:
    enum Direction {
        Up,
        Middle,
        Down
    };
private:
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX )
    Q_PROPERTY(qreal y READ y WRITE setY )

    // variables
    const qreal VITESSE_BOULET = 3;    //valeur à ajuster
    //qreal yPos;
    //qreal xPos;
    qreal rightLimiteScreen;
    QTimer * timer;
    bool freeze;
    //QGraphicsPixmapItem * feu;
    //QPropertyAnimation * xAnimation;d
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

    Direction attackDirection;

    Boulet boulet;
    QTimer * animationBoulet;

    void updatePixmapBoulet();

public slots:
    void move();

signals:
    void collideFail(); // fonction qui n'est pas défini elle est émise

public:
    // constructeur
    explicit BossBoulet(qreal bossPosY, qreal limiteScreen, Direction direction = Direction::Middle);

    // destructeur
    ~BossBoulet();

    void freezeInPlace();
    bool collidesWithEnemy();
};
#endif // BOSSBOULET_H

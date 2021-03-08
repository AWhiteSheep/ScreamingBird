#include "pillaritem.h"
#include "scene.h"

PillarItem::PillarItem():
    topPillar(new QGraphicsPixmapItem(QPixmap(":/images/pipe-green-top.png"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/images/pipe-green.png"))),
    pastBird(false)
{
    topPillar->setPos(QPointF(0,0) - QPointF(topPillar->boundingRect().width()/2,
                                             topPillar->boundingRect().height() + 60));

    bottomPillar->setPos(QPointF(0,0) + QPointF(-bottomPillar->boundingRect().width()/2,
                                                60));

    addToGroup(topPillar);
    addToGroup(bottomPillar);

    // rend l'initilisation random
    yPos = QRandomGenerator::global()->bounded(150);
    setPos(QPoint(0,0) + QPoint(260, yPos));

    // création de l'animation de droite à gauche
    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(600);
    xAnimation->setEndValue(-600);
    xAnimation->setEasingCurve(QEasingCurve::Linear); // la function utiliser pour atteindre la position final
    xAnimation->setDuration(3500);
    connect(xAnimation, &QPropertyAnimation::finished, [=](){
        scene()->removeItem(this);
        delete this;
    });
    xAnimation->start();

    // set le son pour l'incrémentation de score
    pillarMedia = new QMediaPlayer();
}

PillarItem::~PillarItem()
{
    delete topPillar;
    delete bottomPillar;
    delete xAnimation;
    delete pillarMedia;
    delete pillarMedia;
}

qreal PillarItem::x() const
{
    return m_x;
}

void PillarItem::freezeInPlace()
{
    xAnimation->stop();
}

void PillarItem::setX(qreal x)
{
    m_x = x;

    if(x < 0 && !pastBird) {
        pastBird = true;
        QGraphicsScene * mScene = scene();
        Scene *myScene = dynamic_cast<Scene*>(mScene);
        if(myScene)
        {
            myScene->incrementScore();
            int pillar = myScene->getScore();
             qDebug() << "pillar : "<< pillar;
            // jouer le son pour l'incrémentation du score
            pillarMedia->setMedia(QUrl("qrc:/sound effects/smb_coin.wav"));
            pillarMedia->play();
        }
    }

    if(collidesWithBird())
    {
        emit collideFail();
    }
    setPos(QPointF(0,0) + QPointF(x,yPos));

}

bool PillarItem::collidesWithBird()
{
    // list des items qui touche l'objet
    QList<QGraphicsItem*> collidingItems = topPillar->collidingItems();
    collidingItems.append(bottomPillar->collidingItems());

    foreach(QGraphicsItem * item, collidingItems)
    {
        BirdItem * birdItem = dynamic_cast<BirdItem*>(item);
        if(birdItem)
            return true;
    }
    return false;
}


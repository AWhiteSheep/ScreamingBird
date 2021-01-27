#include "pillaritem.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QDebug>

PillarItem::PillarItem():
    topPillar(new QGraphicsPixmapItem(QPixmap(":/images/pipe-green.png"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/images/pipe-green.png")))
{
    topPillar->setPos(QPointF(0,0) - QPointF(topPillar->boundingRect().width()/2,
                                             topPillar->boundingRect().height() + 60));

    bottomPillar->setPos(QPointF(0,0) + QPointF(-bottomPillar->boundingRect().width()/2,
                                                60));
    addToGroup(topPillar);
    addToGroup(bottomPillar);
    // rend l'initilisation random
    yPos = QRandomGenerator::global()->bounded(150);
    int xRandomizer = QRandomGenerator::global()->bounded(200);
    setPos(QPoint(0,0) + QPoint(260 + xRandomizer, yPos));

    // création de l'animation de droite à gauche
    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(260 + xRandomizer);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear); // la function utiliser pour atteindre la position final
    xAnimation->setDuration(1500);
    connect(xAnimation, &QPropertyAnimation::finished, [=](){
        qDebug() << "Animation finished";
        scene()->removeItem(this);
        delete this;
    });
    xAnimation->start();

}

PillarItem::~PillarItem()
{
    qDebug() << "Deleting Pillar";
}

qreal PillarItem::x() const
{
    return m_x;
}

void PillarItem::setX(qreal x)
{
    qDebug() << "Pillar position: " << x;
    m_x = x;
    setPos(QPointF(0,0) + QPointF(x,yPos));
}

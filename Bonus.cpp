#include "Bonus.h"
#include "scene.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

Bonus::Bonus()
{
    //set l'ennemi dans l'espace
    m_y = QRandomGenerator::global()->bounded(150);
    setPos(QPoint(0,0) + QPoint(260, m_y));

    updatePixmap();

    //Commence l'animation d'avancement
    // création de l'animation de droite à gauche
    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(600);
    xAnimation->setEndValue(-600);
    xAnimation->setEasingCurve(QEasingCurve::Linear); // la function utiliser pour atteindre la position final
    xAnimation->setDuration(3500);
    connect(xAnimation, &QPropertyAnimation::finished, [=](){
        if (scene() != NULL) 
        {
            QList<QGraphicsItem*> sceneItems = scene()->items();
            foreach(QGraphicsItem * item, sceneItems) {
                if (item == this) {
                    scene()->removeItem(this);
                    delete this;
                }
            }
        }
    });
    xAnimation->start();

};

Bonus::~Bonus()
{
    delete xAnimation;
};

void Bonus::removeAnimation() 
{
}

qreal Bonus::x() const
{
    return m_x;
};

void Bonus::freezeInPlace()
{
    xAnimation->stop();
};

void Bonus::setX(qreal x)
{
    m_x = x;
    setPos(QPointF(0,0) + QPointF(x,m_y));
    if(collidesWithBird())
    {
        emit collideFail();
    }
};

bool Bonus::collidesWithBird()
{
    // list des items qui touche l'objet
    QList<QGraphicsItem*> collidingItems = this->collidingItems();

   foreach(QGraphicsItem * item, collidingItems)
    {
        BirdItem * birdItem = dynamic_cast<BirdItem*>(item);
        if(birdItem)
            return true;
    }
    return false;
};

void Bonus::updatePixmap()
{
    setPixmap(QPixmap(":/images/Bonus.png"));
}

#include "button.h"

Button::Button(QPixmap pixmap_idle, QPixmap pixmap_press)
    :pixmap_idle(pixmap_idle), pixmap_press(pixmap_press)
{
    setPixmap(pixmap_idle);
}

Button::~Button()
{
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    setPixmap(pixmap_press);
    // placement au centre de l'écran
    setPos(QPointF(0,0) - QPointF(boundingRect().width()/2,
                                               boundingRect().height()/2));
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{

}

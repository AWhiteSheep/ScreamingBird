#include "button.h"

Button::Button(QPixmap pixmap_idle, QPixmap pixmap_press)
    :pixmap_idle(pixmap_idle), pixmap_press(pixmap_press)
{
    setPixmap(pixmap_idle);
}

Button::~Button()
{
}

void Button::setIdlePixmap(QPixmap pixmap_idle)
{
    this->pixmap_idle = pixmap_idle;
    setPixmap(pixmap_idle);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    setPixmap(pixmap_press);
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    setPixmap(pixmap_idle);
    emit mouseRelease();
}

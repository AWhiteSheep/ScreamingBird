#ifndef BUTTON_H
#define BUTTON_H


#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimer>
#include <QGraphicsScene>
#include <QMediaPlayer>

class Button : public QObject, public QGraphicsPixmapItem
{
public:
    Button(QPixmap pixmap_idle, QPixmap pixmap_press);
    ~Button();
//    void buttonRelease();
//    void buttonPress();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    QPixmap pixmap_idle;
    QPixmap pixmap_press;
};

#endif // BUTTON_H

/*
*
*   Author: jara2502, pera3307, rouy2404, veic1101
*   Date: 2021-04-13 (mar., 13 avril. 2021)
*   Description: Classe de base pour les boutons graphiques du jeu, qui override le mouse press et le mouse release event.
*
*/
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
    Q_OBJECT
public:
    Button(QPixmap pixmap_idle, QPixmap pixmap_press);
    ~Button();
    void setIdlePixmap(QPixmap pixmap_idle);
    void setToIdle();
    void setToPress();
    bool selected = false;
signals:
    void mouseRelease();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    QPixmap pixmap_idle;
    QPixmap pixmap_press;
};

#endif // BUTTON_H

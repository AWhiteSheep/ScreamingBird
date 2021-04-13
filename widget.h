/*
*
*   Author: jara2502, pera3307, rouy2404, veic1101
*   Date: 2021-04-13 (mar., 13 avril. 2021)
*   Description: Classe qui instancie la scene et qui est conteneur de notre application.
*
*/
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <scene.h>
#include <QMediaPlayer>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QMainWindow>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget*parent = nullptr);
    ~Widget();
    void setFocusToGraphicView();
private slots:

private:
    Scene * scene;
    QVBoxLayout* verticalLayout;
    QGraphicsView* graphicsView;
};
#endif // WIDGET_H

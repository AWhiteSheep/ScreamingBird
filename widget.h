#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <scene.h>
#include <QMediaPlayer>
#include <QVBoxLayout>
#include <QGraphicsView>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void setFocusToGraphicView();
private slots:

private:
    Widget* ui;
    Scene * scene;
    QVBoxLayout* verticalLayout;
    QGraphicsView* graphicsView;
};
#endif // WIDGET_H

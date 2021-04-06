#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <scene.h>
#include <QMediaPlayer>
#include <QVBoxLayout>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void setFocusToGraphicView();
private slots:
    void on_startGameButton_clicked();

private:
    Widget *ui;
    Scene * scene; 
    QVBoxLayout* verticalLayout;
    QGraphicsView* graphicsView;
};
#endif // WIDGET_H

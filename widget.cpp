#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>
#include <pillaritem.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // initialisation de la scene et configuration de ce qui sera affiché
    // dans une vue graphique
    scene = new Scene(this); // besoin d'une référence au parent
    //scene->setSceneRect(-250,-300,500,600);

    // recheche de la ressource de l'arrière plan
    QPixmap background(":/images/background-day.png");
    QGraphicsPixmapItem * pixItem =
            new QGraphicsPixmapItem(background);
    pixItem->setPos(QPointF(0,0) - QPointF(pixItem->boundingRect().width()/2,
                                           pixItem->boundingRect().height()/2));

    scene->addItem(pixItem);

    // centrer l'arrière plan

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->graphicsView->setSceneRect(scene->sceneRect());
    scene->addBird();
    scene->startMusic();
    scene->addMenu();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_startGameButton_clicked()
{
    scene->startGame();
}

void Widget::setFocusToGraphicView()
{
    ui->graphicsView->setFocus();
}

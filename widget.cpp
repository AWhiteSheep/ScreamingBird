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
    scene->sceneBackgroundMap =
            new QGraphicsPixmapItem(background);
    QGraphicsPixmapItem * pixItem = scene->sceneBackgroundMap;
    scene->sceneBackgroundMap->setPos(QPointF(0,0) - QPointF(pixItem->boundingRect().width()/2,
                                           pixItem->boundingRect().height()/2));

    scene->addItem(pixItem);
    // ajout de score board
    QGraphicsPixmapItem* score = new QGraphicsPixmapItem(QPixmap(":/images/scores/score-background-200.png"));
    score->setPos(QPointF(pixItem->boundingRect().width()/2, -pixItem->boundingRect().height()/2)
                  -QPointF(score->boundingRect().width(),0)
                  +QPointF(-10,10));
    score->setZValue(1);
    scene->addItem(score);
    scene->addSceneScore();
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

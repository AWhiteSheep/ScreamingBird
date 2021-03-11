#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>
#include <pillaritem.h>
#include "enemy.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // initialisation de la scene et configuration de ce qui sera affiché
    // dans une vue graphique
    scene = new Scene(this); // besoin d'une référence au parent
    // recheche de la ressource de l'arrière plan
    QPixmap background(":/images/background-day.png");
    scene->sceneBackgroundMap =
            new QGraphicsPixmapItem(background);
    QGraphicsPixmapItem * pixItem = scene->sceneBackgroundMap;
    scene->sceneBackgroundMap->setPos(QPointF(0,0) - QPointF(pixItem->boundingRect().width()/2,
                                           pixItem->boundingRect().height()/2));
    scene->addItem(pixItem);
    // ajout du score
    QGraphicsPixmapItem* score = new QGraphicsPixmapItem(QPixmap(":/images/scores/score-background-200.png"));
    score->setPos(QPointF(pixItem->boundingRect().width()/2, -pixItem->boundingRect().height()/2)
                  -QPointF(score->boundingRect().width(),0)
                  +QPointF(-10,10));
    score->setZValue(1);
    scene->addItem(score);
    scene->addSceneScore();
    // ajout du high score
    QGraphicsPixmapItem* highScore = new QGraphicsPixmapItem(QPixmap(":/images/scores/high-score-200.png"));
    highScore->setPos(-QPointF(pixItem->boundingRect().width()/2, pixItem->boundingRect().height()/2)
                  +QPointF(10,10));
    highScore->setZValue(1);
    scene->addItem(highScore);
    scene->addSceneHighScore();
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

#include "widget.h"
#include <QGraphicsPixmapItem>
#include <pillaritem.h>
#include "enemy.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // SETUP UI
    verticalLayout = new QVBoxLayout;
    graphicsView = new QGraphicsView;
    this->resize(1177, this->width());
    this->resize(637, this->height());
    this->setWindowTitle("Screaming Bird");
    this->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
    verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
    graphicsView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);
    graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);
    graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    verticalLayout->addWidget(graphicsView);
    this->setLayout(verticalLayout);

    // INITIALIZE SCENE
    scene = new Scene(this); // besoin d'une référence au parent

    // ADD BACKGROUND TO SCENE
    QPixmap background(":/images/background-day.png");
    scene->sceneBackgroundMap = new QGraphicsPixmapItem(background);
    QGraphicsPixmapItem * pixItem = scene->sceneBackgroundMap;
    scene->sceneBackgroundMap->setPos(QPointF(0,0) - QPointF(pixItem->boundingRect().width()/2,
                                           pixItem->boundingRect().height()/2));
    scene->addItem(pixItem);

    // ADD SCORE GRAPHICS SLOT
    QGraphicsPixmapItem* score = new QGraphicsPixmapItem(QPixmap(":/images/scores/score-background-200.png"));
    score->setPos(QPointF(pixItem->boundingRect().width()/2, -pixItem->boundingRect().height()/2)
                  -QPointF(score->boundingRect().width(),0)
                  +QPointF(-10,10));
    score->setZValue(1);
    scene->addItem(score);
    scene->addSceneScore();

    // ADD HIGHSCORE GRAPHICS SLOT
    QGraphicsPixmapItem* highScore = new QGraphicsPixmapItem(QPixmap(":/images/scores/high-score-200.png"));
    highScore->setPos(-QPointF(pixItem->boundingRect().width()/2, pixItem->boundingRect().height()/2)
                  +QPointF(10,10));
    highScore->setZValue(1);
    scene->addItem(highScore);
    scene->addSceneHighScore();
    
    // SET SCENE
    graphicsView->setScene(scene);
    graphicsView->setSceneRect(scene->sceneRect());

    // SET APP BEGIN
    scene->addBird();
    scene->startMusic();
    scene->addMenu();
}

Widget::~Widget()
{
    delete scene;
    delete graphicsView;
    delete verticalLayout;
}

void Widget::setFocusToGraphicView()
{
   graphicsView->setFocus();
}

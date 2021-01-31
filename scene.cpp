#include "scene.h"
#include "birditem.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    setUpPillarTimer();
}

void Scene::addBird()
{
    // initialisation the bird et ajout à la scene
    bird = new BirdItem(QPixmap(":/images/redbird-upflap.png"));
    addItem(bird);// fonction de QGraphicsScene
}

void Scene::startGame()
{
    //start animation for Bird and Pillars
    bird->startFlying();
    // ajoute un item Pillar à chaque 1000
    if(!pillarTimer->isActive())
    {
        pillarTimer->start(1000);
    }
}

void Scene::setUpPillarTimer()
{
    pillarTimer = new QTimer(this);
    // quand le timer à terminé ajoute un Pillar
    connect(pillarTimer, &QTimer::timeout, [=](){
        PillarItem * pillarItem = new PillarItem();
        addItem(pillarItem);
    });
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    // vérifier le le boutton presser else if(event->key() == Qt::Key_Escape)
    if(event->key() == Qt::Key_Escape){
        paused = !paused;
        if(paused)
        {
            bird->pause();
        } else {
            bird->start();
        }
    } else if(event->key() == Qt::Key_Space && !paused){
        bird->shootUp();
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // vérifier le le boutton presser
    if(event->button() == Qt::LeftButton && !paused){
        bird->shootUp();
    }
    QGraphicsScene::mousePressEvent(event);
}

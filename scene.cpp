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

void Scene::setUpPillarTimer()
{
    pillarTimer = new QTimer(this);
    // quand le timer à terminé ajoute un Pillar
    connect(pillarTimer, &QTimer::timeout, [=](){
        PillarItem * pillarItem = new PillarItem();
        addItem(pillarItem);
    });
    // ajoute un item Pillar à chaque 1000
    pillarTimer->start(1000);
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    // vérifier le le boutton presser
    if(event->key() == Qt::Key_Space){
        bird->shootUp();
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // vérifier le le boutton presser
    if(event->button() == Qt::LeftButton){
        bird->shootUp();
    }
    QGraphicsScene::mousePressEvent(event);
}

#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include "pillaritem.h"
#include "birditem.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QMediaPlayer>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    ~Scene();
    void addBird();
    void startGame();
    bool getGameOn() const;
    void setGameOn(bool value);
    void incrementScore();
    void startMusic();
signals:
public slots:
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    void showGameOverGraphics();
    void hideGameOverGraphics();
    void setUpPillarTimer();
    void freezeBirdAndPillarsInPlace();
    void cleanPillars();
    QTimer * pillarTimer;
    BirdItem * bird;
    bool paused = false;
    bool gameOn;
    int score;
    int bestScore;
    QGraphicsPixmapItem * gameOverPix;
    QGraphicsTextItem * scoreTextItem;
    QMediaPlayer * sceneMedia;

    // QGraphicsScene interface
};

#endif // SCENE_H

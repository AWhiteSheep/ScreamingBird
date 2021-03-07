#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include "pillaritem.h"
#include "birditem.h"
#include "enemy.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QMediaPlayer>
#include "button.h"

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
    int getScore();
    void addMenu();
    void addReplayButton();
    void addSceneScore();
    void addSceneHighScore();
    void updateSceneScore();
    void updateSceneHighScore();
    QGraphicsPixmapItem * sceneBackgroundMap;
signals:
public slots:
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    void showGameOverGraphics();
    void hideGameOverGraphics();
    void setUpPillarTimer();
    void setUpEnemy();
    void setUpAttack();
    void setUpEnemyTimer();
    void freezeBirdAndPillarsInPlace();
    void cleanPillars();
    void cleanEnemy();
    QTimer * pillarTimer;
    QTimer * enemyTimer;
    BirdItem * bird;
    Button * btnStart;
    Button * btnNext;
    Button * btnBack;
    Button * btnMusic;
    bool musicOn = true;
    bool paused = false;
    bool gameOn;
    int score;
    int bestScore;
    int birdColor = 0;
    QGraphicsPixmapItem * gameOverPix;
    QGraphicsTextItem * scoreTextItem;
    QGraphicsTextItem * sceneScoreTextItem;
    QGraphicsTextItem * sceneHighScoreTextItem;
    QMediaPlayer * sceneMedia;

    // QGraphicsScene interface
};

#endif // SCENE_H

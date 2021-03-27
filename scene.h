#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include "pillaritem.h"
#include "birditem.h"
#include "enemy.h"
#include "Bonus.h"
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
    void incrementBonus();
    void startMusic();
    int getScore();
    void addMenu();
    void addReplayButton();
    void addSceneScore();
    void addSceneHighScore();
    void addSceneBonus();
    void updateSceneScore();
    void updateSceneHighScore();
    void updateSceneBonus();
    void setMusic(bool x);
    void showTitle();
    void hideTitle();
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
    void setUpBonus();
    void setUpAttack();
    void setUpEnemyTimer();
    void setUpBonusEffectTimer();
    void freezeBirdAndPillarsInPlace();
    void cleanPillars();
    void cleanEnemy();
    void cleanAttack();
    void cleanBonus();
    void BonusEffect();
    QTimer * pillarTimer;
    QTimer * enemyTimer;
    QTimer * bonusTimer;
    QTimer * bonusEffectTimer;
    BirdItem * bird;
    BirdAttack * fireball;
    Button * btnStart;
    Button * btnNext;
    Button * btnBack;
    Button * btnMusic;
    Button * btnMenu;
    bool musicOn = true;
    bool paused = false;
    bool gameOn;
    int score;
    int bestScore;
    int birdColor = 0;
    int bonus;
    QGraphicsPixmapItem * gameOverPix;
    QGraphicsPixmapItem * titlePix;
    QGraphicsTextItem * scoreTextItem;
    QGraphicsTextItem * bonusTextItem;
    QGraphicsTextItem * sceneScoreTextItem;
    QGraphicsTextItem * sceneHighScoreTextItem;
    QGraphicsTextItem * sceneBonusTextItem;
    QMediaPlayer * sceneMedia;
    QMediaPlayer * Bonuseffect;

    // QGraphicsScene interface
};

#endif // SCENE_H

#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QMediaPlayer>
#include "button.h"
#include "pillaritem.h"
#include "birditem.h"
#include "enemy.h"
#include "Bonus.h"
#include "Boss.h"
#include "BossAttack.h"
#include "BossBoulet.h"
#include "CommunicationFPGA.h"
#include "freezable.h"
#include <memory>

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
    void startFPGACommunication();
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
    void setUpBoss();
    void setUpBossAttack();
    void setUpEnemyTimer();
    void setUpBonusEffectTimer();
    void setBossIndex(int Index);
    void freezeBirdAndPillarsInPlace();
    void cleanPillars();
    void cleanEnemy();
    void cleanAttack();
    void cleanBonus();
    void cleanBoss();
    void cleanBossAttack();
    void BonusEffect();
    void updatePixmap();
    QTimer * pillarTimer;
    QTimer * enemyTimer;
    QTimer * bonusTimer;
    QTimer * bonusEffectTimer;
    QTimer * titleTimer;
    QTimer* fpgaTimer;
    QTimer * BossAttackTimer;
    BirdItem * bird;
    BirdAttack * fireball;
    BossAttack * BossBall;
    BossBoulet * Boulet;
    Boss * BossItem;
    Button * btnStart;
    Button * btnNext;
    Button * btnBack;
    Button * btnMusic;
    Button * btnMenu;
    Button* btnTest;
    bool musicOn = true;
    bool paused = false;
    bool gameOn;
    int score;
    int bestScore;
    int birdColor = 0;
    int bonus;
    int titleIndex = 1;
    int bossIndex;
    int attack;
    QGraphicsPixmapItem * gameOverPix;
    QGraphicsPixmapItem * titlePix;
    QGraphicsTextItem * scoreTextItem;
    QGraphicsTextItem * bonusTextItem;
    QGraphicsTextItem * sceneScoreTextItem;
    QGraphicsTextItem * sceneHighScoreTextItem;
    QGraphicsTextItem * sceneBonusTextItem;
    QMediaPlayer * sceneMedia;
    QMediaPlayer * Bonuseffect;

    // Communication FPGA
    CommunicationFPGA* fpga;
    
    // Phonèmes
public:
    enum phonemes {
        A, E, I, O,DEFAULT
    };
    phonemes currentPhoneme = phonemes::DEFAULT;
    int counter = 0;
};

#endif // SCENE_H

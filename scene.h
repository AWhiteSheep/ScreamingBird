/*
*
*   Author: jara2502, pera3307, rouy2404, veic1101
*   Date: 2021-04-13 (mar., 13 avril. 2021)
*   Description: Classe qui instancie et utilise la majorité des classes de l'application (le coeur de l'application)
*
*/
#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QMediaPlayer>
#include <QProgressBar>
#include <QVBoxLayout>
#include <memory>
#include <Vector>
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
#include "user.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
    enum GameState {
        STOPPED, PLAY, IN_CALLIBRATION
    };
    enum phonemes {
        A, E, I, O, DEFAULT
    };
public:
    explicit Scene(QObject* parent = nullptr);
    ~Scene();
    void addBird();
    void startGame();
    void setDifficulty();
    GameState getGameState() const;
    void setGameState(GameState state);
    void incrementScore();
    void incrementBonus();
    void startMusic();
    int getScore();
    void addMenu();
    void addMenuCallibration();
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
    QGraphicsPixmapItem* sceneBackgroundMap;
    QVBoxLayout*layout;
signals:
public slots:
protected:
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
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
    void showMenu();
    void showCallibration();
    void hideAllButton();
    void createBird();
    QTimer* pillarTimer;
    QTimer* enemyTimer;
    QTimer* bonusTimer;
    QTimer* bonusEffectTimer;
    QTimer* titleTimer;
    QTimer* fpgaTimer;
    QTimer* BossAttackTimer;
    BirdItem* bird;
    Boss* BossItem;    
    vector<Button*> menuButtons;
    // phoneme
    vector<Button*> btnPhonemes;
    int phonemesCallibration[4][4];
    int currentPhonemeCallibrationIndex;
    Button* backButtonPhoneme;
    Button* backButtonDifficulty;
    Button* espaceButton;
    Button* btnMenu;
    Button* btnClavier;
    Button* btnPhoneme;
    int currentProgression;
    QProgressBar* progressBarPhonemes;
    
    User user;
    bool musicOn = true;
    bool paused = false;
    bool gameOn;
    int score;
    int bestScore;
    int birdColor = 0;
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
    
public:
    int bonus;
    // Phon�mes
    phonemes currentPhoneme = phonemes::DEFAULT;
    int counter = 0;
    // Game state
    GameState gameState = GameState::STOPPED;
};

#endif // SCENE_H

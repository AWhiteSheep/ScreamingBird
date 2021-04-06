#include "scene.h"
#include "widget.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    gameOn(false), score(0), bestScore(0), bonus(0), bossIndex(0)
{
    gameOverPix = nullptr;
    scoreTextItem = nullptr;
    bonusTextItem = nullptr;
    sceneMedia =  new QMediaPlayer();
    Bonuseffect = new QMediaPlayer();
    setUpPillarTimer();
    setUpEnemyTimer();
    setUpBonus();
    setUpBonusEffectTimer();
}

Scene::~Scene()
{
    delete pillarTimer;
    delete enemyTimer;
    delete titleTimer;
    delete fireball;
    delete titlePix;
    delete gameOverPix;
    delete scoreTextItem;
    delete bonusTextItem;
    delete sceneScoreTextItem;
    delete sceneBonusTextItem;
    delete sceneBackgroundMap;
    delete sceneMedia;
    delete bird;
    QList<QGraphicsItem*> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems){
        Button*button = dynamic_cast<Button*>(item);
        // si c'est bien un pillar appel de la fonction
        if(button){
            delete button;
        }
    }
}

void Scene::startMusic()
{
    if(musicOn) {
        if(sceneMedia->state() == QMediaPlayer::PlayingState)
            sceneMedia->stop();
        sceneMedia->setMedia(QUrl("qrc:/sound effects/super_mario_medley.mp3"));
        sceneMedia->play();
    }
}

void Scene::addBird()
{
    // initialisation the bird et ajout à la scene
    bird = new BirdItem(QPixmap(":/images/redbird-upflap.png"),
                        -sceneBackgroundMap->boundingRect().height()/2,
                        sceneBackgroundMap->boundingRect().height()/2
                        );
    bird->color = static_cast<enum::BirdColor>(0);
    bird->setZValue(1);
    bird->setPos(QPointF(0,0) - QPointF(bird->boundingRect().width()/2,
                                                   bird->boundingRect().height()/2));
    addItem(bird);// fonction de QGraphicsScene
}

void Scene::startGame()
{
    //start animation for Bird and Pillars
    delete bird;
    if(static_cast<enum::BirdColor>(birdColor) == BirdColor::RED)
        bird = new BirdItem(QPixmap(":/images/redbird-midflap.png"),
                            -sceneBackgroundMap->boundingRect().height()/2, sceneBackgroundMap->boundingRect().height()/2);
    else if(static_cast<enum::BirdColor>(birdColor) == BirdColor::BLUE)
        bird = new BirdItem(QPixmap(":/images/birds/bluebird-midflap-200.png"),
                            -sceneBackgroundMap->boundingRect().height()/2, sceneBackgroundMap->boundingRect().height()/2);
    else if(static_cast<enum::BirdColor>(birdColor) == BirdColor::YELLOW)
        bird = new BirdItem(QPixmap(":/images/birds/yellowbird-midflap-200.png"),
                            -sceneBackgroundMap->boundingRect().height()/2, sceneBackgroundMap->boundingRect().height()/2);
    bird->setPos(QPointF(0,0) - QPointF(bird->boundingRect().width()/2,
                                                   bird->boundingRect().height()/2));

    bird->color = static_cast<BirdColor>(this->birdColor);
    addItem(bird);
    bird->setZValue(1);
    score = 0;
    bonus = 0;
    updateSceneScore();
    updateSceneBonus();
    cleanPillars();
    cleanEnemy();
    cleanAttack();
    cleanBonus();
    setGameOn(true);
    hideGameOverGraphics();
    Widget * parent = dynamic_cast<Widget*>(this->parent());
    parent->setFocusToGraphicView();
    startMusic();
    hideTitle();
    // ajoute un item Pillar à chaque 1000
    if(!pillarTimer->isActive())
    {
        pillarTimer->start(1000);
        enemyTimer->start(3000);
        bonusTimer->start(4500);
    }
}

void Scene::addMenu()
{
    showTitle();
    // MENU BUTTON
    btnMenu = new Button(QPixmap(":/images/buttons/menu-button-200.png"),
                         QPixmap(":/images/buttons/menu-button-press-200.png"));
    btnMenu->setZValue(1);
    addItem(btnMenu);
    connect(btnMenu, &Button::mouseRelease, [=]{
        showTitle();
        hideGameOverGraphics();
        delete bird;
        addBird();
        cleanPillars();
        cleanEnemy();
        cleanAttack();
        cleanBoss();
        QList<QGraphicsItem*> sceneItems = items();
        foreach(QGraphicsItem *item, sceneItems){
            Button*button = dynamic_cast<Button*>(item);
            // si c'est bien un pillar appel de la fonction
            if(button){
                button->show();
            }
        }
        btnMenu->hide();
    });
    btnMenu->hide();
    // START BUTTON
    btnStart = new Button(QPixmap(":/images/buttons/play-button-idle-200.png"),
                             QPixmap(":/images/buttons/play-button-press-200.png"));
    btnStart->setZValue(1);
    addItem(btnStart);// fonction de QGraphicsScene
    // placement au centre de l'écran
    btnStart->setPos(QPointF(0,-50) - QPointF(btnStart->boundingRect().width()/2,
                                               btnStart->boundingRect().height()/2));
    connect(btnStart, &Button::mouseRelease, [=]{
            QList<QGraphicsItem*> sceneItems = items();
            foreach(QGraphicsItem *item, sceneItems){
                Button*button = dynamic_cast<Button*>(item);
                // si c'est bien un pillar appel de la fonction
                if(button){
                    button->hide();
                }
            }
            startGame();
    });
    // NEXT BUTTON
    btnNext = new Button(QPixmap(":/images/buttons/right-button-idle-200.png"),
                             QPixmap(":/images/buttons/right-button-press-200.png"));
    btnNext->setZValue(1);
    addItem(btnNext);
    btnNext->setPos(QPointF(50,0) - QPointF(btnNext->boundingRect().width()/2,
                                               btnNext->boundingRect().height()/2));
    connect(btnNext, &Button::mouseRelease, [=]{
        qDebug() << "button next";
        if(birdColor == 2)
            birdColor = 0;
        else
            birdColor++;
        bird->color = static_cast<enum::BirdColor>(birdColor);
    });
    // BACK BUTTON
    btnBack = new Button(QPixmap(":/images/buttons/left-button-idle-200.png"),
                             QPixmap(":/images/buttons/left-button-press-200.png"));
    btnBack->setZValue(1);
    addItem(btnBack);
    btnBack->setPos(QPointF(-50,0) - QPointF(btnBack->boundingRect().width()/2,
                                               btnBack->boundingRect().height()/2));
    connect(btnBack, &Button::mouseRelease, [=]{
        qDebug() << "button back";
        if(birdColor == 0)
            birdColor = 2;
        else
            birdColor--;
        bird->color = static_cast<enum::BirdColor>(birdColor);
    });
    // MUSIC BUTTON
    if(musicOn)
        btnMusic = new Button(QPixmap(":/images/buttons/music-on-off-on-200.png"),
                             QPixmap(":/images/buttons/music-on-off-idle-200.png"));
    else
        btnMusic = new Button(QPixmap(":/images/buttons/music-on-off-off-200.png"),
                             QPixmap(":/images/buttons/music-on-off-idle-200.png"));
    btnMusic->setZValue(1);
    addItem(btnMusic);
    btnMusic->setPos(QPointF(0,50) - QPointF(btnMusic->boundingRect().width()/2,
                                               btnMusic->boundingRect().height()/2));
    connect(btnMusic, &Button::mouseRelease, [=]{
        setMusic(!musicOn);
        if(musicOn)
            btnMusic->setIdlePixmap(QPixmap(":/images/buttons/music-on-off-on-200.png"));
        else
            btnMusic->setIdlePixmap(QPixmap(":/images/buttons/music-on-off-off-200.png"));
    });
}

void Scene::addReplayButton()
{

}

void Scene::addSceneScore()
{
    sceneScoreTextItem = new QGraphicsTextItem();
    QString htmlString = "<p>" + QString::number(score) + "</p>";
    QFont mFont("Consolas", 20, QFont::Bold);
    sceneScoreTextItem->setHtml(htmlString);
    sceneScoreTextItem->setFont(mFont);
    sceneScoreTextItem->setDefaultTextColor(Qt::red);
    addItem(sceneScoreTextItem);

    sceneScoreTextItem->setPos(QPointF(sceneBackgroundMap->boundingRect().width()/2,-sceneBackgroundMap->boundingRect().height()/2)
                               +QPointF(-65,10));
    sceneScoreTextItem->setZValue(2);
}

void Scene::addSceneHighScore()
{
    sceneHighScoreTextItem = new QGraphicsTextItem();
    QString htmlString = "<p>" + QString::number(bestScore) + "</p>";
    QFont mFont("Consolas", 20, QFont::Bold);
    sceneHighScoreTextItem->setHtml(htmlString);
    sceneHighScoreTextItem->setFont(mFont);
    sceneHighScoreTextItem->setDefaultTextColor(Qt::red);
    addItem(sceneHighScoreTextItem);
    sceneHighScoreTextItem->setPos(-QPointF(sceneBackgroundMap->boundingRect().width()/2,sceneBackgroundMap->boundingRect().height()/2)
                               +QPointF(102,10));
    sceneHighScoreTextItem->setZValue(2);
}

void Scene::addSceneBonus()
{
    sceneBonusTextItem = new QGraphicsTextItem();
    QString htmlString = "<p>" + QString::number(bonus) + "</p>";
    QFont mFont("Consolas", 20, QFont::Bold);
    sceneBonusTextItem->setHtml(htmlString);
    sceneBonusTextItem->setFont(mFont);
    sceneBonusTextItem->setDefaultTextColor(Qt::red);
    addItem(sceneBonusTextItem);
    sceneBonusTextItem->setPos(-QPointF(sceneBackgroundMap->boundingRect().width()/2,sceneBackgroundMap->boundingRect().height()/2)
                               +QPointF(102,60));
    sceneBonusTextItem->setZValue(2);
}

void Scene::updateSceneScore()
{
    QString htmlString = "<p>" + QString::number(score) + "</p>";
    QFont mFont("Consolas", 20, QFont::Bold);
    sceneScoreTextItem->setHtml(htmlString);
}

void Scene::updateSceneHighScore()
{
    QString htmlString = "<p>" + QString::number(bestScore) + "</p>";
    QFont mFont("Consolas", 20, QFont::Bold);
    sceneHighScoreTextItem->setHtml(htmlString);
}

void Scene::updateSceneBonus()
{
    QString htmlString = "<p>" + QString::number(bonus) + "</p>";
    QFont mFont("Consolas", 20, QFont::Bold);
    sceneBonusTextItem->setHtml(htmlString);
}

void Scene::setMusic(bool x)
{
    musicOn = x;
    if(sceneMedia->state() == QMediaPlayer::PlayingState && !musicOn)
        sceneMedia->stop();
    else if(musicOn) {
        startMusic();
    }
}

void Scene::showTitle()
{
    titlePix = new QGraphicsPixmapItem(QPixmap(":/images/screaming-bird-title-600.png"));
    addItem(titlePix);
    // placement au centre de l'écran
    titlePix->setPos(QPointF(0,0) - QPointF(titlePix->boundingRect().width()/2,
                                               250));
    titleTimer = new QTimer();
    connect(titleTimer, &QTimer::timeout, [=]{
        updatePixmap();
    });
    titleTimer->start(50);
}

void Scene::hideTitle()
{    
    if(titlePix != nullptr) {
        titleTimer->stop();
        delete titleTimer;
        removeItem(titlePix);
        delete titlePix;
        titlePix = nullptr;
    }
}

void Scene::setUpPillarTimer()
{
    pillarTimer = new QTimer(this);
    // quand le timer à terminé ajoute un Pillar
    connect(pillarTimer, &QTimer::timeout, [=](){
        PillarItem * pillarItem = new PillarItem();
        connect(pillarItem, &PillarItem::collideFail,[=]{
            // stop the game
            // stop pillar timer, lorsqu'il y a une collision
            pillarTimer->stop();
            enemyTimer->stop();
            bonusTimer->stop();
            freezeBirdAndPillarsInPlace();
            setGameOn(false);
            showGameOverGraphics();
        });
        addItem(pillarItem);
    });
}

void Scene::setUpEnemyTimer(){
    enemyTimer = new QTimer(this);
    connect(enemyTimer, &QTimer::timeout, [=](){
    enemy * enemyItem = new enemy();
    connect(enemyItem, &enemy::collideFail,[=]{
        pillarTimer->stop();
        enemyTimer->stop();
        bonusTimer->stop();
        freezeBirdAndPillarsInPlace();
        setGameOn(false);
        showGameOverGraphics();
        });
    enemyItem->setPos(QPointF(0,0) - QPointF(enemyItem->boundingRect().width()/2,
                                                   enemyItem->boundingRect().height()/2));
    addItem(enemyItem);
    });
}

void Scene::setUpBonus()
{
    bonusTimer = new QTimer(this);
    connect(bonusTimer, &QTimer::timeout, [=](){
        Bonus * bonus = new Bonus();
    bonus->setPos(QPointF(0,0) - QPointF(bonus->boundingRect().width()/2,
                                                       bonus->boundingRect().height()/2));
    addItem(bonus);
    });
}

void Scene::setUpAttack()
{
    fireball = new BirdAttack(bird->y(), sceneBackgroundMap->boundingRect().width()/2);
    addItem(fireball);
}

void Scene::setUpBonusEffectTimer()
{
    bonusEffectTimer = new QTimer(this);
    connect(bonusEffectTimer, &QTimer::timeout, [=](){    
        bird->setPowerUp(false);
        Bonuseffect->setMedia(QUrl("qrc:/sound effects/smb_pipe.wav"));
        if(!paused){
            Bonuseffect->play();
        }
        bonusEffectTimer->stop();
    });
}

void Scene::setBossIndex(int Index)
{
    bossIndex = Index;
}

void Scene::BonusEffect(){
    if(bonus <= 0){
    } else {
      // Nouveau nombres de bonus
      bonus--;
      updateSceneBonus();
      // Jouer le son
      Bonuseffect->setMedia(QUrl("qrc:/sound effects/smb_powerup.wav"));
      Bonuseffect->play();
      // Effet du bonus
      bird->setPowerUp(true);
      bonusEffectTimer->start(5000);
    }
}

void Scene::freezeBirdAndPillarsInPlace()
{
    // freeze bird
    bird->freezeInPlace();

    // freeze pillar, get all item in scene
    QList<QGraphicsItem*> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems){
        PillarItem* pillar = dynamic_cast<PillarItem*>(item);
        enemy* EnemyItem = dynamic_cast<enemy*>(item);
        BirdAttack* fireballItem = dynamic_cast<BirdAttack*>(item);
        Bonus* bonusItem = dynamic_cast<Bonus*>(item);
        Boss* bossItem = dynamic_cast<Boss*>(item);
        // si c'est bien un pillar appel de la fonction
        if(pillar){
            pillar->freezeInPlace();
        }else if(EnemyItem){
            EnemyItem->freezeInPlace();
        }else if (fireballItem) {
            fireballItem->freezeInPlace();
        }else if (bonusItem){
            bonusItem->freezeInPlace();
        }else if (bossItem){
            bossItem->freezeInPlace();
        }
    }
}

void Scene::cleanPillars()
{
    QList<QGraphicsItem*> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems){
        PillarItem*pillar = dynamic_cast<PillarItem*>(item);
        // si c'est bien un pillar appel de la fonction
        if(pillar){
            removeItem(pillar);
            delete pillar;
        }
    }
}

void Scene::cleanEnemy()
{
    QList<QGraphicsItem*> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems){
        enemy *enemyItem = dynamic_cast<enemy*>(item);
        // si c'est bien un enemy appel de la fonction
        if(enemyItem){
            removeItem(enemyItem);
            delete enemyItem;
        }
    }
}

void Scene::cleanAttack()
{
    QList<QGraphicsItem*> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems)
    {
        BirdAttack *fireballItem = dynamic_cast<BirdAttack*>(item);
        if(fireballItem){
            //removeItem(fireballItem);
            delete fireballItem;
        }
    }
}

void Scene::cleanBonus()
{
    QList<QGraphicsItem*> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems)
    {
        Bonus *bonusItem = dynamic_cast<Bonus*>(item);
        if(bonusItem){
            removeItem(bonusItem);
            delete bonusItem;
        }
    }
}

void Scene::cleanBoss()
{
    QList<QGraphicsItem*> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems)
    {
        Boss *bossItem = dynamic_cast<Boss*>(item);
        if(bossItem){
            removeItem(bossItem);
            delete bossItem;
        }
    }
}
void Scene::updatePixmap()
{
    if(titleIndex >= 21)
        titleIndex = 1;
    else
        titleIndex++;
    QString path =":/images/title/screaming-bird-title-"+QString::number(titleIndex)+".png";
    titlePix->setPixmap(QPixmap(path));
}

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool value)
{
    gameOn = value;
}

void Scene::incrementScore()
{
    score++;
    bossIndex++;
    if(score > bestScore){
        bestScore = score;
        updateSceneHighScore();
    }

    //Initialisation du Boss apres un certain nombre
    if(bossIndex == 5){
        pillarTimer->stop();
        enemyTimer->stop();
        bonusTimer->stop();
        setUpBoss();
    }

    qDebug() << "Score: " << score << " Best Score: " << bestScore;
    updateSceneScore();
}

void Scene::setUpBoss()
{
    Boss * BossItem = new Boss();
    BossItem->setPos(QPointF(0,0) - QPointF(BossItem->boundingRect().width()/2,
                                                   BossItem->boundingRect().height()/2));
    BossItem->setZValue(1);

    connect(BossItem, &Boss::Bossdead,[=](){
        qDebug() << "Continuation du niveau";
        pillarTimer->start(1000);
        enemyTimer->start(3000);
        bonusTimer->start(4500);
        setBossIndex(0);
    });
    addItem(BossItem);
}

void Scene::continueGame()
{
    qDebug() << "Continuation du niveau";
    pillarTimer->start(1000);
    enemyTimer->start(3000);
    bonusTimer->start(4500);
    setBossIndex(0);
}

void Scene::incrementBonus()
{
    bonus++;
    qDebug() << "Bonus: " << bonus;
    updateSceneBonus();
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    // vérifier le le boutton presser else if(event->key() == Qt::Key_Escape)
    if(!gameOn) { // ne rien faire
    }
    else if(event->key() == Qt::Key_Escape){
        paused = !paused;
        if(paused)
        {
            bird->pause();
        } else {
            bird->start();
        }
    } else if((event->key() == Qt::Key_Space || event->key() == Qt::Key_W)  && !paused){
        bird->shootUp();
    } else if(event->key() == Qt::Key_S  && !paused){
        bird->shootDown();
    } else if (event->key() == Qt::Key_D && !paused) {
        setUpAttack();
    } else if (event->key() == Qt::Key_A && !paused){
        BonusEffect();
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // vérifier le le boutton presser
    if(!gameOn) {// ne rien faire
    }
    else if(event->button() == Qt::LeftButton && !paused){
        bird->shootUp();
    }
    QGraphicsScene::mousePressEvent(event);
}

void Scene::showGameOverGraphics()
{
    bird->die();
    if(sceneMedia->state() == QMediaPlayer::PlayingState)
        sceneMedia->stop();
    sceneMedia->setMedia(QUrl("qrc:/sound effects/smb_gameover.wav"));
    sceneMedia->play();
    if(gameOverPix)
        delete gameOverPix;
    gameOverPix = new QGraphicsPixmapItem(QPixmap(":/images/gameover.png"));
    addItem(gameOverPix);
    // placement au centre de l'écran
    gameOverPix->setPos(QPointF(0,0) - QPointF(gameOverPix->boundingRect().width()/2,
                                               gameOverPix->boundingRect().height()/2));
    btnMenu->setPos(QPointF(0,0)
                    - QPointF(btnMenu->boundingRect().width()/2,
                              btnMenu->boundingRect().height()/2
                              -gameOverPix->boundingRect().height()
                              -30));
    btnMenu->show();
    btnStart->show();
}

void Scene::hideGameOverGraphics()
{
    if(gameOverPix != nullptr) {
        removeItem(gameOverPix);
        delete gameOverPix;
        gameOverPix = nullptr;
    }
    if(scoreTextItem != nullptr){
        removeItem(scoreTextItem);
        delete scoreTextItem;
        scoreTextItem = nullptr;
    }
}

 int Scene::getScore()
 {
     return score;
 }

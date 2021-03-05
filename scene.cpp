#include "scene.h"
#include "widget.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    gameOn(false), score(0), bestScore(0)
{
    gameOverPix = nullptr;
    scoreTextItem = nullptr;
    sceneMedia =  new QMediaPlayer();
    setUpPillarTimer();
}

Scene::~Scene()
{
    delete gameOverPix;
    delete scoreTextItem;
    delete sceneMedia;
    delete bird;
    delete btnStart;
}

void Scene::startMusic()
{
    if(sceneMedia->state() == QMediaPlayer::PlayingState)
        sceneMedia->stop();
    sceneMedia->setMedia(QUrl("qrc:/sound effects/super_mario_medley.mp3"));
    sceneMedia->play();
}

void Scene::addBird()
{
    // initialisation the bird et ajout à la scene
    bird = new BirdItem(QPixmap(":/images/redbird-upflap.png"));
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
        bird = new BirdItem(QPixmap(":/images/redbird-midflap.png"));
    else if(static_cast<enum::BirdColor>(birdColor) == BirdColor::BLUE)
        bird = new BirdItem(QPixmap(":/images/birds/bluebird-midflap-200.png"));
    else if(static_cast<enum::BirdColor>(birdColor) == BirdColor::YELLOW)
        bird = new BirdItem(QPixmap(":/images/birds/yellowbird-midflap-200.png"));
    bird->setPos(QPointF(0,0) - QPointF(bird->boundingRect().width()/2,
                                                   bird->boundingRect().height()/2));

    addItem(bird);
    bird->setZValue(1);
    bird->startFlying();
    // ajoute un item Pillar à chaque 1000
    if(!pillarTimer->isActive())
    {
        score = 0;
        cleanPillars();
        setGameOn(true);
        hideGameOverGraphics();
        pillarTimer->start(1000);
        startMusic();
        Widget * parent = dynamic_cast<Widget*>(this->parent());
        parent->setFocusToGraphicView();
    }
}

void Scene::addMenu()
{
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
        musicOn = !musicOn;
        if(musicOn)
            btnMusic->setIdlePixmap(QPixmap(":/images/buttons/music-on-off-on-200.png"));
        else
            btnMusic->setIdlePixmap(QPixmap(":/images/buttons/music-on-off-off-200.png"));
    });
}

void Scene::addReplayButton()
{

}

void Scene::setUpPillarTimer()
{
    pillarTimer = new QTimer(this);
    // quand le timer à terminé ajoute un Pillar
    connect(pillarTimer, &QTimer::timeout, [=](){
        PillarItem * pillarItem = new PillarItem();
        int number = 0;
        pillarItem->setPillarNumber(number);
        connect(pillarItem, &PillarItem::collideFail,[=]{
            // stop the game
            // stop pillar timer, lorsqu'il y a une collision
            pillarTimer->stop();
            freezeBirdAndPillarsInPlace();
            setGameOn(false);
            showGameOverGraphics();
        });
        addItem(pillarItem);
    });
}

void Scene::setUpEnemy(){
    enemy *enemyItem = new enemy();
    addItem(enemyItem);
    qDebug() << "enemy created";

}

void Scene::freezeBirdAndPillarsInPlace()
{
    // freeze bird
    bird->freezeInPlace();
    // freeze pillar, get all item in scene
    QList<QGraphicsItem*> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems){
        PillarItem*pillar = dynamic_cast<PillarItem*>(item);
        // si c'est bien un pillar appel de la fonction
        if(pillar){
            pillar->freezeInPlace();
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
    if(score > bestScore)
        bestScore = score;

    qDebug() << "Score: " << score << " Best Score: " << bestScore;
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
    } else if(event->key() == Qt::Key_Space && !paused){
        bird->shootUp();
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // vérifier le le boutton presser
    if(!gameOn) {// ne rien fiare
    }
    else if(event->button() == Qt::LeftButton && !paused){
        bird->shootUp();
    }
    QGraphicsScene::mousePressEvent(event);
}

void Scene::showGameOverGraphics()
{
    if(sceneMedia->state() == QMediaPlayer::PlayingState)
        sceneMedia->stop();
    sceneMedia->setMedia(QUrl("qrc:/sound effects/smb_gameover.wav"));
    sceneMedia->play();
    gameOverPix = new QGraphicsPixmapItem(QPixmap(":/images/gameover.png"));
    addItem(gameOverPix);
    // placement au centre de l'écran
    gameOverPix->setPos(QPointF(0,0) - QPointF(gameOverPix->boundingRect().width()/2,
                                               gameOverPix->boundingRect().height()/2));
    // QGraphicsTextItem class provides a text item that you can add to a QGraphicsScene to display formatted text.
    scoreTextItem = new QGraphicsTextItem();
    QString htmlString = "<p> Score : " + QString::number(score) + " </p>"
        + "<p> Best Score : " + QString::number(bestScore) + "</p>";

    QFont mFont("Consolas", 30, QFont::Bold);
    scoreTextItem->setHtml(htmlString);
    scoreTextItem->setFont(mFont);
    scoreTextItem->setDefaultTextColor(Qt::red);
    addItem(scoreTextItem);

    scoreTextItem->setPos(QPointF(0,0) - QPointF(scoreTextItem->boundingRect().width()/2,
                                                 -gameOverPix->boundingRect().height()/2));


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

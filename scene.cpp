/*
*
*   Author: jara2502, pera3307, rouy2404, veic1101
*   Date: 2021-04-13 (mar., 13 avril. 2021)
*
*/
#include <math.h> 
#include "scene.h"
#include "widget.h"

Scene::Scene(QObject* parent) : QGraphicsScene(parent),
    gameOn(false), score(0), bestScore(0), bonus(0), bossIndex(0), attack(0)
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
    setUpBossAttack();
    startFPGACommunication();
}

Scene::~Scene()
{
    delete pillarTimer;
    delete enemyTimer;
    delete titlePix;
    delete gameOverPix;
    delete scoreTextItem;
    delete bonusTextItem;
    delete sceneScoreTextItem;
    delete sceneBonusTextItem;
    delete sceneBackgroundMap;
    delete sceneMedia;
    //delete bird;
    foreach(Button *item, menuButtons){
        delete item;
    }
    foreach(Button* item, btnPhonemes) {
        delete item;
    }
    delete backButtonPhoneme;
    if (fpga->estOk())
        delete fpga;
    delete titleTimer;
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
        -sceneBackgroundMap->boundingRect().height() / 2,
        sceneBackgroundMap->boundingRect().height() / 2
    );
    bird->color = static_cast<enum::BirdColor>(0);
    bird->setZValue(1);
    bird->setPos(QPointF(0, 0) - QPointF(bird->boundingRect().width() / 2,
        bird->boundingRect().height() / 2));
    addItem(bird);
}

void Scene::createBird()
{
    if (static_cast<enum::BirdColor>(birdColor) == BirdColor::RED)
        bird = new BirdItem(QPixmap(":/images/redbird-midflap.png"),
            -sceneBackgroundMap->boundingRect().height() / 2, sceneBackgroundMap->boundingRect().height() / 2);
    else if (static_cast<enum::BirdColor>(birdColor) == BirdColor::BLUE)
        bird = new BirdItem(QPixmap(":/images/birds/bluebird-midflap-200.png"),
            -sceneBackgroundMap->boundingRect().height() / 2, sceneBackgroundMap->boundingRect().height() / 2);
    else if (static_cast<enum::BirdColor>(birdColor) == BirdColor::YELLOW)
        bird = new BirdItem(QPixmap(":/images/birds/yellowbird-midflap-200.png"),
            -sceneBackgroundMap->boundingRect().height() / 2, sceneBackgroundMap->boundingRect().height() / 2);
    bird->setPos(QPointF(0, 0) - QPointF(bird->boundingRect().width() / 2,
        bird->boundingRect().height() / 2));

    bird->color = static_cast<BirdColor>(this->birdColor);
    addItem(bird);
    bird->setZValue(1);
}

void Scene::startGame()
{
    //start animation for Bird and Pillars
    //delete bird;
    createBird();
    
    score = 0;
    bonus = 0;
    attack = 0;
    bossIndex = 0;
    updateSceneScore();
    updateSceneBonus();
    cleanAll();
    setGameState(GameState::PLAY);
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

void Scene::setDifficulty()
{
    // enlever l'oiseau
    delete bird;

    // ajouter 2 boutons
    // clavier
    btnClavier = new Button(QPixmap(":/images/buttons/clavier-button.png"),
        QPixmap(":/images/buttons/clavier-button.png"));
    btnClavier->setZValue(1);
    addItem(btnClavier);
    btnClavier->setPos(QPointF(0, -20) - QPointF(btnClavier->boundingRect().width() / 2,
        btnClavier->boundingRect().height() / 2));

    connect(btnClavier, &Button::mouseRelease, [=] {
        btnClavier->hide();
        btnPhoneme->hide();
        backButtonDifficulty->hide();
        startGame();    
    });

    // phonemes
    btnPhoneme = new Button(QPixmap(":/images/buttons/phonemes-button.png"),
        QPixmap(":/images/buttons/phonemes-button.png"));
    btnPhoneme->setZValue(1);
    addItem(btnPhoneme);
    btnPhoneme->setPos(QPointF(0, 50) - QPointF(btnPhoneme->boundingRect().width() / 2,
        btnPhoneme->boundingRect().height() / 2));

    connect(btnPhoneme, &Button::mouseRelease, [=] {
        btnPhoneme->hide();
        btnClavier->hide();
        backButtonDifficulty->hide();
        startGame();
    });

    // back button
    backButtonDifficulty = new Button(QPixmap(":/images/buttons/left-button-idle-200.png"),
        QPixmap(":/images/buttons/left-button-press-200.png"));
    backButtonDifficulty->setZValue(1);
    addItem(backButtonDifficulty);
    QPointF backButtonDifficulty_position = QPointF(backButtonPhoneme->boundingRect().width(), -backButtonPhoneme->boundingRect().height())
        + QPointF(-sceneBackgroundMap->boundingRect().width() / 2, sceneBackgroundMap->boundingRect().height() / 2)
        + QPointF(20, -20);
    backButtonDifficulty->setPos(backButtonDifficulty_position);
    connect(backButtonDifficulty, &Button::mouseRelease, [=]
        {
            btnPhoneme->hide();
            btnClavier->hide();
            backButtonDifficulty->hide();
            showMenu();
            createBird();
            setDifficultyOrNo = true;
        });
          
}

void Scene::cleanAll()
{
    hideGameOverGraphics();
    cleanPillars();
    cleanEnemy();
    cleanAttack();
    cleanBonus();
    cleanBoss();
    cleanBossAttack();
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
        cleanAll();
        showTitle();
        //delete bird;
        addBird();        
        showMenu();
        setDifficultyOrNo = true;
        btnMenu->hide();
    });
    btnMenu->hide();
    // START BUTTON
    Button * btnStart = new Button(QPixmap(":/images/buttons/play-button-idle-200.png"),
                             QPixmap(":/images/buttons/play-button-press-200.png"));
    btnStart->setZValue(1);
    addItem(btnStart);// fonction de QGraphicsScene
    // placement au centre de l'écran
    btnStart->setPos(QPointF(0,-50) - QPointF(btnStart->boundingRect().width()/2,
                                               btnStart->boundingRect().height()/2));
    connect(btnStart, &Button::mouseRelease, [=]{
        hideAllButton();
        cleanAll();
        if (setDifficultyOrNo)
        {
            setDifficulty();
            setDifficultyOrNo = false;
        }
        else
        {
            startGame();
        }
    });
    menuButtons.push_back(btnStart);
    // NEXT BUTTON
    Button * btnNext = new Button(QPixmap(":/images/buttons/right-button-idle-200.png"),
                             QPixmap(":/images/buttons/right-button-press-200.png"));
    btnNext->setZValue(1);
    addItem(btnNext);
    btnNext->setPos(QPointF(50,0) - QPointF(btnNext->boundingRect().width()/2,
                                               btnNext->boundingRect().height()/2));
    connect(btnNext, &Button::mouseRelease, [=]{
        if(birdColor == 2)
            birdColor = 0;
        else
            birdColor++;
        bird->color = static_cast<enum::BirdColor>(birdColor);
    });
    menuButtons.push_back(btnNext);
    // BACK BUTTON
    Button* btnBack = new Button(QPixmap(":/images/buttons/left-button-idle-200.png"),
                             QPixmap(":/images/buttons/left-button-press-200.png"));
    btnBack->setZValue(1);
    addItem(btnBack);
    btnBack->setPos(QPointF(-50,0) - QPointF(btnBack->boundingRect().width()/2,
                                               btnBack->boundingRect().height()/2));
    connect(btnBack, &Button::mouseRelease, [=]{
        if(birdColor == 0)
            birdColor = 2;
        else
            birdColor--;
        bird->color = static_cast<enum::BirdColor>(birdColor);
    });
    menuButtons.push_back(btnBack);
    // MUSIC BUTTON
    Button* btnMusic;
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
    menuButtons.push_back(btnMusic);
    // TEST BUTTON
    Button * btnTest = new Button(QPixmap(":/images/buttons/test-button-200.png"),
        QPixmap(":/images/buttons/test-button-press-200.png")); 
    btnTest->setZValue(1);
    addItem(btnTest);
    btnTest->setPos(QPointF(0, 100) - QPointF(btnTest->boundingRect().width() / 2,
        btnTest->boundingRect().height() / 2));
    connect(btnTest, &Button::mouseRelease, [=] {
        hideAllButton();
        // ajout des bonus pour les tests
        this->bonus = 999999;
        this->updateSceneBonus();
    });
    menuButtons.push_back(btnTest);
    // CALLIBRATION BUTTON
    Button * btnCallibration = new Button(QPixmap(":/images/buttons/callibration-button-200.png"),
        QPixmap(":/images/buttons/callibration-button-press-200.png"));
    btnCallibration->setZValue(1);
    addItem(btnCallibration);
    btnCallibration->setPos(QPointF(0, 150) - QPointF(btnCallibration->boundingRect().width() / 2,
        btnCallibration->boundingRect().height() / 2));
    connect(btnCallibration, &Button::mouseRelease, [=] {
        for (int i = 0; i < 4; i++)
            for (int y = 0; y < 4; y++)
                phonemesCallibration[i][y] = 0;
        // Progress bar
        progressBarPhonemes = new QProgressBar();
        progressBarPhonemes->setMaximum(100);
        progressBarPhonemes->setMinimum(0);
        this->layout->addWidget(progressBarPhonemes);
        hideAllButton();
        this->setGameState(GameState::IN_CALLIBRATION);
        showCallibration();
        btnPhonemes[0]->mouseRelease();
    });
    menuButtons.push_back(btnCallibration);
    // PHONEME A BUTTON
    Button* btnA = new Button(QPixmap(":/images/Phonemes/A.png"),
        QPixmap(":/images/Phonemes/A-selected.png"));
    btnA->setZValue(1);
    addItem(btnA);
    btnA->setPos(QPointF(btnA->boundingRect().width() * -3, 0) - QPointF(btnA->boundingRect().width() / 2,
        btnA->boundingRect().height() / 2));
    btnA->hide();
    connect(btnA, &Button::mouseRelease, [=] {
        currentPhonemeCallibrationIndex = 0;
        for (int y = 0; y < 4; y++)
            phonemesCallibration[currentPhonemeCallibrationIndex][y] = 0;
        user.clearPhoneme(static_cast<User::Phonemes>(currentPhonemeCallibrationIndex));
        progressBarPhonemes->setValue(currentProgression = 0);
        foreach(Button* item, btnPhonemes) {
            item->selected = false;
            item->setToIdle();
        }
        btnA->selected = true;
        btnA->setToPress();
    });
    btnPhonemes.push_back(btnA);
    // PHONEME E BUTTON
    Button* btnE = new Button(QPixmap(":/images/Phonemes/E.png"),
        QPixmap(":/images/Phonemes/E-selected.png"));
    btnE->setZValue(1);
    addItem(btnE);
    btnE->setPos(QPointF(btnE->boundingRect().width() * -1, 0) - QPointF(btnE->boundingRect().width() / 2,
        btnE->boundingRect().height() / 2));
    btnE->hide();
    connect(btnE, &Button::mouseRelease, [=] {
        currentPhonemeCallibrationIndex = 1;
        for (int y = 0; y < 4; y++)
            phonemesCallibration[currentPhonemeCallibrationIndex][y] = 0;
        user.clearPhoneme(static_cast<User::Phonemes>(currentPhonemeCallibrationIndex));
        progressBarPhonemes->setValue(currentProgression = 0);
        foreach(Button * item, btnPhonemes) {
            item->selected = false;
            item->setToIdle();
        }
        btnE->selected = true;
        btnE->setToPress();
    });
    btnPhonemes.push_back(btnE);
    // PHONEME I BUTTON
    Button* btnI = new Button(QPixmap(":/images/Phonemes/I.png"),
        QPixmap(":/images/Phonemes/I-selected.png"));
    btnI->setZValue(1);
    addItem(btnI);
    btnI->setPos(QPointF(btnI->boundingRect().width() * 1, 0) - QPointF(btnI->boundingRect().width() / 2,
        btnI->boundingRect().height() / 2));
    btnI->hide();
    connect(btnI, &Button::mouseRelease, [=] {
        currentPhonemeCallibrationIndex = 2;
        for (int y = 0; y < 4; y++)
            phonemesCallibration[currentPhonemeCallibrationIndex][y] = 0;
        user.clearPhoneme(static_cast<User::Phonemes>(currentPhonemeCallibrationIndex));
        progressBarPhonemes->setValue(currentProgression = 0);
        foreach(Button * item, btnPhonemes) {
            item->selected = false;
            item->setToIdle();
        }
        btnI->selected = true;
        btnI->setToPress();
    });
    btnPhonemes.push_back(btnI);
    // PHONEME O BUTTON
    Button* btnO = new Button(QPixmap(":/images/Phonemes/O.png"),
        QPixmap(":/images/Phonemes/O-selected.png"));
    btnO->setZValue(1);
    addItem(btnO);
    btnO->setPos(QPointF(btnO->boundingRect().width() * 3, 0) - QPointF(btnO->boundingRect().width() / 2,
        btnO->boundingRect().height() / 2));
    btnO->hide();
    connect(btnO, &Button::mouseRelease, [=] {
        currentPhonemeCallibrationIndex = 3;
        for (int y = 0; y < 4; y++)
            phonemesCallibration[currentPhonemeCallibrationIndex][y] = 0;
        user.clearPhoneme(static_cast<User::Phonemes>(currentPhonemeCallibrationIndex));
        progressBarPhonemes->setValue(currentProgression = 0);
        foreach(Button * item, btnPhonemes) {
            item->selected = false;
            item->setToIdle();
        }
        btnO->selected = true;
        btnO->setToPress();
    });
    btnPhonemes.push_back(btnO);
    // BACK BUTTON PHONEME
    backButtonPhoneme = new Button(QPixmap(":/images/buttons/left-button-idle-200.png"),
        QPixmap(":/images/buttons/left-button-press-200.png"));
    backButtonPhoneme->setZValue(1);
    addItem(backButtonPhoneme);
    backButtonPhoneme->hide();
    QPointF backButtonPhoneme_position = QPointF(backButtonPhoneme->boundingRect().width(), -backButtonPhoneme->boundingRect().height())
        + QPointF(-sceneBackgroundMap->boundingRect().width() / 2, sceneBackgroundMap->boundingRect().height() / 2)
        + QPointF(20, -20);
    backButtonPhoneme->setPos(backButtonPhoneme_position);
    connect(backButtonPhoneme, &Button::mouseRelease, [=] {
        this->setGameState(GameState::STOPPED);
        hideAllButton();
        showMenu();
        for (int i = 0; i < 4; i++)
            for (int y = 0; y < 4; y++)
                phonemesCallibration[i][y] = phonemesCallibration[i][y] / progressBarPhonemes->maximum();
        layout->removeWidget(progressBarPhonemes);
        delete progressBarPhonemes;
    });
    // ESPACE BUTTON
    espaceButton = new Button(QPixmap(":/images/Phonemes/espace-button.png"),
        QPixmap(":/images/Phonemes/espace-button-press.png"));
    espaceButton->setZValue(1);
    addItem(espaceButton);
    espaceButton->hide();
    QPointF espaceButton_position = QPointF(-espaceButton->boundingRect().width() / 2, backButtonPhoneme_position.y())
        + QPointF(0, -espaceButton->boundingRect().height() / 2);
    espaceButton->setPos(espaceButton_position);
// pas de connect pour espace parce que nous allons écrire le code dans le keypressevent de la scene
}
void Scene::showCallibration() 
{
    foreach(Button * item, btnPhonemes) {
        item->show();
    }
    backButtonPhoneme->show();
    espaceButton->show();
}
void Scene::showMenu() {
    foreach(Button * item, menuButtons) {
        item->show();
    }
}

void Scene::hideAllButton() 
{
    QList<QGraphicsItem*> sceneItems = items();
    foreach(QGraphicsItem * item, sceneItems) {
        Button* button = dynamic_cast<Button*>(item);
        // si c'est bien un pillar appel de la fonction
        if (button) {
            button->hide();
        }
    }
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

void Scene::startFPGACommunication()
{
    fpga = new CommunicationFPGA();
    fpgaTimer = new QTimer();
    connect(fpgaTimer, &QTimer::timeout, [=] {
        if (fpga->estOk()) {
            if (this->getGameState() == GameState::PLAY)
            {
                auto start = chrono::steady_clock::now();
                // 0 1 2 4 8
                int stat_btn = 0; 
                /*int echconv[4];*/
                int* echconv = fpga->read4Channel();
                int filtrePredefinedPhone[4][4];

                // si l'utilisateur n'a pas défini ses phonèmes
                if (user.phonemesReady()) 
                {
                    int** userDefinedPhonemes = user.getPhonemes();
                    for (int m = 0; m < 4; m++)
                        for (int n = 0; n < 4; n++)
                            filtrePredefinedPhone[m][n] = userDefinedPhonemes[m][n];
                }
                else 
                {
                    for (int m = 0; m < 4; m++)
                        for (int n = 0; n < 4; n++)
                            filtrePredefinedPhone[m][n] = fpga->filtrePredefinedPhone[m][n];
                }

                int filtreDist[4] = { 0,0,0,0};
                fpga->lireRegistre(nreg_lect_stat_btn, stat_btn);     // lecture buttons
                if (fpga->stat_btn != stat_btn && stat_btn != 0)
                {
                    switch (stat_btn)
                    {
                    case 1:
                        bird->shootUp();
                        break;
                    case 2:
                        bird->shootDown();
                        break;
                    case 4:
                        setUpAttack();
                        break;
                    }
                }
                fpga->stat_btn = stat_btn;
            
                // si seulement si le boutton 8 est présé
                if (stat_btn == 8)
                {
                    // enregistrement des distances pour chaque phonème
                    for (int m = 0; m < 4; m++)
                    {
                        for (int n = 0; n < 4; n++)
                        {
                            filtreDist[m] += (filtrePredefinedPhone[m][n] - echconv[n]) * (filtrePredefinedPhone[m][n] - echconv[n]);
                        }
                        filtreDist[m] = sqrt(filtreDist[m]);
                    }

                    // trouver la distance minimal des distances trouvées 
                    int index = 0;
                    phonemes phonemeMinFound;
                    int minDist = filtreDist[index];
                    for (int m = 0; m < 4; m++)
                    {
                        if (minDist > filtreDist[m])
                        {
                            minDist = filtreDist[m];
                            index = m;
                        }
                    }

                    if (minDist < 30) 
                    {
                        // choix du phon et ajout au conteur
                        phonemeMinFound = static_cast<phonemes>(index);
                        if (this->currentPhoneme == phonemeMinFound)
                        {
                            this->counter++;
                        }
                        else
                        {
                            this->currentPhoneme = phonemeMinFound;
                            this->counter = 1;
                        }

                        // faire l'action si plus que 50ms pour le phonèmes
                        if (this->counter >= 12)
                        {
                            switch (index)
                            {
                            case 0:
                                bird->shootUp();
                                break;
                            case 1:
                                bird->shootDown();
                                break;
                            case 2:
                                setUpAttack();
                                break;
                            case 3:
                                BonusEffect();
                                break;
                            }
                            qDebug() << "Distance min: " << filtreDist[index] << " Phonème: " << this->currentPhoneme;
                            this->currentPhoneme = phonemes::DEFAULT;
                            this->counter = 0;
                        }
                    }
                    else
                    {
                        this->currentPhoneme = phonemes::DEFAULT;
                        this->counter = 0;
                    }
                }
                else
                {
                    this->currentPhoneme = phonemes::DEFAULT;
                    this->counter = 0;
                }
                auto end = chrono::steady_clock::now();
                auto diff = end - start;
                qDebug() << chrono::duration <double, milli>(diff).count() << " ms" << endl;
            }
            }
        });
    fpgaTimer->start(10);
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
            setGameState(GameState::STOPPED);
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
        setGameState(GameState::STOPPED);
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
        connect(bonus, &Bonus::collideFail, [=] {
            incrementBonus();
            removeItem(bonus);
        });
        addItem(bonus);
    });
}

void Scene::setUpAttack()
{
    BirdAttack* fireball = new BirdAttack(bird->y(), sceneBackgroundMap->boundingRect().width()/2);
    addItem(fireball);
}

void Scene::setUpBossAttack()
{
    BossAttackTimer = new QTimer(this);
    connect(BossAttackTimer, &QTimer::timeout, [=](){
    if(attack != 3){
        BossAttack* BossBall = new BossAttack(BossItem->y(),sceneBackgroundMap->boundingRect().width()/2);
        attack++;
        connect(BossBall, &BossAttack::collideFail,[=]{
            pillarTimer->stop();
            enemyTimer->stop();
            bonusTimer->stop();
            BossAttackTimer->stop();
            freezeBirdAndPillarsInPlace();
            setGameState(GameState::STOPPED);
            showGameOverGraphics();
        });
        BossBall->setZValue(2);
        addItem(BossBall);
    }else{
        BossBoulet* Boulet = new BossBoulet(BossItem->y(),sceneBackgroundMap->boundingRect().width()/2);
        attack = 0;
        connect(Boulet, &BossBoulet::collideFail,[=]{
            pillarTimer->stop();
            enemyTimer->stop();
            bonusTimer->stop();
            BossAttackTimer->stop();
            freezeBirdAndPillarsInPlace();
            setGameState(GameState::STOPPED);
            showGameOverGraphics();
        });
        Boulet->setZValue(2);
        addItem(Boulet);
    }
    });

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
        Freezable* itemFreezable = dynamic_cast<Freezable*>(item);
        // si c'est bien un pillar appel de la fonction
        if(itemFreezable)
            itemFreezable->freezeInPlace();
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

void Scene::cleanBossAttack()
{
    QList<QGraphicsItem*> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems)
    {
        BossAttack *fireballItem = dynamic_cast<BossAttack*>(item);
        BossBoulet *bouletItem = dynamic_cast<BossBoulet*>(item);
        if(fireballItem){
            //removeItem(fireballItem);
            delete fireballItem;
        } else if(bouletItem){
            //removeItem(fireballItem);
            delete bouletItem;
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

Scene::GameState Scene::getGameState() const
{
    return this->gameState;
}

void Scene::setGameState(GameState state)
{
    this->gameState = state;
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
    if(bossIndex == 18){
        pillarTimer->stop();
        enemyTimer->stop();
        bonusTimer->stop();
        setUpBoss();
    }
    updateSceneScore();
}

void Scene::setUpBoss()
{
    BossItem = new Boss();
    BossItem->setPos(QPointF(0,0) - QPointF(BossItem->boundingRect().width()/2,
                                                   BossItem->boundingRect().height()/2));
    BossItem->setZValue(1);
    //sceneMedia->stop();
    //SceneMedia->setMedia(QUrl("qrc:/sound effects/mega-man-2-wily-stage-remix.mp3"));
    //SceneMedia->play();
    connect(BossItem, &Boss::Bossdead,[=](){
        cleanBossAttack();
        //SceneMedia->stop();
        startMusic();
        BossAttackTimer->stop();
        pillarTimer->start(1000);
        enemyTimer->start(3000);
        bonusTimer->start(4500);
        setBossIndex(0);
    });
    connect(BossItem, &Boss::BeginAttack,[=](){
        BossAttackTimer->start(1000);
    });

    addItem(BossItem);
}

void Scene::incrementBonus()
{
    bonus++;
    updateSceneBonus();
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    // vérifier le le boutton presser else if(event->key() == Qt::Key_Escape)
    if(this->getGameState() == GameState::IN_CALLIBRATION) { // ne rien faire
        auto keypressed = event->key();
        if (event->key() == Qt::Key_Space) {
            if (currentProgression != progressBarPhonemes->maximum() && currentPhonemeCallibrationIndex >= 0 && currentPhonemeCallibrationIndex < 4)
            {
                if (fpga->estOk()) 
                {
                    int* echconv = fpga->read4Channel();
                    bool nearPredefined = true; 
                    int filtreDist[4] = { 0,0,0,0 };
                    for (int channel = 0; channel < Phoneme::nombre_channel; channel++)
                    {
                        for (int n = 0; n < Phoneme::nombre_channel; n++)
                        {
                            filtreDist[channel] += (fpga->filtrePredefinedPhone[channel][n] - echconv[n]) * (fpga->filtrePredefinedPhone[channel][n] - echconv[n]);
                        }
                        filtreDist[channel] = sqrt(filtreDist[channel]);
                        if (filtreDist[channel] > 60)
                            nearPredefined = false;
                    }
                    if (nearPredefined)
                    {
                        user.ajoutEnregistrement(echconv, static_cast<User::Phonemes>(currentPhonemeCallibrationIndex));
                        progressBarPhonemes->setValue(++currentProgression);
                    }
                }
                else
                {
                    int* echconv = new int[4]{ 1,1,1,1 };
                    user.ajoutEnregistrement(echconv, static_cast<User::Phonemes>(currentPhonemeCallibrationIndex));
                    progressBarPhonemes->setValue(++currentProgression);
                }
            }
            qDebug() << "IN_CALLIBRATION : key_espace event " << currentProgression << "   => " << phonemesCallibration[currentPhonemeCallibrationIndex][0];
        }
    }
    else if (this->getGameState() == GameState::PLAY) {
        if(event->key() == Qt::Key_Escape){
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
    menuButtons[0]->show();
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

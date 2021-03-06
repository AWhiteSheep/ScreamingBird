#include "birditem.h"
#include "birdattack.h"
#include "scene.h"
#include <QGraphicsScene>


BirdItem::BirdItem(QPixmap pixmap)
    :wingPosition(WingPosition::Up),
     wingDirection(0)
{
    setPixmap(pixmap);

    QTimer * birdWingsTimer = new QTimer(this);
    // listener pour le timer fait une appel à chaque fois le timer complêté
    connect(birdWingsTimer, &QTimer::timeout, [=](){
        updatePixmap();
    });

    birdWingsTimer->start(80);

    // initialisation de l'animation de l'oiseau tomber vers le bas
    groundPosition = scenePos().y() + 290;
    yAnimation = new QPropertyAnimation(this, "y", this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);
    // initialisation de l'animation donnant la rotation
    rotationAnimation = new QPropertyAnimation(this, "rotation", this);

    birdMedia = new QMediaPlayer();
}

BirdItem::~BirdItem()
{
    delete yAnimation;
    delete rotationAnimation;
    delete birdMedia;
}

qreal BirdItem::rotation() const
{
    return m_rotation;
}

qreal BirdItem::y() const
{
    return m_y;
}

void BirdItem::shootUp()
{
    if(birdMedia->state() == QMediaPlayer::PlayingState)
        birdMedia->stop();

    yAnimation->stop();
    rotationAnimation->stop();
    qreal curPosY = y();
    yAnimation->setStartValue(curPosY);
    yAnimation->setEndValue(curPosY - JUMP_HEIGHT);
    yAnimation->setEasingCurve(QEasingCurve::OutQuad);
    yAnimation->setDuration(JUMP_DURATION);
    // lorsque l'animation est terminé débuter l'animation de tomber
    connect(yAnimation, &QPropertyAnimation::finished, [=](){
        fallToGroundIfNecessary();
    });
    yAnimation->start();
    rotateTo(-20, 200, QEasingCurve::OutCubic);

    birdMedia->setMedia(QUrl("qrc:/sound effects/sfx_wing.wav"));
    birdMedia->play();
}

void BirdItem::attack()
{
    flamme = new BirdAttack();
    qDebug() << "flamme created";
    //scene->addItem(flamme);
}

void BirdItem::startFlying()
{
    // start y animation and rotation
    yAnimation->start();
    rotateTo(90, 1200, QEasingCurve::InQuad);
}

void BirdItem::freezeInPlace()
{
    yAnimation->stop();
    rotationAnimation->stop();
}

void BirdItem::setRotation(qreal rotation)
{
    m_rotation = rotation;
    // get the center point of the bird
    QPointF c = boundingRect().center();
    // début de la transformation de l'oiseau
    QTransform t;
    t.translate(c.x(), c.y());
    t.rotate(rotation);
    t.translate(-c.x(),-c.y());
    setTransform(t);
}

void BirdItem::setY(qreal y)
{
    moveBy(0,y-m_y);
    m_y = y;
}

void BirdItem::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);
    rotationAnimation->start();
}

void BirdItem::fallToGroundIfNecessary()
{
    if(y() < groundPosition){
        rotationAnimation->stop();
        //yAnimation->stop();

        yAnimation->setStartValue(y());
        yAnimation->setEndValue(groundPosition);
        yAnimation->setDuration(FALL_SPEED);
        yAnimation->start();

        rotateTo(90, 1100, QEasingCurve::InCubic);
    }
}

// Animation de bird
void BirdItem::updatePixmap()
{
    // vérifier l'état dans lequel
    if(wingPosition == WingPosition::Middle){
        if(wingDirection){
            // UP
            if(color == BirdColor::RED)
                setPixmap(QPixmap(":/images/redbird-upflap.png"));
            else if(color == BirdColor::BLUE)
                setPixmap(QPixmap(":/images/birds/bluebird-upflap-200.png"));
            else if(color == BirdColor::YELLOW)
                setPixmap(QPixmap(":/images/birds/yellowbird-upflap-200.png"));
            wingPosition = WingPosition::Up;
            wingDirection = 0;
        } else {
            // DOWN
            if(color == BirdColor::RED)
                setPixmap(QPixmap(":/images/redbird-downflap.png"));
            else if(color == BirdColor::BLUE)
                setPixmap(QPixmap(":/images/birds/bluebird-downflap-200.png"));
            else if(color == BirdColor::YELLOW)
                setPixmap(QPixmap(":/images/birds/yellowbird-downflap-200.png"));
            wingPosition = WingPosition::Down;
            wingDirection = 1;
        }
    } else {
        if(color == BirdColor::RED)
            setPixmap(QPixmap(":/images/redbird-midflap.png"));
        else if(color == BirdColor::BLUE)
            setPixmap(QPixmap(":/images/birds/bluebird-midflap-200.png"));
        else if(color == BirdColor::YELLOW)
            setPixmap(QPixmap(":/images/birds/yellowbird-midflap-200.png"));
        wingPosition = WingPosition::Middle;
    }
}

void BirdItem::pause()
{
    yAnimation->pause();
    rotationAnimation->pause();
}

void BirdItem::start()
{
    yAnimation->resume();
    rotationAnimation->resume();
}

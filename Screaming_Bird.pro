TEMPLATE = vcapp
TARGET  = ScreamingBird
CONFIG += warn_on qt debug_and_release windows console
QT       += core gui multimedia widgets

SOURCES += \
    Bonus.cpp \
    Boss.cpp \
    BossAttack.cpp \
    BossBoulet.cpp \
    birdattack.cpp \
    birditem.cpp \
    button.cpp \
    enemy.cpp \
    main.cpp \
    pillaritem.cpp \
    scene.cpp \
    widget.cpp \
    CommunicationFPGA.cpp \
    user.cpp \
    phoneme.cpp\
	Instructions.cpp


HEADERS += \
    CommunicationFPGA.h \
    freezable.h \
    Bonus.h \
    Boss.h \
    BossAttack.h \
    BossBoulet.h \
    birdattack.h \
    birditem.h \
    button.h \
    enemy.h \
    pillaritem.h \
    scene.h \
    score.h \
    widget.h \
    user.h \
    phoneme.h\
	Instructions.h

RESOURCES += \
    resource.qrc

DISTFILES += \
    images/pixel-fire-ball.png

LIBS += ./CommunicationFPGA.lib
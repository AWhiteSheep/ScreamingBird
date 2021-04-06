TEMPLATE = vcapp
TARGET  = ScreamingBird
CONFIG += warn_on qt debug_and_release windows console
QT       += core gui multimedia widgets
SOURCES += \
    birdattack.cpp \
    birditem.cpp \
    button.cpp \
    enemy.cpp \
    main.cpp \
    pillaritem.cpp \
    scene.cpp \
    widget.cpp

HEADERS += \
    CommunicationFPGA.h \
    birdattack.h \
    birditem.h \
    button.h \
    enemy.h \
    pillaritem.h \
    scene.h \
    score.h \
    widget.h

RESOURCES += \
    resource.qrc

DISTFILES += \
    images/pixel-fire-ball.png

LIBS += ./CommunicationFPGA.lib


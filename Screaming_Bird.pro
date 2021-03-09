QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

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
    birdattack.h \
    birditem.h \
    button.h \
    enemy.h \
    pillaritem.h \
    scene.h \
    score.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    ../../../../Downloads/pixel-fire-ball.png \
    images/pixel-fire-ball.png

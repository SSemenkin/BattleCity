QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    base.cpp \
    blink.cpp \
    bonusitem.cpp \
    bullet.cpp \
    enemytank.cpp \
    explosion.cpp \
    game.cpp \
    gameover.cpp \
    gamescene.cpp \
    graphicspixmapobject.cpp \
    interface.cpp \
    level.cpp \
    main.cpp \
    menuScene.cpp \
    menutextitem.cpp \
    multimedia.cpp \
    player.cpp \
    score.cpp \
    shield.cpp \
    staticblock.cpp

HEADERS += \
    base.h \
    blink.h \
    bonusitem.h \
    bullet.h \
    enemytank.h \
    explosion.h \
    game.h \
    gameover.h \
    gamescene.h \
    graphicspixmapobject.h \
    interface.h \
    level.h \
    menuScene.h \
    menutextitem.h \
    multimedia.h \
    player.h \
    score.h \
    shield.h \
    staticblock.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc


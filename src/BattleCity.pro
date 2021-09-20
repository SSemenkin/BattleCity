QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    entities/bullet.cpp \
    entities/enemytank.cpp \
    entities/entity.cpp \
    entities/explosion.cpp \
    entities/playertank.cpp \
    entities/rigidbody.cpp \
    entities/staticbody.cpp \
    entities/tank.cpp \
    game.cpp \
    level.cpp \
    main.cpp \
    scenes/gamescene.cpp \
    scenes/menuscene.cpp

HEADERS += \
    entities/bullet.h \
    entities/enemytank.h \
    entities/entity.h \
    entities/explosion.h \
    entities/playertank.h \
    entities/rigidbody.h \
    entities/staticbody.h \
    entities/tank.h \
    game.h \
    level.h \
    scenes/gamescene.h \
    scenes/menuscene.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc



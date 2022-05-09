QT       += core gui network sql
QT       += multimedia
QT       += websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

LIBS += \
    -ldwmapi -lOle32 -lwinmm -lksuser -luuid -lUser32


SOURCES += \
    ExtendWight.cpp \
    ExternVariable.cpp \
    Widget.cpp \
    aboutus.cpp \
    controllabel.cpp \
    controlwidget.cpp \
    dialoglist.cpp \
    ken/RemoteC.cpp \
    ken/VideoC.cpp \
    ken/externwight.cpp \
    ken/form.cpp \
    ken/netcliet.cpp \
    ken/netmanage.cpp \
    ken/se.cpp \
    main.cpp \
    meetinginfor.cpp \
    meetlogin.cpp \
    normal.cpp \
    recvcontrolwidget.cpp \
    rediosetting.cpp \
    settingwidget.cpp \
    sharecontrol.cpp \
    sharewidget.cpp \
    signup.cpp \
    syssetting.cpp \
    videochat.cpp \
    videowidget.cpp

HEADERS += \
    ExtendWight.h \
    ExternVariable.h \
    Widget.h \
    aboutus.h \
    controllabel.h \
    controlwidget.h \
    dialoglist.h \
    ken/RemoteC.h \
    ken/VideoC.h \
    ken/externwight.h \
    ken/form.h \
    ken/netcliet.h \
    ken/netmanage.h \
    ken/se.h \
    meetinginfor.h \
    meetlogin.h \
    normal.h \
    recvcontrolwidget.h \
    rediosetting.h \
    settingwidget.h \
    sharecontrol.h \
    sharewidget.h \
    signup.h \
    syssetting.h \
    videochat.h \
    videowidget.h

FORMS += \
    Widget.ui \
    aboutus.ui \
    controlwidget.ui \
    dialoglist.ui \
    meetinginfor.ui \
    meetlogin.ui \
    recvcontrolwidget.ui \
    rediosetting.ui \
    settingwidget.ui \
    sharecontrol.ui \
    sharewidget.ui \
    signup.ui \
    syssetting.ui \
    videochat.ui \
    videowidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

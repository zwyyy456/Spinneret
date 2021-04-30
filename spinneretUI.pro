QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Ant.cpp \
    Common.cpp \
    advmot.cpp \
    antpath.cpp \
    main.cpp \
    mainwindow.cpp \
    vision.cpp

HEADERS += \
    Ant.h \
    Common.h \
    StdAfx.h \
    advmot.h \
    antpath.h \
    include/AdvMotApi.h \
    include/AdvMotDev.h \
    include/AdvMotDrv.h \
    include/AdvMotErr.h \
    include/AdvMotPropID.h \
    include/vision.h \
    mainwindow.h \
    include/GigECamera_Types.h \
    include/MVCamProptySheet.h \
    include/MVGigE.h \
    include/MVImage.h \
    include/MVImageC.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += C:/opencv/build/include \
               C:/opencv/build/include/opencv2 \

RESOURCES += \
    icon.qrc

DESTDIR = $$PWD/bin/QTBin/MSVC

win32: LIBS += -L$$PWD/lib/ -lMVTickDlg

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/MVTickDlg.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/libMVTickDlg.a

win32: LIBS += -L$$PWD/lib/ -lMVGigE

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/MVGigE.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/libMVGigE.a

win32: LIBS += -L$$PWD/lib/ -lMVCamProptySheet

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/MVCamProptySheet.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/libMVCamProptySheet.a

#opencv
LIBS += C:/opencv/build/x64/vc15/lib/opencv_world451.lib
LIBS += C:/opencv/build/x64/vc15/lib/opencv_world451d.lib



win32: LIBS += -L$$PWD/lib/ -lADVMOT

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/ADVMOT.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/libADVMOT.a

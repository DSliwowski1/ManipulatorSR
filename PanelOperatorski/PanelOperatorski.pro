QT       += core gui serialport charts opengl 3drender 3dcore 3dextras

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

TARGET = myViewer
CONFIG *= qt opengl release
QT *= opengl xml

# Windows
INCLUDEPATH *= C:\Users\sliwa\Desktop\wds\GLViewer\libQGLViewer-2.7.2
LIBS *= -LC:\Users\sliwa\Desktop\wds\GLViewer\libQGLViewer-2.7.2\QGLViewer -lQGLViewer2

INCLUDEPATH *= C:\Users\sliwa\Desktop\wds\asspimp\
LIBS *= -LC:\Users\sliwa\Desktop\wds\asspimp\lib -lassimp-vc142-mt

INCLUDEPATH *= C:\Users\sliwa\Desktop\wds\glm\glm\glm

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    manipulator.cpp \
    polaczenia.cpp \
    viewer.cpp

HEADERS += \
    CRC.h \
    LoadOBJ.h \
    mainwindow.h \
    manipulator.h \
    polaczenia.h \
    viewer.h

FORMS += \
    mainwindow.ui \
    polaczenia.ui

LIBS += -lopengl32

RESOURCES += \
    zasoby.qrc


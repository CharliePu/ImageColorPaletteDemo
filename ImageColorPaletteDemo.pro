QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    color.cpp \
    image.cpp \
    kmeansmethod.cpp \
    main.cpp \
    mainwindow.cpp \
    mediancutmethod.cpp \
    octreequantizationmethod.cpp \
    quantizationmethod.cpp \
    uniformquantizationmethod.cpp

HEADERS += \
    color.h \
    image.h \
    kmeansmethod.h \
    mainwindow.h \
    mediancutmethod.h \
    octreequantizationmethod.h \
    quantizationmethod.h \
    uniformquantizationmethod.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

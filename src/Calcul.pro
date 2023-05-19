QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/View/graph.cc \
    ../src/plot/qcustomplot.cpp \
    ../src/View/main.cc \
    ../src/View/mainwindow.cc \
    ../src/Model/calculator.cc \
    ../src/Model/credit_calc.cc \
    ../src/Controller/controller.cc

HEADERS += \
    ../src/Model/errors.h \
    ../src/View/graph.h \
    ../src/plot/qcustomplot.h \
    ../src/View/mainwindow.h \
    ../src/Model/calculator.h \
    ../src/Model/credit_calc.h \
    ../src/Controller/controller.h \
    ../src/constants.h

FORMS += \
    ../src/View/graph.ui \
    ../src/View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

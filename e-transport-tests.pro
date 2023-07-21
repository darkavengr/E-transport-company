QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_LIBS=-lcrypt -lboost_unit_test_framework

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH = headers headers/UserInterface

SOURCES += \
    src/cargoowner.cpp \
    src/database.cpp \
    src/driver.cpp \
    src/exception.cpp \
    src/main.cpp \
    src/transaction.cpp \
    src/transportationcompany.cpp \
    src/user.cpp \
    src/userinterface/MainWindow.cpp \
    src/userinterface/cargoowneruihelper.cpp \
    src/userinterface/driveruihelper.cpp \
    src/userinterface/transportcompanyuihelper.cpp \
    src/vehicle.cpp
    tests/et-tests.cpp

HEADERS += \   
    headers/UserInterface/MainWindow.h \
    headers/UserInterface/MessageInterface.h \
    headers/UserInterface/signin.h \
    headers/cargoowner.h \
    headers/database.h \
    headers/driver.h \
    headers/exception.h \
    headers/file_path.h \
    headers/filelocations.h \
    headers/main.h \
    headers/transaction.h \
    headers/transportationcompany.h \
    headers/user.h \
    headers/vehicle.h \
    headers/UserInterface/driveruihelper.h \
    headers/UserInterface/transportcompanyuihelper.h \
    headers/UserInterface/cargoowneruihelper.h

FORMS += \
    ui/MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

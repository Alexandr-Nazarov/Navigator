QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
#CONFIG -=debug_and_release debug_and_release_target        из 1й лабы отключить сборки
#DESTDIR= ./exe  #windeployqt для развертывания (конец лаб_1)

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TRANSLATIONS +=Navigator_ru.ts

SOURCES += \
    main.cpp \
    my_scene.cpp \
    my_size.cpp \
    my_way.cpp \
    mytableview.cpp \
    navogator.cpp \
    tablemodel.cpp

HEADERS += \
    my_scene.h \
    my_size.h \
    my_way.h \
    mytableview.h \
    navogator.h \
    tablemodel.h

FORMS += \
    navogator.ui




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Navigator_ru.ts

RESOURCES += \
    MyImages.qrc



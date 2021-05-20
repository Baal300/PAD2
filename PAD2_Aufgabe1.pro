TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        database.cpp \
        main.cpp \
        mediafile.cpp \
        movie.cpp \
        series.cpp

HEADERS += \
    database.h \
    mediafile.h \
    movie.h \
    series.h

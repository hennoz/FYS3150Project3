TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    celestialbody.cpp \
    vec3.cpp \
    solver.cpp

HEADERS += \
    celestialbody.h \
    vec3.h \
    solver.h

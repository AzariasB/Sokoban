
QT              -= gui core
CONFIG          += c++17
QMAKE_CXXFLAGS  += -std=c++17

SOURCES += src/main.cpp \
            src/Map.cpp \
            src/State.cpp

HEADERS += src/Map.h \
           src/State.hpp

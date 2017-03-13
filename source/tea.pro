CONFIG += c++14
QT -= gui

CONFIG += console
CONFIG -= app_bundle

SOURCES += \
    main.cpp \
    template/codetemplate.cpp \
    template/codetemplatecomponent.cpp \
    rom/rom.cpp \
    rom/romref.cpp \
    rom/romutil.cpp \
    code/code.cpp \
    codetemplatelibrary.cpp \
    valuelibrary.cpp \
    value/value.cpp \
    lang/expression/abstractexpression.cpp \
    lang/expression/codeexpression.cpp \
    lang/expression/valueexpression.cpp \
    lang/expression/labelexpression.cpp \
    lang/expression/numberexpression.cpp \
    decompiler/codedisassembler.cpp \
    lang/expression/orgexpression.cpp \
    lang/print/printhint.cpp

HEADERS += \
    template/codetemplate.h \
    template/codetemplatecomponent.h \
    rom/rom.h \
    rom/romref.h \
    rom/romutil.h \
    code/code.h \
    codetemplatelibrary.h \
    valuelibrary.h \
    value/value.h \
    lang/expression/abstractexpression.h \
    lang/expression/codeexpression.h \
    lang/expression/valueexpression.h \
    lang/expression/labelexpression.h \
    lang/expression/numberexpression.h \
    decompiler/codedisassembler.h \
    lang/expression/orgexpression.h \
    lang/print/printhint.h

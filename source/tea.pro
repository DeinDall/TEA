CONFIG += c++14
QT -= gui

CONFIG += console
CONFIG -= app_bundle

SOURCES += \
    main.cpp \
    core/rom/rom.cpp \
    core/rom/romref.cpp \
    core/rom/romutil.cpp \
    core/rom/romwriter.cpp \
    lang/core/code/codetemplate.cpp \
    lang/core/code/codetemplatecomponent.cpp \
    lang/core/code/code.cpp \
    lang/codetemplatelibrary.cpp \
    lang/core/value/value.cpp \
    lang/valuelibrary.cpp \
    lang/core/expression/abstractexpression.cpp \
    lang/core/expression/codeexpression.cpp \
    lang/core/expression/valueexpression.cpp \
    lang/core/expression/labelexpression.cpp \
    lang/core/expression/numberexpression.cpp \
    lang/core/expression/orgexpression.cpp \
    lang/disassembler/codedisassembler.cpp \
    lang/print/printhint.cpp \
    lang/lexer/lexer.cpp \
    lang/parser/parser.cpp \
    lang/assembler/codeassembler.cpp \
    lang/core/keywords.cpp \
    lang/assembler/assemblervalue.cpp

HEADERS += \
    core/rom/rom.h \
    core/rom/romref.h \
    core/rom/romutil.h \
    core/rom/romwriter.h \
    lang/core/code/codetemplate.h \
    lang/core/code/codetemplatecomponent.h \
    lang/core/code/code.h \
    lang/codetemplatelibrary.h \
    lang/core/value/value.h \
    lang/valuelibrary.h \
    lang/core/expression/abstractexpression.h \
    lang/core/expression/codeexpression.h \
    lang/core/expression/valueexpression.h \
    lang/core/expression/labelexpression.h \
    lang/core/expression/numberexpression.h \
    lang/core/expression/orgexpression.h \
    lang/disassembler/codedisassembler.h \
    lang/print/printhint.h \
    lang/lexer/lexer.h \
    lang/core/token.h \
    lang/parser/parser.h \
    lang/assembler/codeassembler.h \
    lang/core/keywords.h \
    lang/assembler/assemblervalue.h

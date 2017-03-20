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
    lang/core/value/value.cpp \
    lang/valuelibrary.cpp \
    lang/core/expression/abstractexpression.cpp \
    lang/core/expression/valueexpression.cpp \
    lang/core/expression/numberexpression.cpp \
    lang/disassembler/codedisassembler.cpp \
    lang/print/printhint.cpp \
    lang/lexer/lexer.cpp \
    lang/parser/parser.cpp \
    lang/assembler/codeassembler.cpp \
    lang/core/keywords.cpp \
    lang/disassembler/disassemblerstate.cpp \
    lang/core/code/codeparametertype.cpp \
    lang/core/statement/abstractstatement.cpp \
    lang/core/statement/codestatement.cpp \
    lang/core/statement/orgstatement.cpp \
    lang/core/statement/labelstatement.cpp \
    lang/print/statementprinter.cpp \
    lang/core/token.cpp \
    lang/core/expression/tupleexpression.cpp \
    lang/parser/parselet/startparselet.cpp \
    lang/parser/parselet/numberparselet.cpp \
    lang/parser/parselet/valueparselet.cpp \
    lang/parser/parselet/nextparselet.cpp \
    lang/parser/parselet/tupleparselet.cpp \
    assemblercontroller.cpp \
    lang/preprocessor/preprocessor.cpp \
    lang/library/codelibrary.cpp

HEADERS += \
    core/rom/rom.h \
    core/rom/romref.h \
    core/rom/romutil.h \
    core/rom/romwriter.h \
    lang/core/code/codetemplate.h \
    lang/core/value/value.h \
    lang/valuelibrary.h \
    lang/core/expression/abstractexpression.h \
    lang/core/expression/valueexpression.h \
    lang/core/expression/numberexpression.h \
    lang/disassembler/codedisassembler.h \
    lang/print/printhint.h \
    lang/lexer/lexer.h \
    lang/core/token.h \
    lang/parser/parser.h \
    lang/assembler/codeassembler.h \
    lang/core/keywords.h \
    lang/disassembler/disassemblerstate.h \
    lang/core/code/codeparametertype.h \
    lang/core/statement/abstractstatement.h \
    lang/core/statement/codestatement.h \
    lang/core/statement/orgstatement.h \
    lang/core/statement/labelstatement.h \
    lang/print/statementprinter.h \
    lang/core/expression/tupleexpression.h \
    lang/parser/parselet/startparselet.h \
    lang/parser/parselet/numberparselet.h \
    lang/parser/parselet/valueparselet.h \
    lang/parser/parselet/nextparselet.h \
    lang/parser/parselet/tupleparselet.h \
    assemblercontroller.h \
    lang/preprocessor/preprocessor.h \
    lang/library/codelibrary.h

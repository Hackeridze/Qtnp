#-------------------------------------------------
#
# Project created by QtCreator 2011-10-04T22:55:22
#
#-------------------------------------------------

QT       += core gui

TARGET = Qtnp
TEMPLATE = app


SOURCES += main.cpp\
        qtnp.cpp \
    QtnpColorWidget.cpp \
    QtnpImage.cpp \
    QtnpNewFileDialog.cpp \
    QtnpAddGridDialog.cpp \
    QtnpGridAndCoordPlane.cpp \
    fparser/muparser/muParserTokenReader.cpp \
    fparser/muparser/muParserTest.cpp \
    fparser/muparser/muParserInt.cpp \
    fparser/muparser/muParserError.cpp \
    fparser/muparser/muParserDLL.cpp \
    fparser/muparser/muParserCallback.cpp \
    fparser/muparser/muParserBytecode.cpp \
    fparser/muparser/muParserBase.cpp \
    fparser/muparser/muParser.cpp \
    fparser/fparser.cpp \
    QtnpGraphicDialog.cpp \
    QtnpMenuWidget.cpp

HEADERS  += qtnp.h\
    QtnpColorWidget.h \
    QtnpTool.h \
    QtnpImage.h \
    QtnpNewFileDialog.h \
    QtnpAddGridDialog.h \
    QtnpGridAndCoordPlane.h \
    fparser/muparser/muParserTokenReader.h \
    fparser/muparser/muParserToken.h \
    fparser/muparser/muParserTest.h \
    fparser/muparser/muParserTemplateMagic.h \
    fparser/muparser/muParserStack.h \
    fparser/muparser/muParserInt.h \
    fparser/muparser/muParserFixes.h \
    fparser/muparser/muParserError.h \
    fparser/muparser/muParserDLL.h \
    fparser/muparser/muParserDef.h \
    fparser/muparser/muParserCallback.h \
    fparser/muparser/muParserBytecode.h \
    fparser/muparser/muParserBase.h \
    fparser/muparser/muParser.h \
    fparser/fparser.h \
    QtnpGraphicDialog.h \
    QtnpMenuWidget.h

FORMS += \
    qtnp.ui \
    QtnpNewFileDialog.ui \
    QtnpAddGridDialog.ui \
    QtnpGridAndCoordPlane.ui \
    QtnpGraphicDialog.ui

RESOURCES += \
    res.qrc

TRANSLATIONS = qtnp_ru.ts\
	qtnp_az.ts\
	qtnp_de.ts\
	qtnp_kz.ts\
        qtnp_be.ts\
        qtnp_en.ts

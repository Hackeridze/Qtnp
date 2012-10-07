#-------------------------------------------------
#
# Project created by QtCreator 2011-10-04T22:55:22
#
#-------------------------------------------------

QT  += core gui

TARGET = Qtnp
TEMPLATE = app


SOURCES += main.cpp \
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
    QtnpMenuWidget.cpp \
    digital_clock.cpp

HEADERS  += qtnp.h \
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
    QtnpMenuWidget.h \
    digital_clock.h

FORMS += \
    qtnp.ui \
    QtnpNewFileDialog.ui \
    QtnpAddGridDialog.ui \
    QtnpGridAndCoordPlane.ui \
    QtnpGraphicDialog.ui

RESOURCES += \
    res.qrc

TRANSLATIONS = qtnp_ru.ts\
    qtnp_en.ts

OTHER_FILES += \
    res/template.png \
    res/splash.png \
    res/save.png \
    res/save_as.png \
    res/qtnp_ru.qm \
    res/qtnp_en.qm \
    res/prev.png \
    res/pencil.png \
    res/pencil_ico.png \
    res/open.png \
    res/next.png \
    res/new.png \
    res/line.png \
    res/line_ico.png \
    res/jogged.png \
    res/jogged_ico.png \
    res/grid.png \
    res/graphic.png \
    res/fullscreen.png \
    res/exit.png \
    res/cursor.png \
    res/circle.png \
    res/change_pens_ico.png \
    res/about.png \
    VERSION \
    res/GNU_GPLv3_Logo.png

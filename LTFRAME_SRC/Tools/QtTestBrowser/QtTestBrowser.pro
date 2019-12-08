# -------------------------------------------------------------------
# Project file for the QtTestBrowser binary
#
# See 'Tools/qmake/README' for an overview of the build system
# -------------------------------------------------------------------

TEMPLATE = app

INCLUDEPATH += \
    $${ROOT_WEBKIT_DIR}/Source/WebKit/qt/WebCoreSupport \
    $${ROOT_WEBKIT_DIR}/Tools/DumpRenderTree/qt/ \

load(features)

SOURCES += \
    $${ROOT_WEBKIT_DIR}/Tools/DumpRenderTree/qt/QtInitializeTestFonts.cpp \
    locationedit.cpp \
    launcherwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    urlloader.cpp \
    utils.cpp \
    webpage.cpp \
    webview.cpp \
    fpstimer.cpp \
    cookiejar.cpp

HEADERS += \
    $${ROOT_WEBKIT_DIR}/Tools/DumpRenderTree/qt/QtInitializeTestFonts.h \
    locationedit.h \
    launcherwindow.h \
    mainwindow.h \
    urlloader.h \
    utils.h \
    webinspector.h \
    webpage.h \
    webview.h \
    fpstimer.h \
    cookiejar.h


WEBKIT += webcore

CONFIG += qtwebkit

DESTDIR = $$ROOT_BUILD_DIR/bin

QT += network

macx:QT += xml
haveQt(5): QT += printsupport widgets

contains(DEFINES, HAVE_FONTCONFIG=1): PKGCONFIG += fontconfig

contains(QT_CONFIG, opengl): QT += opengl

RESOURCES += \
    QtTestBrowser.qrc

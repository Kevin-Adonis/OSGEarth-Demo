#-------------------------------------------------
#
# Project created by QtCreator 2019-12-15T19:50:56
#
#-------------------------------------------------

QT       += core gui xml sql svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl

TARGET = map
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

INCLUDEPATH += \
                $$(OSG_3RPARTY_DIR)/include \
                $$(OSG_DIR)/include \
                $$(OSGEARTH_DIR)/include

LIBS += \
    -L$$(OSG_3RPARTY_DIR)/lib \
        -lfreetyped -lgdal_i -lgeos -lgeos_cd -lgeosd -lglut32 -ljpeg -llibcurl_imp -llibgeosd \
        -llibpng16 -llibpng16_staticd -llibpng16d -logr -lproj_4_9_d -ltiffd -lzlibd -lzlibstaticd \
    -L$$(OSGEARTH_DIR)/lib \
        -losgEarthd -losgEarthAnnotationd -losgEarthFeaturesd -losgEarthQt5d -losgEarthSplatd -losgEarthSymbologyd -losgEarthUtild \
    -L$$(OSG_DIR)/lib \
        -lOpenThreadsd -losgd -lOsgAnimationd -losgDBd -losgFXd -losgGAd -losgManipulatord -losgParticled -losgPresentationd \
        -losgQt5d -losgShadowd -losgSimd -losgTerraind -losgTextd -losgUId -losgUtild -losgViewerd -losgVolumed -losgWidgetd

HEADERS += \
        map_osg/map_osg_baseviewer.h \
        map_osg/map_osg_examplewindow.h \
    map_osg/map_osg_layercontrolwidget.h \
        map_osg/map_osg_viewcontroller.h \
    map_dlg/map_dlg_createproject.h \
    map_dlg/map_dlg_dialogfactory.h \
    map_gui/map_gui_mainwindow.h \
    map_controller/map_controller_mainwindowcontroller.h \
    map_controller/map_controller_templatecontroller.h \
    map_globaldata/map_globaldata_appdata.h \
    map_gui/map_gui_entityinfoview.h \
    map_gui/map_gui_currentinfoview.h \
    map_gui/map_gui_showview.h \
    map_gui/map_gui_dockwidgettitlebar.h \
    map_dlg/map_dlg_templatedialog.h \
    map_gui/map_gui_titlebar.h

SOURCES += \
        map_main/main.cpp \
        map_osg/map_osg_baseviewer.cpp \
        map_osg/map_osg_examplewindow.cpp \
    map_osg/map_osg_layercontrolwidget.cpp \
        map_osg/map_osg_viewcontroller.cpp \
    map_dlg/map_dlg_createproject.cpp \
    map_dlg/map_dlg_dialogfactory.cpp \
    map_gui/map_gui_mainwindow.cpp \
    map_controller/map_controller_mainwindowcontroller.cpp \
    map_controller/map_controller_templatecontroller.cpp \
    map_globaldata/map_globaldata_appdata.cpp \
    map_gui/map_gui_entityinfoview.cpp \
    map_gui/map_gui_currentinfoview.cpp \
    map_gui/map_gui_showview.cpp \
    map_gui/map_gui_dockwidgettitlebar.cpp \
    map_dlg/map_dlg_templatedialog.cpp \
    map_gui/map_gui_titlebar.cpp

FORMS += \
        map_osg/map_osg_examplewindow.ui \
    map_dlg/map_dlg_createproject.ui \
    map_gui/map_gui_mainwindow.ui \
    map_gui/map_gui_entityinfoview.ui \
    map_gui/map_gui_currentinfoview.ui \
    map_gui/map_gui_showview.ui \
    map_gui/map_gui_dockwidgettitlebar.ui \
    map_dlg/map_dlg_templatedialog.ui \
    map_gui/map_gui_titlebar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

# 禁止“未引用的形参”这一警告
win32-msvc* {
    QMAKE_CXXFLAGS *=  /wd"4100"
    contains (QMAKE_CXXFLAGS_WARN_ON, -w34100) : QMAKE_CXXFLAGS_WARN_ON -= -w34100
}

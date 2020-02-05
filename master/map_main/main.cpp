#include "mainwindow.h"
#include <QApplication>

#include "map_osg/map_osg_examplewindow.h"
#include "map_gui/map_gui_mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //MAP_OSG_ExampleWindow w;
    //w.show();
    QFont font("Microsoft Yahei", 11);
    a.setFont(font);

    MAP_GUI_MainWindow *b = MAP_GUI_MainWindow::getInstance();
    b->show();

    return a.exec();
}

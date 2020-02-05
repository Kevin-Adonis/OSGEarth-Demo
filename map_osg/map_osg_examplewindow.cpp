#include "map_osg_examplewindow.h"
#include "ui_map_osg_examplewindow.h"

MAP_OSG_ExampleWindow::MAP_OSG_ExampleWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MAP_OSG_ExampleWindow)
{
    ui->setupUi(this);
    m_osgWidget = MAP_OSG_ViewController::addView(qApp->applicationDirPath() + QString("/example_data/base.earth"));
    setCentralWidget(m_osgWidget);
}

MAP_OSG_ExampleWindow::~MAP_OSG_ExampleWindow()
{
    MAP_OSG_ViewController::removeView(m_osgWidget);
}

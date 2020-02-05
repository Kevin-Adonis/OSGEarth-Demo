#ifndef MAP_OSG_EXAMPLEWINDOW_H
#define MAP_OSG_EXAMPLEWINDOW_H

/// MAP_OSG_ExampleWindow
/// 使用MAP_OSG_ViewController和MAP_OSG_BaseViewer加载地图的示例窗口。
/// 使用该示例，需将example_data放在编译目录下，
/// 并注释掉main.cpp中的MainWindow w;然后取消注释#include "map_osg/map_osg_examplewindow.h"和MAP_OSG_ExampleWindow w;。

#include <QMainWindow>
#include <QLayout>

#include "map_osg_viewcontroller.h"

namespace Ui {
    class MAP_OSG_ExampleWindow;
}

class MAP_OSG_ExampleWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MAP_OSG_ExampleWindow(QWidget *parent = nullptr);
    ~MAP_OSG_ExampleWindow();

signals:

public slots:

private:
    MAP_OSG_BaseViewer *m_osgWidget;
    Ui::MAP_OSG_ExampleWindow *ui;
};

#endif // MAP_OSG_EXAMPLEWINDOW_H

#ifndef MAP_OSG_LAYERCONTROLWIDGET_H
#define MAP_OSG_LAYERCONTROLWIDGET_H

#include <QWidget>

class MAP_OSG_BaseViewer;
#ifndef MAP_OSG_BASEVIEWER_H
#include "map_osg_baseviewer.h"
#endif

class MAP_OSG_LayerControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MAP_OSG_LayerControlWidget(MAP_OSG_BaseViewer *viewer, QWidget *parent = nullptr);
    ~MAP_OSG_LayerControlWidget();

public slots:
    void checkBoxStateChange(bool enabled);

private:
    MAP_OSG_BaseViewer *m_viewer;
};

#endif // MAP_OSG_LAYERCONTROLWIDGET_H

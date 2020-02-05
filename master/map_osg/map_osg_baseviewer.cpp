﻿#include "map_osg_baseviewer.h"

MAP_OSG_BaseViewer::MAP_OSG_BaseViewer(osgViewer::View *view, osg::GraphicsContext *gcToShare) :
    osgEarth::QtGui::ViewWidget(view, gcToShare), m_controller(nullptr)
{

}

MAP_OSG_BaseViewer::MAP_OSG_BaseViewer(osgViewer::View *view, const QGLFormat &format) :
    osgEarth::QtGui::ViewWidget(view, format), m_controller(nullptr)
{

}

MAP_OSG_BaseViewer::~MAP_OSG_BaseViewer()
{

}

void MAP_OSG_BaseViewer::setControllWidget(MAP_OSG_LayerControlWidget *controller)
{
    m_controller = controller;
}

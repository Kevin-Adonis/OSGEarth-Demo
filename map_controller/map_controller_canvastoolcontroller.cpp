#include "map_controller_canvastoolcontroller.h"
#include <map_globaldata/map_globaldata_appdata.h>
#include <osg/Camera>
#include <osgEarthSymbology/Common>

MAP_CONTROLLER_CanvasToolController::MAP_CONTROLLER_CanvasToolController()
    : m_colors{osg::Vec4(1,1,1,1), osg::Vec4(1,0,0,1), osg::Vec4(1,1,0,1), osg::Vec4(0,1,0,1) }
{
    m_bLatLongGrid = true;
    m_pLatLongGridLayer = nullptr;
    m_gridColorIndex = 0;
}

void MAP_CONTROLLER_CanvasToolController::switchLatLongGrid()
{
    if(!m_pLatLongGridLayer)
    {
        m_pLatLongGridLayer = new  osgEarth::Util::GeodeticGraticule();
        auto l_map = MAP_GLOBALDATA_APPData::getInstance()->g_mapData->pMap;
        auto l_view = MAP_GLOBALDATA_APPData::getInstance()->g_mapData->pView;

        l_map->addLayer(m_pLatLongGridLayer);
        m_fSmallFeatureCullingPixelSize = l_view->getCamera()->getSmallFeatureCullingPixelSize();
        m_fNearFarRatio = l_view->getCamera()->getNearFarRatio();
        l_view->getCamera()->setSmallFeatureCullingPixelSize(-1.0f);
        l_view->getCamera()->setNearFarRatio(0.0001);
    }
    m_pLatLongGridLayer->setEnabled(m_bLatLongGrid);
    m_bLatLongGrid = !m_bLatLongGrid;
//    changeLatLongGridStyle();
}

void MAP_CONTROLLER_CanvasToolController::removeLatLongGrid()
{
    if(!m_pLatLongGridLayer)
        return;
    auto l_map = MAP_GLOBALDATA_APPData::getInstance()->g_mapData->pMap;
    auto l_view = MAP_GLOBALDATA_APPData::getInstance()->g_mapData->pView;

    l_map->removeLayer(m_pLatLongGridLayer);
    l_view->getCamera()->setSmallFeatureCullingPixelSize(m_fSmallFeatureCullingPixelSize);
    l_view->getCamera()->setNearFarRatio(m_fNearFarRatio);
    m_pLatLongGridLayer = nullptr;
}

void MAP_CONTROLLER_CanvasToolController::changeLatLongGridStyle()
{
    if(!m_pLatLongGridLayer)
        return;
    // Could also use the get/setGridLabelStyle API here, but this demonstrates
    // changing the options and calling dirty() or apply().
    osgEarth::Symbology::Style gridLabelStyle = m_pLatLongGridLayer->options().gridLabelStyle().get();
    m_gridColorIndex = (m_gridColorIndex+1)%4;
    gridLabelStyle.getOrCreate<osgEarth::Symbology::TextSymbol>()->fill()->color() = m_colors[m_gridColorIndex];
    m_pLatLongGridLayer->options().gridLabelStyle() = gridLabelStyle;

    m_pLatLongGridLayer->dirty();
}

#ifndef MAP_CONTROLLER_CANVASTOOLCONTROLLER_H
#define MAP_CONTROLLER_CANVASTOOLCONTROLLER_H

#include "map_controller/map_controller_templatecontroller.h"
#include <osgEarthUtil/GeodeticGraticule>


class MAP_CONTROLLER_CanvasToolController : public MAP_CONTROLLER_TemplateController
{
public:
    MAP_CONTROLLER_CanvasToolController();
    /**
     * @brief switchLatLongGrid
     * 用于切换显示经纬网络
     */
    void switchLatLongGrid();
    /**
     * @brief removeLatLongGrid
     * 删除经纬网络，并清空相关的设置参数
     */
    void removeLatLongGrid();
    /**
     * @brief changeLatLongGridStyle
     * 更改经纬网络显示样式；
     * 可进一步拆分几个子函数分别控制颜色、线宽、数量等。
     */
    void changeLatLongGridStyle();

private:
    //经纬网络相关
    bool m_bLatLongGrid;
    osgEarth::Util::GeodeticGraticule* m_pLatLongGridLayer;
    float m_fSmallFeatureCullingPixelSize;
    float m_fNearFarRatio;
    const osg::Vec4 m_colors[4];
    int m_gridColorIndex;

};

#endif // MAP_CONTROLLER_CANVASTOOLCONTROLLER_H

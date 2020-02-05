#ifndef MAP_GLOBALDATA_APPDATA_H
#define MAP_GLOBALDATA_APPDATA_H

#include <QObject>
#include <osgViewer/View>
#include <osgEarth/MapNode>
#include <osgEarth/SpatialReference>
#include <osgEarthUtil/EarthManipulator>

#include "map_controller/map_controller_mainwindowcontroller.h"
#include "map_controller/map_controller_primitiveconfigcontroller.h"
#include "map_controller/map_controller_canvastoolcontroller.h"
#include "map_osg/map_osg_basehandler.h"
#include "map_controller/map_controller_svgcontroller.h"
#include "../map_osg/map_osg_baseviewer.h"
#include "map_gr/map_gr_dis.h"
/**
 * @brief The MAP_GLOBALDATA_APPData class
 * 全局使用到的数据在该类中进行交互；
 * 该类为单一实例类
 */
class MAP_GLOBALDATA_APPData
{
public:
    /**
     * @brief The DrawingPrimitiveMode enum
     * 用于记录图元的绘制的样式，包括：
     * 点、线...
     * 主要应用于mainwindow以及控制器之间传递图元信息
     * 获取：
     * MAP_GLOBALDATA_APPData::getInstance()->primitiveMode;
     */
    enum DrawingPrimitiveMode
    {
        POINT, LINE
    };
    DrawingPrimitiveMode g_primitiveMode;

    /**
     * @brief The osgMapData struct
     * 储存了所有osg地图的数据，它们默认会在初始化时储存进去。
     * 使用前先判定一下valid是否有效。
     * 使用方法：
     * MAP_GLOBALDATA_APPData::getInstance()->g_mapData;
     * 比如获取mapNode：
     * if(MAP_GLOBALDATA_APPData::getInstance()->g_mapData->valid)
     *      auto mapNode = MAP_GLOBALDATA_APPData::getInstance()->g_mapData->pMapNode;
     */
    struct osgMapData
    {
        bool valid;
        osgEarth::Map *pMap;
        osgEarth::MapNode *pMapNode;
        osgViewer::View *pView;
        osgEarth::Util::EarthManipulator *pEarthManipulator;
        /**
         * @brief pHandler
         * 通过该指针可获取事件中捕获的数据，如世界坐标值等；
         * 参见该头文件
         * @see
         * map_osg/map_osg_basehandler.h
         * 使用前请判定是否为nullptr
         */
        MAP_OSG_BaseHandler *pHandler;
        const osgEarth::SpatialReference *pMapSRS;
    };
    const osgMapData* g_mapData;
    /**
     * @brief g_rootNode
     * osg模型的根节点，
     * earth属于它的子节点。
     * 要在地图上添加部分模型时必须用到（如指南针）。
     */
    osg::ref_ptr<osg::Group> g_rootNode;

    /**
     * @brief g_osgWidget
     * OSG的承载控件。
     * 注意，该类为ui控件，请尽量不要使用该类的接口！
     */
    const MAP_OSG_BaseViewer *g_osgWidget;

    static MAP_GLOBALDATA_APPData *getInstance();
private:
    MAP_GLOBALDATA_APPData();

    static MAP_GLOBALDATA_APPData *m_instance;

};


/**
 * @brief The MAP_GLOBALDATA_Controller class
 * 该类用于包含各个controller类的全局实例，设置为全局属性的主要原因是考虑各个controller之间的通信
 * 进一步也是两个窗口或者两个部件之间的通信，考虑通过controller进而影响界面的变化
 * 涉及属性的变化进而导致界面更新的建议通过controller之间去连接信号与槽
 */
class MAP_GLOBALDATA_Controller : public QObject
{
    Q_OBJECT

public:
    MAP_GLOBALDATA_Controller();

public:
    static MAP_CONTROLLER_MainWindowController *mainWindowController;
    static MAP_CONTROLLER_EntityViewController *entityViewController;
    static MAP_CONTROLLER_CurrentInfoViewController *currInfoViewController;
    static MAP_CONTROLLER_ShowViewController *showViewController;
    static MAP_CONTROLLER_PrimitiveConfigController *primitiveConfigController;
    static MAP_CONTROLLER_CanvasToolController *canvasToolController;
    static MAP_CONTROLLER_SVGController *svgController;


};
#endif // MAP_GLOBALDATA_APPDATA_H

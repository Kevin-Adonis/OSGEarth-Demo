#include "map_osg_viewcontroller.h"
#include "map_osg/map_osg_basehandler.h"
#include "map_osg/map_osg_basehandler.h"
#include "map_globaldata/map_globaldata_appdata.h"
#include <QDebug>
#include <osgEarth/SpatialReference>
#include <osgEarthUtil/Controls>
#include <osgEarthUtil/MouseCoordsTool>

MAP_OSG_ViewController *MAP_OSG_ViewController::m_instance = nullptr;

MAP_OSG_ViewController::MAP_OSG_ViewController()
{
    m_instance = this;
    m_viewer.setThreadingModel(m_viewer.SingleThreaded);

    //关闭自带的esc退出事件
    m_viewer.setKeyEventSetsDone(0);
    connect(&m_timer, &QTimer::timeout, this, &MAP_OSG_ViewController::paint);
    m_timer.start(20);
}

void MAP_OSG_ViewController::initGlobalData()
{
    auto l_pCurrView = m_instance->m_viewer.getView(0);
    if(l_pCurrView)
    {
        MAP_GLOBALDATA_APPData::osgMapData *mapData = new MAP_GLOBALDATA_APPData::osgMapData;
        mapData->valid = true;
        mapData->pView = l_pCurrView;
        mapData->pMapNode = osgEarth::MapNode::get(l_pCurrView->getSceneData());
        mapData->pEarthManipulator = dynamic_cast<osgEarth::Util::EarthManipulator*>(
                                         l_pCurrView->getCameraManipulator());
        mapData->pMap = mapData->pMapNode->getMap();
        mapData->pMapSRS = mapData->pMap->getSRS();
        auto l_pHandlerTemp = *(mapData->pView->getEventHandlers().begin());
        mapData->pHandler = dynamic_cast<MAP_OSG_BaseHandler*>(l_pHandlerTemp.get());
        MAP_GLOBALDATA_APPData::getInstance()->g_mapData = mapData;
    }
}

void MAP_OSG_ViewController::initView(osg::ref_ptr<osg::Node> node)
{
    //添加默认事件处理器
    //捕捉事件坐标点
    MAP_OSG_BaseHandler *l_baseHandler = new MAP_OSG_BaseHandler();
    m_instance->addHandler(l_baseHandler);
    //实时显示经纬高
    //高程未加载完成时，显示的高度有问题..
    osgEarth::Util::Controls::ControlCanvas* canvas = new osgEarth::Util::Controls::ControlCanvas();
    node->asGroup()->addChild( canvas );
    osgEarth::Util::Controls::VBox* vbox = new osgEarth::Util::Controls::VBox();
    canvas->addControl( vbox );

    osgEarth::Util::Controls::LabelControl* readout = new osgEarth::Util::Controls::LabelControl();
    vbox->addControl( readout );

    osgEarth::Util::MouseCoordsTool* tool = new osgEarth::Util::MouseCoordsTool(
                                                osgEarth::MapNode::findMapNode(node));
    tool->addCallback( new osgEarth::Util::MouseCoordsLabelCallback(readout) );
    m_instance->addHandler(tool);
    //初始化全局记录的数据
    m_instance->initGlobalData();
}

MAP_OSG_ViewController::~MAP_OSG_ViewController()
{

}

MAP_OSG_BaseViewer *MAP_OSG_ViewController::addView(const QString &earthFilePath)
{
    __initializeIfNot();
    int argc = 2;
    char **argv = new char *[2];

    char *appPath = new char[300];
    QByteArray pathByteArray = qApp->applicationFilePath().toLocal8Bit();
    memcpy_s(appPath, 300, pathByteArray.data(), rsize_t(pathByteArray.length() + 1));
    char *earthPath = new char[300];
    QByteArray earthByteArray = earthFilePath.toLocal8Bit();
    memcpy_s(earthPath, 300, earthByteArray.data(), rsize_t(earthByteArray.length() + 1));
    argv[0] = appPath;
    argv[1] = earthPath;

    osg::ArgumentParser args(&argc,argv);
    osg::ref_ptr<osg::Group> root = new osg::Group;
    osg::ref_ptr<osg::Node> node = osgDB::readNodeFiles(args);
    if (!node.valid())
    {
        QMessageBox::critical(nullptr, QString(u8"加载地图错误"), QString(u8"[ osgDB ] readNodeFiles 未能加载地图文件\"%1\".").arg(earthPath));
        return nullptr;
    }

    osg::ref_ptr<osgViewer::View> view = new osgViewer::View();

    MAP_OSG_BaseViewer* viewWidget = new MAP_OSG_BaseViewer(view);

    // 关闭自带的鼠标左键双击事件
    auto l_earthManipulator = new osgEarth::Util::EarthManipulator;
    auto settings = l_earthManipulator->getSettings();
    settings->bindMouseDoubleClick(osgEarth::Util::EarthManipulator::ACTION_NULL,
                                   osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON);
    l_earthManipulator->applySettings(settings);
    view->setCameraManipulator(l_earthManipulator);

    root->addChild(node);
    view->setSceneData(root);
    MAP_GLOBALDATA_APPData::getInstance()->g_rootNode = root;

    m_instance->m_viewer.addView(view);

    m_instance->initView(node);

    delete[] appPath;
    delete[] earthPath;
    delete[] argv;

    return viewWidget;
}

void MAP_OSG_ViewController::removeView(MAP_OSG_BaseViewer *baseViewer)
{
    __initializeIfNot();
    m_instance->m_viewer.removeView(baseViewer->getView());
}

bool MAP_OSG_ViewController::addHandler(osgGA::GUIEventHandler *pHandler, int index)
{
    auto l_pCurrView =  m_instance->m_viewer.getView(index);
    if(l_pCurrView)
    {
        l_pCurrView->addEventHandler(pHandler);
        return true;
    }
    return false;
}

bool MAP_OSG_ViewController::removeHandler(osgGA::GUIEventHandler *pHandler, int index)
{
    m_instance->m_viewer.markRemoveHandler(index, pHandler);
    return true;
}

void MAP_OSG_ViewController::paint()
{
    if (m_viewer.getRunFrameScheme() == osgViewer::ViewerBase::CONTINUOUS ||
        m_viewer.checkNeedToDoFrame() )
    {
        m_viewer.frame();
    }
}

void MAP_OSG_ViewController::__initializeIfNot()
{
    if(m_instance == nullptr)
        m_instance = new MAP_OSG_ViewController;
}

MAP_OSG_CompositeView::MAP_OSG_CompositeView(const osgViewer::CompositeViewer &cv, const osg::CopyOp &copyop)
    : osgViewer::CompositeViewer(cv, copyop)
{
    ::MAP_OSG_CompositeView();
}

MAP_OSG_CompositeView::MAP_OSG_CompositeView(osg::ArgumentParser &arguments)
    : osgViewer::CompositeViewer(arguments)
{
    ::MAP_OSG_CompositeView();
}

MAP_OSG_CompositeView::MAP_OSG_CompositeView()
{
    m_bRemoveHandler = false;
    m_index = 0;
    m_pHandler = nullptr;
}

void MAP_OSG_CompositeView::markRemoveHandler(int index, osgGA::GUIEventHandler *pHandler)
{
    m_bRemoveHandler = true;
    m_index = index;
    m_pHandler = pHandler;
}

void MAP_OSG_CompositeView::updateTraversal()
{
    osgViewer::CompositeViewer::updateTraversal();
    if(m_bRemoveHandler)
    {
        auto l_pCurrView = this->getView(m_index);
        if(l_pCurrView)
        {
            l_pCurrView->removeEventHandler(m_pHandler);
        }
    }
}

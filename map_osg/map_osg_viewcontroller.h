#ifndef MAP_OSG_VIEWCONTROLLER_H
#define MAP_OSG_VIEWCONTROLLER_H

/// MAP_OSG_ViewController
/// 用于控制osgViewer::View的刷新以及地图的读取。
/// 参考MAP_OSG_ExampleWindow使用该类读取地图。


#include <QObject>
#include <osg/Notify>
#include <osgViewer/CompositeViewer>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarth/FileUtils>
#include <QTimer>
#include <QWidget>
#include <QString>
#include <QApplication>
#include <QMessageBox>
#include "map_osg_baseviewer.h"

/**
 * @brief The MAP_OSG_CompositeView class
 * 该类是继承CompositeViewer类，主要重写了更新回调函数。
 * 作用是删除注册的handler，避免崩溃。
 */
class MAP_OSG_CompositeView : public osgViewer::CompositeViewer
{
public:
    MAP_OSG_CompositeView(const CompositeViewer&,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);
    MAP_OSG_CompositeView(osg::ArgumentParser& arguments);
    MAP_OSG_CompositeView();

    /**
     * @brief markRemoveHandler
     * 提供的标记删除函数，在更新回调时才会真正删除
     * @param index
     * @param pHandler
     */
    void markRemoveHandler(int index, osgGA::GUIEventHandler *pHandler);
protected:
    /**
     * @brief updateTraversal
     * 更新回调函数
     */
    void updateTraversal() override;
private:
    bool m_bRemoveHandler;
    int m_index;
    osgGA::GUIEventHandler *m_pHandler;
};

class MAP_OSG_ViewController : public QObject
{
    Q_OBJECT
public:
    ~MAP_OSG_ViewController();

    static MAP_OSG_BaseViewer *addView(const QString &earthFilePath);
    static void removeView(MAP_OSG_BaseViewer *baseViewer);

    /**
     * @brief addHandler
     * 在地图view上添加handler；
     * 用法：
     * MAP_OSG_ViewController::addHandler(m_pHandler);
     * 也可通过全局变量进行添加：
     * auto l_mapData = MAP_GLOBALDATA_APPData::getInstance()->g_mapData;
     * if(!l_mapData->valid)
     *    return;
     * l_mapData->pView->addEventHandler(m_pHandler);
     * @param pHandler
     * @param index
     * @return
     */
    static bool addHandler(osgGA::GUIEventHandler *pHandler, int index = 0);
    /**
     * @brief removeHandler
     * 在地图view上删除handler；
     * 用法：
     * MAP_OSG_ViewController::addHandler(m_pHandler);
     * 注意：
     * 删除时必须通过此方法删除，否则可能导致崩溃！
     * @param pHandler
     * @param index
     * @return
     */
    static bool removeHandler(osgGA::GUIEventHandler *pHandler, int index = 0);


signals:

public slots:
    void paint();

private:
    static inline void __initializeIfNot();
    explicit MAP_OSG_ViewController();

    /**
     * @brief initView
     * 添加新的view时，进行一些默认操作的设置；
     * 如添加一些实用且持续的控制器
     * @param node
     */
    void initView(osg::ref_ptr<osg::Node> node);

    /**
     * @brief initGlobalData
     * 添加新的view时，把view上绑定的一些属性记录在全局中，方便调用
     */
    void initGlobalData();

    QTimer m_timer;
    MAP_OSG_CompositeView m_viewer;
    static MAP_OSG_ViewController *m_instance;
};
#endif // MAP_OSG_VIEWCONTROLLER_H

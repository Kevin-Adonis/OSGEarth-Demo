#ifndef MAP_OSG_BASEHANDLER_H
#define MAP_OSG_BASEHANDLER_H

#include <QObject>
#include <osgGA/GUIEventHandler>
#include <osg/CoordinateSystemNode>
#include <osgEarth/SpatialReference>

/**
 * @brief The MAP_OSG_BaseHandler class
 * osg绑定的handler的基类，捕获特定的需要的事件，
 * 通过发送信号的方式把相关数据发送出去，自身不处理相关的事件。
 * 默认情况下在osgWidget初始化即绑定在viewer上面。
 * 暂定的功能职责为：捕捉事件坐标点，并给出osg控件的响应
 * 用法：
 * MAP_OSG_BaseHandler *pHandler;
 * connect(pHandler, &MAP_OSG_BaseHandler::signalPicked, receiver, &xx::pickHandle)
 */
class MAP_OSG_BaseHandler : public QObject, public osgGA::GUIEventHandler
{
    Q_OBJECT
public:
    MAP_OSG_BaseHandler();

protected:
    /**
     * @brief handle
     * 核心的事件捕捉函数，
     * 继承osg的GUIEventHandler的handle函数。
     * @param ea
     * @param aa
     * @return
     */
    virtual bool handle(const osgGA::GUIEventAdapter& ea,
        osgGA::GUIActionAdapter& aa);

protected:
    /**
     * @brief getPos
     * 用于通过事件计算出坐标值
     * @param ea
     * @param aa
     * @param pos
     * 用来接收经纬度的坐标
     * @return
     * 返回值为世界坐标值
     */
    osg::Vec3d getPos(const osgGA::GUIEventAdapter& ea,
        osgGA::GUIActionAdapter& aa, osg::Vec3d& pos);

signals:
    // 经纬度信息
    void signalPicked(osg::Vec3d pos);
    void signalMoving(osg::Vec3d pos);
    void signalDoubleClicked(osg::Vec3d l_vecPos,osg::Vec3d l_worldpos);

    // 世界坐标信息
    void signalPickedXYZ(osg::Vec3d pos);
    void signalMovingXYZ(osg::Vec3d pos);


    void signalRightPicked();


protected:
    osg::Vec3d m_vecPostion;
};

#endif // MAP_OSG_BASEHANDLER_H

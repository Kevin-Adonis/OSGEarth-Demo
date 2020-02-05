#ifndef MAP_GR_CREATEPRIMITIVE_H
#define MAP_GR_CREATEPRIMITIVE_H

#include <QObject>
#include <osg/Vec3d>
#include "map_osg/map_osg_basehandler.h"

/**
 * @brief The MAP_GR_CreatePrimitiveHandler class
 * 绘制一系列图元的类，使用时把该类的指针绑定到osg的handler上。
 * 如：
 * MAP_OSG_BaseHandler *pHandler;
 * MAP_GR_CreatePrimitiveHandler *pCreatePrimitve = new MAP_GR_CreatePrimitiveHandler();
 * pCreatePrimitve->beginHandle();
 * 完善该类的一些建议：
 * 1.添加数据记录器，在槽函数中记录历史传递的数据，由此作出绘制决策；
 * 2.通过属性设置，提供set函数，给外界控制自身绘制图元的种类
 *  亦可自身通过MAP_GLOBALDATA_APPData::getInstance()->g_primitiveMode获取当前绘制图元类型。
 * 3.不同图元绘制可分发给不同函数处理；亦可通过继承关系去处理。
 *  注意所有槽函数已设置为虚函数。
 *  相关实现可参考群里发过的kestiny专栏。
 */
class MAP_GR_CreatePrimitive : public QObject
{
    Q_OBJECT
public:
    MAP_GR_CreatePrimitive(const MAP_OSG_BaseHandler *pHandler);
    /**
     * @brief beginHandle
     * 开始绑定所有处理槽函数。
     */
    void beginHandle();
    /**
     * @brief endHandle
     * 解绑所有处理槽函数
     */
    void endHandle();

public slots:
    /**
     * @brief slotPicked
     * 响应处理点击事件
     * @param pos
     * 参数为经纬度坐标
     */
    virtual void slotPicked(osg::Vec3d pos);
    /**
     * @brief slotMoveing
     * 响应处理鼠标移动事件
     * @param pos
     * 参数为经纬度坐标
     */
    virtual void slotMoving(osg::Vec3d pos);

    /**
     * @brief slotPickedXYZ
     * 响应处理点击事件
     * @param pos
     * 参数为世界坐标点
     */
    virtual void slotPickedXYZ(osg::Vec3d pos);
    /**
     * @brief slotMoveingXYZ
     * 响应处理鼠标移动事件
     * @param pos
     * 参数为世界坐标点
     */
    virtual void slotMovingXYZ(osg::Vec3d pos);

    /**
     * @brief slotRightHandle
     * 响应处理右键点击事件
     */
    virtual void slotRightHandle();
private:
    const MAP_OSG_BaseHandler *m_pHandler;

};

#endif // MAP_GR_CREATEPRIMITIVE_H

#include "map_osg_basehandler.h"
#include <osgViewer/View>
#include <osgEarth/MapNode>
#include <osgEarth/TerrainEngineNode>
#include <QDebug>

MAP_OSG_BaseHandler::MAP_OSG_BaseHandler()
{
}

bool MAP_OSG_BaseHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
    // 存储经纬度信息
    osg::Vec3d l_vecPos;
    switch (ea.getEventType())
    {
        // 键盘按键事件
        case osgGA::GUIEventAdapter::KEYDOWN:
        {
//            qDebug() << "enter";
//            auto k = ea.getKey();
//            qDebug() << k;
            break;
        }
        // 点击事件
        case osgGA::GUIEventAdapter::PUSH:
        {
            osg::Vec3d l_worldPos = getPos(ea, aa, l_vecPos);
            // 鼠标左键
            if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
            {
                m_vecPostion = l_worldPos;
            }
            break;
        }
        case osgGA::GUIEventAdapter::DOUBLECLICK:
        {
            //鼠标双击
            osg::Vec3d l_worldPos =getPos(ea,aa,l_vecPos);

            emit signalDoubleClicked(l_vecPos,l_worldPos);
//          emit signalDoubleClickedXYZ(l_worldPos);
            break;

        }

        // 鼠标移动事件
        case osgGA::GUIEventAdapter::MOVE:
        {
//            qDebug() << u8"鼠标移动：";

            osg::Vec3d l_worldPos = getPos(ea, aa, l_vecPos);
//            qDebug() << u8"世界坐标值:" << l_worldPos.x() << ", " << l_worldPos.y() << ", " << l_worldPos.z();
//            qDebug() << u8"经纬度坐标值:" << l_vecPos.x() << ", " << l_vecPos.y() << ", " << l_vecPos.z();

            emit signalMoving(l_vecPos);
            emit signalMovingXYZ(l_worldPos);
            break;
        }

        // 鼠标释放事件
        case osgGA::GUIEventAdapter::RELEASE:
        {
            osg::Vec3d l_worldPos = getPos(ea, aa, l_vecPos);
            // 鼠标左键
            if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
            {
                // 如果释放的点和点击的点同一，则发送单击事件发生的位置
                if (m_vecPostion == l_worldPos && m_vecPostion != osg::Vec3d(0, 0, 0))
                {
//                    qDebug() << u8"鼠标点击：";

//                    qDebug() << u8"世界坐标值:" << l_worldPos.x() << ", " << l_worldPos.y() << ", " << l_worldPos.z();
//                    qDebug() << u8"经纬度坐标值:" << l_vecPos.x() << ", " << l_vecPos.y() << ", " << l_vecPos.z();
                    emit signalPicked(l_vecPos);
                    emit signalPickedXYZ(l_worldPos);
                }
            }
            else if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
            {
//                qDebug() << u8"右键点击";
                emit signalRightPicked();
            }
            break;
        }


    default:
            break;
    }

    return false;
}

osg::Vec3d MAP_OSG_BaseHandler::getPos(
        const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Vec3d &pos)
{
    pos = osg::Vec3d(0, 0, 0);
    osgViewer::View* l_pViewer = dynamic_cast<osgViewer::View*>(&aa);
    auto l_mapNode = osgEarth::MapNode::findMapNode(l_pViewer->getSceneData());
    osg::NodePath l_nodePath;
    l_nodePath.push_back(l_mapNode->getTerrainEngine());
    if (l_pViewer == NULL)
    {
        return osg::Vec3d(0, 0, 0);
    }
    // 获取当前点
    osgUtil::LineSegmentIntersector::Intersections intersection;
    l_pViewer->computeIntersections(ea.getX(), ea.getY(), l_nodePath, intersection);
    osgUtil::LineSegmentIntersector::Intersections::iterator iter
        = intersection.begin();
    if (iter != intersection.end())
    {
        //下方法获取的高度值似乎不对
//        m_pEllipsoid->convertXYZToLatLongHeight(
//            iter->getWorldIntersectPoint().x(), iter->getWorldIntersectPoint().y(), iter->getWorldIntersectPoint().z(),
//            pos.y(), pos.x(), pos.z());
//        pos.x() = osg::RadiansToDegrees(pos.x());
//        pos.y() = osg::RadiansToDegrees(pos.y());

        osgEarth::GeoPoint point;
        point.fromWorld(l_mapNode->getMap()->getSRS(), iter->getWorldIntersectPoint());
        pos.x() = point.x();
        pos.y() = point.y();
        pos.z() = point.z();

        return iter->getWorldIntersectPoint();
    }
    return osg::Vec3d(0, 0, 0);
}

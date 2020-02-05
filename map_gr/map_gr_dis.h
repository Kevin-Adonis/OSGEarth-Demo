#ifndef MAP_GR_DIS_H
#define MAP_GR_DIS_H
#include "map_osg/map_osg_basehandler.h"
#include "map_osg/map_osg_baseviewer.h"
#include <QObject>
#include <osgGA/GUIEventHandler>
#include <osg/CoordinateSystemNode>
#include <osgEarth/SpatialReference>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/LineWidth>
#include <String>
#include <osgEarthAnnotation/ImageOverlay>
#include <osgEarthAnnotation/CircleNode>
#include <osgEarthAnnotation/RectangleNode>
#include <osgEarthAnnotation/EllipseNode>
#include <osgEarthAnnotation/LabelNode>
#include <osgEarthAnnotation/LocalGeometryNode>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthAnnotation/ModelNode>
#include <osgEarthAnnotation/ImageOverlayEditor>
#include <osgEarthAnnotation/ImageOverlay>
#include <osgEarthAnnotation/CircleNode>
#include <osgEarthAnnotation/RectangleNode>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthAnnotation/LocalGeometryNode>
#include <osgEarthAnnotation/AnnotationEditing>
#include <osgEarth/ElevationQuery>
#include <osgEarthSymbology/GeometryFactory>
#include "map_globaldata/map_globaldata_appdata.h"

class MAP_GR_DIS: public MAP_OSG_BaseHandler
{
public:


    MAP_GR_DIS()
    {
        clickCase=0;
        vectexArray=new osg::Vec3dArray;
        drawLine=new osg::Geode;

    }
    void MeasuringDistance();                                       //按下按钮应该跳到的函数
    double getTwoPointDistance(osg::Vec3d point1,osg::Vec3d point2); //工具函数，两点之间的距离函数

    double getDis(osg::Vec3dArray &vec);
    double totalDis;                    //得到最后起点与终点的总distance

    double getHeight(double longitude, double latitude);            //经纬为参数，返回高度
    osg::Vec3d MapToWorld(osg::Vec3d vec);                             //未完善

    int clickCase;
    //clickcase=0 表示还没开始双击
    //clickcase=1 表示画第一个点了
    //clickCasse=2 表示开始画第二个点

    osg::Vec3d startPointVec;  //起点经纬度坐标
    osg::Vec3d endPointVec;    //终点经纬度坐标
    osg::Vec3d startPointWorld;  //起点世界坐标
    osg::Vec3d endPointWorld;    //终点世界坐标



    //绘图有关
    osg::ref_ptr<osg::Geode> drawLine;
    osg::ref_ptr<osg::Vec3dArray> vectexArray;
    const MAP_OSG_BaseHandler *m_pHandler;


// public slots:
     void DIS_handler(osg::Vec3d l_vecPos,osg::Vec3d l_worldPos);   //处理DoubleClicked的函数
};
class DISCLASS
{
public:
    static MAP_GR_DIS * disObject;

};



#endif // DIS_H

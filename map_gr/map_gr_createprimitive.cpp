#include "map_gr_createprimitive.h"
#include <QDebug>
#include <osgEarthAnnotation/ImageOverlay>
#include <osgEarthAnnotation/CircleNode>
#include <osgEarthAnnotation/RectangleNode>
#include <osgEarthAnnotation/EllipseNode>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthAnnotation/LabelNode>
#include <osgEarthAnnotation/LocalGeometryNode>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthAnnotation/ModelNode>

#include <osgEarthAnnotation/AnnotationEditing>
#include <osgEarthAnnotation/ImageOverlayEditor>

#include <osgEarthSymbology/GeometryFactory>
#include "map_globaldata/map_globaldata_appdata.h"

MAP_GR_CreatePrimitive::MAP_GR_CreatePrimitive(const MAP_OSG_BaseHandler *pHandler)
{
    this->m_pHandler = pHandler;
}

void MAP_GR_CreatePrimitive::beginHandle()
{
    auto a = MAP_GLOBALDATA_APPData::getInstance()->g_mapData->pHandler;
    connect(a, &MAP_OSG_BaseHandler::signalPicked, this, &MAP_GR_CreatePrimitive::slotPicked);
    connect(m_pHandler, &MAP_OSG_BaseHandler::signalMoving, this, &MAP_GR_CreatePrimitive::slotMoving);
    connect(m_pHandler, &MAP_OSG_BaseHandler::signalPickedXYZ, this, &MAP_GR_CreatePrimitive::slotPickedXYZ);
    connect(m_pHandler, &MAP_OSG_BaseHandler::signalMovingXYZ, this, &MAP_GR_CreatePrimitive::slotMovingXYZ);
    connect(m_pHandler, &MAP_OSG_BaseHandler::signalRightPicked, this, &MAP_GR_CreatePrimitive::slotRightHandle);
}

void MAP_GR_CreatePrimitive::endHandle()
{
    disconnect(m_pHandler, &MAP_OSG_BaseHandler::signalPicked, this, &MAP_GR_CreatePrimitive::slotPicked);
    disconnect(m_pHandler, &MAP_OSG_BaseHandler::signalMoving, this, &MAP_GR_CreatePrimitive::slotMoving);
    disconnect(m_pHandler, &MAP_OSG_BaseHandler::signalPickedXYZ, this, &MAP_GR_CreatePrimitive::slotPickedXYZ);
    disconnect(m_pHandler, &MAP_OSG_BaseHandler::signalMovingXYZ, this, &MAP_GR_CreatePrimitive::slotMovingXYZ);
    disconnect(m_pHandler, &MAP_OSG_BaseHandler::signalRightPicked, this, &MAP_GR_CreatePrimitive::slotRightHandle);
}

void MAP_GR_CreatePrimitive::slotPicked(osg::Vec3d pos)
{
//    qDebug() << "slot start:";
    auto l_pMapData = MAP_GLOBALDATA_APPData::getInstance()->g_mapData;
    if(!l_pMapData->valid)
        return;
    osg::Group* annoGroup = new osg::Group();
    annoGroup->setName("annoGroup");
    l_pMapData->pMapNode->addChild( annoGroup );
    //annoGroup是一个osg::Group类型，加到mapNode里面

    //labelGroup是一个osg::Group类型，加到mapNode里面
    //也可以通过加到annoGroup里面间接加入

    // Make a group for labels
    osg::Group* labelGroup = new osg::Group();

    annoGroup->addChild( labelGroup );

    osgEarth::Style labelStyle;
    labelStyle.getOrCreate<osgEarth::TextSymbol>()->alignment() = osgEarth::TextSymbol::ALIGN_CENTER_CENTER;
    labelStyle.getOrCreate<osgEarth::TextSymbol>()->fill()->color() = osgEarth::Color::Yellow;
    osgEarth::Annotation::FeatureNode* pathNode = 0;
    {
        osgEarth::Geometry* path = new osgEarth::LineString();
        path->push_back( osg::Vec3d(pos.x(), pos.y(),0.0) );   // New York
        path->push_back( osg::Vec3d(49.75, 5.68, 0) );
        path->push_back( osg::Vec3d(139.75, 20.68, 0) );
        path->push_back( osg::Vec3d(139.75, 35.68, 0) );// Tokyo


        osgEarth::Features::Feature* pathFeature = new osgEarth::Features::Feature(path, l_pMapData->pMapSRS);
        pathFeature->geoInterp() = osgEarth::GEOINTERP_GREAT_CIRCLE;

        osgEarth::Style pathStyle;
        pathStyle.getOrCreate<osgEarth::LineSymbol>()->stroke()->color() = osgEarth::Color::White;
        pathStyle.getOrCreate<osgEarth::LineSymbol>()->stroke()->width() = 1.0f;
        pathStyle.getOrCreate<osgEarth::LineSymbol>()->stroke()->smooth() = true;
        pathStyle.getOrCreate<osgEarth::LineSymbol>()->tessellationSize() = 75000;
        pathStyle.getOrCreate<osgEarth::PointSymbol>()->size() = 8;
        pathStyle.getOrCreate<osgEarth::PointSymbol>()->fill()->color() = osgEarth::Color::Red;
        pathStyle.getOrCreate<osgEarth::PointSymbol>()->smooth() = true;
        pathStyle.getOrCreate<osgEarth::AltitudeSymbol>()->clamping() = osgEarth::AltitudeSymbol::CLAMP_TO_TERRAIN;
        pathStyle.getOrCreate<osgEarth::AltitudeSymbol>()->technique() = osgEarth::AltitudeSymbol::TECHNIQUE_GPU;
        pathStyle.getOrCreate<osgEarth::RenderSymbol>()->depthOffset()->enabled() = true;

        //OE_INFO << "Path extent = " << pathFeature->getExtent().toString() << std::endl;

        pathNode = new osgEarth::Annotation::FeatureNode(pathFeature, pathStyle);
        annoGroup->addChild( pathNode );


    }
}

void MAP_GR_CreatePrimitive::slotMoving(osg::Vec3d pos)
{

}

void MAP_GR_CreatePrimitive::slotPickedXYZ(osg::Vec3d pos)
{

}

void MAP_GR_CreatePrimitive::slotMovingXYZ(osg::Vec3d pos)
{

}

void MAP_GR_CreatePrimitive::slotRightHandle()
{
//    qDebug() << "right clicked:";
    auto l_pMapData = MAP_GLOBALDATA_APPData::getInstance()->g_mapData;
    if(!l_pMapData->valid)
        return;
    auto l_num = l_pMapData->pMapNode->getNumChildren();
    for(unsigned int i = 0; i < l_num; i++)
    {
        if(l_pMapData->pMapNode->getChild(i)->getName() == "annoGroup")
        {
            l_pMapData->pMapNode->removeChild(i);
//            qDebug() << "delete successfully!";
            break;
        }
    }
//    l_pMapData->pMapNode->removeChild(0, 1);
//    osg::Group* annoGroup = new osg::Group();
//    l_pMapData->pMapNode->addChild( annoGroup );
}


//void MAP_GR_CreatePrimitive::pick(osgViewer::View *viewer, const osgGA::GUIEventAdapter &ea)
//{
//    osgUtil::LineSegmentIntersector::Intersections intersections;

//    osg::Group* root = dynamic_cast<osg::Group*>(viewer->getSceneData());
//    if (!root) return;

//    if (viewer->computeIntersections(ea,intersections))
//    {
//        auto hitr = intersections.begin();
//        osg::Vec3f temp(hitr ->getWorldIntersectPoint()) ;
//        if (!m_bFirstPush)
//        {
//            point ->clear () ;
//            point ->push_back (osg::Vec3f(temp.x(), temp.y(), 3)) ;
//            ctrlPoints = DrawFirstNode(temp) ;
//            root ->addChild( ctrlPoints.get() );
//            m_bFirstPush = true ;
//        }
//        else
//        {
//            point ->push_back (osg::Vec3f(temp.x(), temp.y(), 3)) ;
//            ctrlPoints ->addChild( DrawCtrlPoints(temp));
//        }
//    }
//}

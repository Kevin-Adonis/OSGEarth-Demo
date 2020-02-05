#include "map_gr_dis.h"



void MAP_GR_DIS::MeasuringDistance()
{
    MAP_OSG_BaseHandler * m_pHandler = MAP_GLOBALDATA_APPData::getInstance()->g_mapData->pHandler;
  connect(m_pHandler, &MAP_OSG_BaseHandler::signalDoubleClicked, this, &MAP_GR_DIS::DIS_handler);

//    connect(m_pHandler, MAP_OSG_BaseHandler::signalDoubleClicked(osg::Vec3d,osg::Vec3d), this,MAP_GR_DIS::DIS_handler(osg::Vec3d,osg::Vec3d ));

}


MAP_GR_DIS * DISCLASS::disObject=new MAP_GR_DIS();

void MAP_GR_DIS::DIS_handler(osg::Vec3d l_vecPos,osg::Vec3d l_worldPos)
{



    if(clickCase==0)
    {

        //得到鼠标位置绑定的第一个点,即起点
        vectexArray->push_back(l_worldPos);
        startPointVec=l_vecPos;
        startPointWorld=l_worldPos;

        clickCase=1;
    }
    else if(clickCase==1)
    {
        //得到终点

        endPointVec=l_vecPos;
        endPointWorld=l_worldPos;

        int dis=getTwoPointDistance(startPointWorld,endPointWorld)*1000000;

        //！！！注意是x() or y()这两个哪个是纬度
        //我这里认为经线是竖直的所以x储存的是经度，纬线是水平的所以y储存的是纬度
        double deltaLatitude=(endPointVec.y()-startPointVec.y())/(float)dis*1000000; //latitude是纬度的意思
        double deltaLongitude=(endPointVec.x()-startPointVec.x())/(float)dis*1000000;//longitude是经度的意思


        osg::Vec3d tempWorld(0,0,0);
        //temp是微分后点的经纬度
        for(int i=1;i<dis;i++)
        {
            double tempLat=startPointVec.y()+i*deltaLatitude;
            double tempLon=startPointVec.x()+i*deltaLongitude;
            double tempHeight=getHeight(tempLat,tempLon);
            //获取该点的高度 已知经纬，求高度

            //得到该点
            osg::Vec3d tempPoint(tempLat,tempLon,tempHeight); //tempPoint是经纬坐标 还得转成世界的
            tempWorld=MapToWorld(tempPoint);

            vectexArray->push_back(tempWorld);

        }
        vectexArray->push_back(endPointWorld);

        //到这里已经把所有微分的点都加到vectexArray里了
        totalDis=getDis(*vectexArray)/100000000000000000/1000000000000000/1000000000000000/1000000000000000;//这里把总距离算出来了




            auto l_pMapData = MAP_GLOBALDATA_APPData::getInstance()->g_mapData;
            osg::Group* annoGroup = new osg::Group();
            annoGroup->setName("annoGroup");
            l_pMapData->pMapNode->addChild( annoGroup );
            osg::Group* labelGroup = new osg::Group();
            annoGroup->addChild(labelGroup);
            osgEarth::Geometry* path = new osgEarth::LineString();
            path->push_back(startPointVec);
            path->push_back(endPointVec);


            osgEarth::Features::Feature* pathFeature = new osgEarth::Features::Feature(path, l_pMapData->pMapSRS);
            pathFeature->geoInterp() = osgEarth::GEOINTERP_GREAT_CIRCLE;

            osgEarth::Style pathStyle;
            pathStyle.getOrCreate<osgEarth::LineSymbol>()->stroke()->color() = osgEarth::Color::White;
            pathStyle.getOrCreate<osgEarth::LineSymbol>()->stroke()->width() = 10.0f;
            pathStyle.getOrCreate<osgEarth::LineSymbol>()->stroke()->smooth() = true;
            pathStyle.getOrCreate<osgEarth::LineSymbol>()->tessellationSize() = 75000;
            pathStyle.getOrCreate<osgEarth::PointSymbol>()->size() = 5;
            pathStyle.getOrCreate<osgEarth::PointSymbol>()->fill()->color() = osgEarth::Color::Green;
            pathStyle.getOrCreate<osgEarth::PointSymbol>()->smooth() = true;
            pathStyle.getOrCreate<osgEarth::AltitudeSymbol>()->clamping() = osgEarth::AltitudeSymbol::CLAMP_TO_TERRAIN;
            pathStyle.getOrCreate<osgEarth::AltitudeSymbol>()->technique() = osgEarth::AltitudeSymbol::TECHNIQUE_GPU;
            pathStyle.getOrCreate<osgEarth::RenderSymbol>()->depthOffset()->enabled() = true;


            osgEarth::Annotation::FeatureNode* pathNode;
            pathNode = new osgEarth::Annotation::FeatureNode(pathFeature, pathStyle);
            annoGroup->addChild( pathNode );
            osgEarth::Style pm;
            pm.getOrCreate<osgEarth::IconSymbol>()->url()->setLiteral( "placemark32.png" );
            pm.getOrCreate<osgEarth::IconSymbol>()->declutter() = true;
            pm.getOrCreate<osgEarth::TextSymbol>()->halo() = osgEarth::Color("#5f5f5f");

            std::string disString=std::to_string(totalDis);
            disString = disString+" m";
            double x=(startPointVec.x()+endPointVec.x())/2.0;
            double y=(startPointVec.y()+endPointVec.y())/2.0;
            osg::Vec3d disStringLoc(x , y,0);
            labelGroup->addChild( new osgEarth::Annotation::PlaceNode(osgEarth::GeoPoint(l_pMapData->pMapSRS, startPointVec.x(), startPointVec.y()), "From" , pm));
            labelGroup->addChild( new osgEarth::Annotation::PlaceNode(osgEarth::GeoPoint(l_pMapData->pMapSRS, disStringLoc.x(), disStringLoc.y()), disString));
            labelGroup->addChild( new osgEarth::Annotation::PlaceNode(osgEarth::GeoPoint(l_pMapData->pMapSRS, endPointVec.x(), endPointVec.y()), "To", pm));

        clickCase=2;
    }
    else if(clickCase==2)
    {
        clickCase=0;

    }
}
double MAP_GR_DIS::getTwoPointDistance(osg::Vec3d point1,osg::Vec3d point2)
{
    return sqrt((point1.x()-point2.x())*(point1.x()-point2.x())+\
            (point1.y()-point2.y())*(point1.y()-point2.y())+\
            (point1.z()-point2.z())*(point1.z()-point2.z()));
}
double MAP_GR_DIS::getDis(osg::Vec3dArray &vec)
{

    for(auto iterator=vec.begin();iterator!=vec.end();iterator++)
    {
        auto iterator2=iterator;
        iterator2++;
        if(iterator2==vec.end())
        {
            break;
        }
        else
        {
            totalDis+=getTwoPointDistance(*iterator,*iterator2);
        }

    }
    return totalDis;
}
double MAP_GR_DIS::getHeight(double longitude, double latitude)
{
    double height = 0.0;
    osg::ref_ptr <osgEarth::MapNode> mapnode;
    if(MAP_GLOBALDATA_APPData::getInstance()->g_mapData->valid)
        mapnode =MAP_GLOBALDATA_APPData::getInstance()->g_mapData->pMapNode;
    mapnode->getTerrain()->getHeight(mapnode->getMapSRS(), longitude, latitude, &height);
    return height;
}
osg::Vec3d MAP_GR_DIS::MapToWorld(osg::Vec3d vec)
{



   //
    osg::Vec3d WorldPoint(0,0,0);
    osg::ref_ptr elpModel=new osg::EllipsoidModel;
    elpModel->convertLatLongHeightToXYZ(
        vec.x(),vec.y(),vec.z(),WorldPoint.x(),WorldPoint.y(),WorldPoint.z());
    return WorldPoint;

}




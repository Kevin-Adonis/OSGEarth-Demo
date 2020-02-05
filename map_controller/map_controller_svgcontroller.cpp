#include <osg/ImageStream>
#include <osg/Node>
#include <osgEarth/TerrainEngineNode>
#include <QDebug>
#include <algorithm>
#include <QMessageBox>
#include <QFile>
#include <QApplication>

#include "map_controller_svgcontroller.h"
#include "map_globaldata/map_globaldata_appdata.h"
#include "map_osg/map_osg_viewcontroller.h"

MAP_CONTROLLER_SVGController::MAP_CONTROLLER_SVGController()
{

}

void MAP_CONTROLLER_SVGController::addSVG(QString svgPath, double x, double y)
{

    //Read the image file and play it if it's a movie
    osg::ref_ptr<osg::Image> image;
    //缓存操作，避免多次读入同一个模型
    auto l_imageIndex = std::find(m_vLoadedImagesName.begin(), m_vLoadedImagesName.end(), svgPath);
    if(l_imageIndex != m_vLoadedImagesName.end())
        image = m_vLoadedImages[l_imageIndex - m_vLoadedImagesName.begin()];
    else
    {
        image = readImageFromChineseName(svgPath);
        if(!image)
        {
            QMessageBox::warning(nullptr, u8"警告", "SVG模型读入失败！");
            return;
        }
        m_vLoadedImagesName.push_back(svgPath);
        m_vLoadedImages.push_back(image);

        if(m_vLoadedImagesName.size() == 1)
        {
            m_pHandler = new MAP_SVG_Handler(this);
            auto l_mapData = MAP_GLOBALDATA_APPData::getInstance()->g_mapData;
            if(!l_mapData->valid)
                return;
            l_mapData->pView->addEventHandler(m_pHandler);
        }
    }
    if(!image)
        return;

    //改变图片的颜色
    unsigned int width_image = image->s();
    unsigned int height_image = image->t();
    osg::Vec4 color(1.0, 0.0,0.0,1.0);
    for(unsigned int j=0; j<height_image; j++)
    {
        for( unsigned int i =0; i<width_image; i++)
        {
            osg::Vec4  color_temp = image->getColor( i,j );
            if(color_temp.a() > 0.1)
                image->setColor(color, i, j);
        }
    }
    if (image.valid())
    {
        osg::ImageStream* is = dynamic_cast<osg::ImageStream*>(image.get());
        if (is)
        {
            is->play();
        }
    }
    //Create a new ImageOverlay and set it's bounds
    auto l_mapData = MAP_GLOBALDATA_APPData::getInstance()->g_mapData;
    if(!l_mapData->valid)
        return;
    auto l_mapNode = l_mapData->pMapNode;
    osgEarth::Annotation::ImageOverlay* overlay = new osgEarth::Annotation::ImageOverlay(l_mapNode);
    overlay->setImage( image );
    if(x == 0 && y == 0)
        overlay->setCenter(-95, 35);
    else
    {
        osg::Vec2 pos = getLatLongDegree(x, y);

        overlay->setCenter(pos.x(), pos.y());
        overlay->setBounds(osgEarth::Bounds(pos.x() - 2, pos.y() - 2, pos.x() + 2, pos.y() + 2));
    }
    l_mapNode->addChild( overlay );
    m_vImageOverlays.push_back(overlay);
    osgEarth::Annotation::ImageOverlayEditor *editor = new osgEarth::Annotation::ImageOverlayEditor(overlay);
    editor->setNodeMask(0);
    l_mapNode->addChild(editor);
    m_vImageOverlayEditors.push_back(editor);
}

void MAP_CONTROLLER_SVGController::removeSVG(osgEarth::Annotation::ImageOverlay* imageOverlay)
{
    auto l_mapData = MAP_GLOBALDATA_APPData::getInstance()->g_mapData;
    if(!l_mapData->valid)
        return;
    auto l_mapNode = l_mapData->pMapNode;
    auto iter = std::find(m_vImageOverlays.begin(), m_vImageOverlays.end(), imageOverlay);
    if(iter == m_vImageOverlays.end())
        return;
    int index = iter - m_vImageOverlays.begin();

    l_mapNode->removeChild(imageOverlay);
    l_mapNode->removeChild(*(m_vImageOverlayEditors.begin() + index));
    m_vImageOverlays.erase(m_vImageOverlays.begin() + index);
    m_vImageOverlayEditors.erase(m_vImageOverlayEditors.begin() + index);
    if(m_vImageOverlays.empty())
        clear();
}

void MAP_CONTROLLER_SVGController::clear()
{
    m_vLoadedImagesName.clear();
    m_vLoadedImages.clear();
    m_vImageOverlays.clear();
    m_vImageOverlayEditors.clear();
    if(m_pHandler)
    {
        auto l_mapData = MAP_GLOBALDATA_APPData::getInstance()->g_mapData;
        if(!l_mapData->valid)
            return;
        MAP_OSG_ViewController::removeHandler(m_pHandler);
        m_pHandler = nullptr;
    }
}

osg::Vec2 MAP_CONTROLLER_SVGController::getLatLongDegree(double x, double y)
{
    osg::Vec2 pos(0.0, 0.0);
    auto l_mapData = MAP_GLOBALDATA_APPData::getInstance()->g_mapData;
    if(!l_mapData->valid)
        return osg::Vec2();
    osgViewer::View* l_pViewer = l_mapData->pView;
    auto l_mapNode = osgEarth::MapNode::findMapNode(l_pViewer->getSceneData());
    osg::NodePath l_nodePath;
    l_nodePath.push_back(l_mapNode->getTerrainEngine());

    // 获取当前点
    osgUtil::LineSegmentIntersector::Intersections intersection;
    l_pViewer->computeIntersections(x, y, l_nodePath, intersection);
    osgUtil::LineSegmentIntersector::Intersections::iterator iter
            = intersection.begin();
    if (iter != intersection.end())
    {
        osgEarth::GeoPoint point;
        point.fromWorld(l_mapNode->getMap()->getSRS(), iter->getWorldIntersectPoint());
        pos.x() = point.x();
        pos.y() = point.y();

        return pos;
    }
    return osg::Vec2();
}

osg::ref_ptr<osg::Image> MAP_CONTROLLER_SVGController::readImageFromChineseName(QString path)
{
    QString tempPath = qApp->applicationDirPath() + "/1.svg";
    QFile::copy(path, tempPath);
    osg::ref_ptr<osg::Image> image = osgDB::readImageFile(tempPath.toStdString());
    QFile::remove(tempPath);
    return image;
}

MAP_CONTROLLER_SVGController::MAP_SVG_Handler::MAP_SVG_Handler(MAP_CONTROLLER_SVGController *svgController)
{
    this->m_pSVGController = svgController;
}

bool MAP_CONTROLLER_SVGController::MAP_SVG_Handler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
    osgEarth::Annotation::ImageOverlay* clickedImage = nullptr;
    int index = 0;
    switch (ea.getEventType())
    {
        // 鼠标双击事件
        case osgGA::GUIEventAdapter::DOUBLECLICK:
            if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
            {
                clickedImage = checkOverlays(ea, index);
                if(clickedImage)
                {
                    auto nodeMask = m_pSVGController->m_vImageOverlayEditors[index]->getNodeMask();
                    if(nodeMask != ~0u)
                        m_pSVGController->m_vImageOverlayEditors[index]->setNodeMask(~0u);
                    else
                        m_pSVGController->m_vImageOverlayEditors[index]->setNodeMask(0u);
                }
            }
            break;
            // 鼠标右键删除
        case osgGA::GUIEventAdapter::RELEASE:
            if(ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
            {
                clickedImage = checkOverlays(ea, index);
                if(clickedImage)
                {
                    m_pSVGController->removeSVG(clickedImage);
                }
            }
            break;

        default:
            break;
    }

    return false;
}

osgEarth::Annotation::ImageOverlay *MAP_CONTROLLER_SVGController::MAP_SVG_Handler::checkOverlays(
        const osgGA::GUIEventAdapter &ea, int &index)
{
    osgEarth::Annotation::ImageOverlay *clickedImage = nullptr;
    for(unsigned long i = 0; i < m_pSVGController->m_vImageOverlays.size(); i++)
    {
        auto bounds = m_pSVGController->m_vImageOverlays[i]->getBounds();
        osg::Vec2 pos = m_pSVGController->getLatLongDegree(ea.getX(), ea.getY());
        if(pos.x() < bounds.xMin() || pos.x() > bounds.xMax() ||
                pos.y() < bounds.yMin() || pos.y() > bounds.yMax())
            continue;
        clickedImage = m_pSVGController->m_vImageOverlays[i];
        index = i;
        break;
    }
    return clickedImage;
}

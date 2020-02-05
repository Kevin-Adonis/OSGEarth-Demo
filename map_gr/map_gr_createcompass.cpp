#include "map_gr_createcompass.h"
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <QApplication>
#include <QMessageBox>

MAP_GR_CreateCompass::MAP_GR_CreateCompass()
{
    m_pCompass = nullptr;
}

osg::ref_ptr<osg::Camera> MAP_GR_CreateCompass::getCompass()
{
    return m_pCompass;
}

void MAP_GR_CreateCompass::deleteCompass()
{
    m_pCompass = nullptr;
}

osg::MatrixTransform *MAP_GR_CreateCompass::createCompassPart(const std::string &image, float radius, float height)
{
    osg::Vec3 center(-radius, -radius, height);
    osg::ref_ptr<osg::Geode> gnode = new osg::Geode();
    gnode->addDrawable(osg::createTexturedQuadGeometry(center, osg::Vec3(radius*2.0, 0.0f, 0.0f), osg::Vec3(0.0f, radius*2.0f, 0.0f)));

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    auto l_image = osgDB::readImageFile(image);
    if((!l_image) || (!l_image->valid()))
    {
        QMessageBox::warning(nullptr, u8"警告", u8"指南针图片加载失败！");
        return nullptr;
    }
    texture->setImage(l_image);

    osg::ref_ptr<osg::MatrixTransform> part = new osg::MatrixTransform;
    part->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture);
    part->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    part->addChild(gnode);
    return part.release();
}

osg::ref_ptr<osg::Camera> MAP_GR_CreateCompass::createCompress(double x, double y)
{
    auto plate = createCompassPart(QString(qApp->applicationDirPath() + "/example_data/Image/compass.png").toStdString()
                                   , 1.5, -1.0);
    if(plate == nullptr)
        return nullptr;
    osg::ref_ptr<osg::Camera> compass = new osg::Camera;
    compass->setViewport(x - 128, y - 128, 128, 128);
    compass->setProjectionMatrix(osg::Matrixd::ortho(-1.5, 1.5, -1.5, 1.5, -10, 10));

    compass->setRenderOrder(osg::Camera::POST_RENDER);
    compass->setClearMask(GL_DEPTH_BUFFER_BIT);

    compass->setAllowEventFocus(false);
    compass->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    compass->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    compass->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);

    compass->addChild(plate);
    m_pCompass = compass;
    return m_pCompass;
}

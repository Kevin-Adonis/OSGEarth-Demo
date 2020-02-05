#ifndef MAP_GR_CREATECOMPASS_H
#define MAP_GR_CREATECOMPASS_H

#include <osg/MatrixTransform>

class MAP_GR_CreateCompass
{
public:
    MAP_GR_CreateCompass();
    osg::ref_ptr<osg::Camera> getCompass();
    void deleteCompass();

    osg::MatrixTransform *createCompassPart(const std::string &image, float radius, float height);
    osg::ref_ptr<osg::Camera> createCompress(double x, double y);

private:
    osg::ref_ptr<osg::Camera> m_pCompass;
};

#endif // MAP_GR_CREATECOMPASS_H

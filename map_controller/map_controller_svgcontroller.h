#ifndef MAP_CONTROLLER_SVGCONTROLLER_H
#define MAP_CONTROLLER_SVGCONTROLLER_H

#include <osg/Vec2>
#include <osg/Image>
#include <osgEarthAnnotation/ImageOverlay>
#include <osgEarthAnnotation/ImageOverlayEditor>

#include "map_controller/map_controller_templatecontroller.h"
#include "map_osg/map_osg_basehandler.h"

/**
 * @brief The MAP_CONTROLLER_SVGController class
 * 控制svg图片的显示
 */
class MAP_CONTROLLER_SVGController : public MAP_CONTROLLER_TemplateController
{
public:
    MAP_CONTROLLER_SVGController();
    void addSVG(QString svgPath, double x = 0, double y = 0);
    void removeSVG(osgEarth::Annotation::ImageOverlay* imageOverlay);
    void clear();

public:
    osg::Vec2 getLatLongDegree(double x, double y);

    std::vector<QString> m_vLoadedImagesName;
    std::vector<osg::Image*> m_vLoadedImages;
    std::vector<osgEarth::Annotation::ImageOverlay*> m_vImageOverlays;
    std::vector<osgEarth::Annotation::ImageOverlayEditor*> m_vImageOverlayEditors;
    osg::ref_ptr<osg::Image> readImageFromChineseName(QString path );

    class MAP_SVG_Handler : public MAP_OSG_BaseHandler
    {
    public:
        MAP_SVG_Handler(MAP_CONTROLLER_SVGController *svgController);
    protected:
        virtual bool handle(const osgGA::GUIEventAdapter& ea,
            osgGA::GUIActionAdapter& aa) override;
    private:
        MAP_CONTROLLER_SVGController *m_pSVGController;
        osgEarth::Annotation::ImageOverlay *checkOverlays(const osgGA::GUIEventAdapter &ea, int &index);

    };
    MAP_SVG_Handler *m_pHandler;
};

#endif // MAP_CONTROLLER_SVGCONTROLLER_H

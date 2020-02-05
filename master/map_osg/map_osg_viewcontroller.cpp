#include "map_osg_viewcontroller.h"
#include <QDebug>

MAP_OSG_ViewController *MAP_OSG_ViewController::m_instance = nullptr;

MAP_OSG_ViewController::MAP_OSG_ViewController()
{
    m_instance = this;
    m_viewer.setThreadingModel(m_viewer.SingleThreaded);
    connect(&m_timer, &QTimer::timeout, this, &MAP_OSG_ViewController::paint);
    m_timer.start(20);
}

MAP_OSG_ViewController::~MAP_OSG_ViewController()
{

}

MAP_OSG_BaseViewer *MAP_OSG_ViewController::addView(const QString &earthFilePath)
{
    __initializeIfNot();
    int argc = 2;
    char **argv = new char *[2];

    char *appPath = new char[300];
    QByteArray pathByteArray = qApp->applicationFilePath().toLocal8Bit();
    memcpy_s(appPath, 300, pathByteArray.data(), rsize_t(pathByteArray.length() + 1));
    char *earthPath = new char[300];
    QByteArray earthByteArray = earthFilePath.toLocal8Bit();
    memcpy_s(earthPath, 300, earthByteArray.data(), rsize_t(earthByteArray.length() + 1));
    argv[0] = appPath;
    argv[1] = earthPath;

    osg::ArgumentParser args(&argc,argv);
    osg::ref_ptr<osg::Node> node = osgDB::readNodeFiles(args);
    if (!node.valid())
    {
        QMessageBox::critical(nullptr, QString(u8"加载地图错误"), QString(u8"[ osgDB ] readNodeFiles 未能加载地图文件\"%1\".").arg(earthPath));
        return nullptr;
    }

    osg::ref_ptr<osgViewer::View> view = new osgViewer::View();

    MAP_OSG_BaseViewer* viewWidget = new MAP_OSG_BaseViewer(view);

    view->setCameraManipulator(new osgEarth::Util::EarthManipulator);
    view->setSceneData(node);

    m_instance->m_viewer.addView(view);

    delete[] appPath;
    delete[] earthPath;
    delete[] argv;

    return viewWidget;
}

void MAP_OSG_ViewController::removeView(MAP_OSG_BaseViewer *baseViewer)
{
    __initializeIfNot();
    m_instance->m_viewer.removeView(baseViewer->getView());
}

void MAP_OSG_ViewController::paint()
{
    if (m_viewer.getRunFrameScheme() == osgViewer::ViewerBase::CONTINUOUS ||
        m_viewer.checkNeedToDoFrame() )
    {
        m_viewer.frame();
    }
}

void MAP_OSG_ViewController::__initializeIfNot()
{
    if(m_instance == nullptr)
        m_instance = new MAP_OSG_ViewController;
}

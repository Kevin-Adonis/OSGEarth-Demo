#include "map_controller_mainwindowcontroller.h"
#include "map_gui/map_gui_mainwindow.h"
#include "map_gui/map_gui_entityinfoview.h"
#include "map_gui/map_gui_currentinfoview.h"
#include "map_gui/map_gui_showview.h"
#include "map_globaldata/map_globaldata_appdata.h"

MAP_CONTROLLER_MainWindowController::MAP_CONTROLLER_MainWindowController()
{
    this->m_mainwindow = nullptr;
    m_pCompass = nullptr;
}

void MAP_CONTROLLER_MainWindowController::registerWidget(QWidget *templateWidget)
{
    this->m_templateWidget = templateWidget;
    this->m_mainwindow = qobject_cast<MAP_GUI_MainWindow*>(templateWidget);
    init();
}

void MAP_CONTROLLER_MainWindowController::deRegister()
{
    this->m_templateWidget = nullptr;
    this->m_mainwindow = nullptr;
}

void MAP_CONTROLLER_MainWindowController::drawingPrimitive()
{
    MAP_GLOBALDATA_Controller::primitiveConfigController->initConfig();
}

void MAP_CONTROLLER_MainWindowController::showLatLongGrid()
{
    MAP_GLOBALDATA_Controller::canvasToolController->switchLatLongGrid();
}

void MAP_CONTROLLER_MainWindowController::showCompass(double x, double y)
{
    if(!m_pCompass)
    {
        m_pCompass = new MAP_GR_CreateCompass;
    }
    auto l_root = MAP_GLOBALDATA_APPData::getInstance()->g_rootNode;
    if(!l_root)
        return;
    if(!m_pCompass->getCompass())
    {
        auto node = m_pCompass->createCompress(x, y);
        l_root->addChild(node);
    }
    else
    {
        auto node = m_pCompass->getCompass();
        l_root->removeChild(node);
        m_pCompass->deleteCompass();
    }
}

MAP_CONTROLLER_EntityViewController::MAP_CONTROLLER_EntityViewController()
{
    this->m_entityView = nullptr;
}

void MAP_CONTROLLER_EntityViewController::registerWidget(QWidget *entityView)
{
    this->m_templateWidget = entityView;
    this->m_entityView = qobject_cast<MAP_GUI_EntityInfoView*>(entityView);
    init();
}

MAP_CONTROLLER_CurrentInfoViewController::MAP_CONTROLLER_CurrentInfoViewController()
{
    this->m_currInoView = nullptr;
}

void MAP_CONTROLLER_CurrentInfoViewController::registerWidget(QWidget *currInfoView)
{
    this->m_templateWidget = currInfoView;
    this->m_currInoView = qobject_cast<MAP_GUI_CurrentInfoView*>(currInfoView);
    init();
}


MAP_CONTROLLER_ShowViewController::MAP_CONTROLLER_ShowViewController()
{
    this->m_showView = nullptr;
}

void MAP_CONTROLLER_ShowViewController::registerWidget(QWidget *showView)
{
    this->m_templateWidget = showView;
    this->m_showView = qobject_cast<MAP_GUI_ShowView*>(showView);
    init();
}

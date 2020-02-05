#include "map_controller_mainwindowcontroller.h"
#include "map_gui/map_gui_mainwindow.h"
#include "map_gui/map_gui_entityinfoview.h"
#include "map_gui/map_gui_currentinfoview.h"
#include "map_gui/map_gui_showview.h"

MAP_CONTROLLER_MainWindowController::MAP_CONTROLLER_MainWindowController()
{
    this->m_mainwindow = nullptr;
}

void MAP_CONTROLLER_MainWindowController::registerWidget(QWidget *templateWidget)
{
    this->m_templateWidget = templateWidget;
    this->m_mainwindow = qobject_cast<MAP_GUI_MainWindow*>(templateWidget);
    init();
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

#include "map_controller_templatecontroller.h"

MAP_CONTROLLER_TemplateController::MAP_CONTROLLER_TemplateController()
{
    m_templateWidget = nullptr;
}

bool MAP_CONTROLLER_TemplateController::isRegistered()
{
    if (m_templateWidget == nullptr)
        return false;
    return true;
}

void MAP_CONTROLLER_TemplateController::registerWidget(QWidget *templateWidget)
{
    this->m_templateWidget = templateWidget;
    init();
}

void MAP_CONTROLLER_TemplateController::init()
{

}

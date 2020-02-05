#include "map_globaldata/map_globaldata_appdata.h"

MAP_GLOBALDATA_APPData *MAP_GLOBALDATA_APPData::m_instance = nullptr;

MAP_GLOBALDATA_APPData *MAP_GLOBALDATA_APPData::getInstance()
{
    if(m_instance == nullptr)
        m_instance = new MAP_GLOBALDATA_APPData();
    return m_instance;
}

MAP_GLOBALDATA_APPData::MAP_GLOBALDATA_APPData()
{

}


MAP_CONTROLLER_MainWindowController *MAP_GLOBALDATA_Controller::mainWindowController =
        new MAP_CONTROLLER_MainWindowController();
MAP_CONTROLLER_EntityViewController *MAP_GLOBALDATA_Controller::entityViewController =
        new MAP_CONTROLLER_EntityViewController();
MAP_CONTROLLER_CurrentInfoViewController *MAP_GLOBALDATA_Controller::currInfoViewController =
        new MAP_CONTROLLER_CurrentInfoViewController();
MAP_CONTROLLER_ShowViewController *MAP_GLOBALDATA_Controller::showViewController =
        new MAP_CONTROLLER_ShowViewController();

MAP_GLOBALDATA_Controller::MAP_GLOBALDATA_Controller()
{

}

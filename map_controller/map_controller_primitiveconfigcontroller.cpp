#include "map_controller_primitiveconfigcontroller.h"
#include "map_globaldata/map_globaldata_appdata.h"
#include "map_dlg/map_dlg_dialogfactory.h"
#include "map_gr/map_gr_createprimitive.h"

MAP_CONTROLLER_PrimitiveConfigController::MAP_CONTROLLER_PrimitiveConfigController()
{
    m_dialog = nullptr;
    m_createPrimitive = nullptr;
}

void MAP_CONTROLLER_PrimitiveConfigController::registerWidget(QWidget *dialog)
{
    this->m_templateWidget = dialog;
    this->m_dialog = qobject_cast<MAP_DLG_PrimitiveConfigDialog*>(dialog);
    init();
}

void MAP_CONTROLLER_PrimitiveConfigController::initConfig()
{
    if(this->isRegistered())
    {
        this->m_dialog->close();
    }

    switch (MAP_GLOBALDATA_APPData::getInstance()->g_primitiveMode)
    {
        case MAP_GLOBALDATA_APPData::POINT:
        {
            initDrawingPoint();
            break;
        }
        case MAP_GLOBALDATA_APPData::LINE:
        {
            initDrawingLine();
            break;
        }
    }
}

void MAP_CONTROLLER_PrimitiveConfigController::deRegister()
{
    this->m_templateWidget = nullptr;
    this->m_dialog = nullptr;
}

void MAP_CONTROLLER_PrimitiveConfigController::exitDrawing()
{
    this->deRegister();
    if(m_createPrimitive)
        m_createPrimitive->endHandle();
}

void MAP_CONTROLLER_PrimitiveConfigController::initDrawingPoint()
{
    auto l_pMapData = MAP_GLOBALDATA_APPData::getInstance()->g_mapData;
    if(!l_pMapData->valid)
        return;
    MAP_DLG_TemplateDialog* dialog = MAP_DLG_TemplateDialogFactory::getFactoryInstance()
                                     ->createConfigDialog();
    this->registerWidget(dialog);
    if(m_dialog)
    {
        m_dialog->setupPointUI();
        connect(m_dialog, &QDialog::accepted, this, &MAP_CONTROLLER_PrimitiveConfigController::exitDrawing);
        m_dialog->show();
    }

    if(!m_createPrimitive)
        m_createPrimitive = new MAP_GR_CreatePrimitive(MAP_GLOBALDATA_APPData::getInstance()->g_mapData->pHandler);
    m_createPrimitive->beginHandle();
}

void MAP_CONTROLLER_PrimitiveConfigController::initDrawingLine()
{
    auto l_pMapData = MAP_GLOBALDATA_APPData::getInstance()->g_mapData;
    if(!l_pMapData->valid)
        return;
    MAP_DLG_TemplateDialog* dialog = MAP_DLG_TemplateDialogFactory::getFactoryInstance()
                                     ->createConfigDialog();
    this->registerWidget(dialog);
    if(m_dialog)
    {
        m_dialog->setupLineUI();
        connect(m_dialog, &QDialog::accepted, this, &MAP_CONTROLLER_PrimitiveConfigController::exitDrawing);
        m_dialog->show();
    }

    if(!m_createPrimitive)
        m_createPrimitive = new MAP_GR_CreatePrimitive(MAP_GLOBALDATA_APPData::getInstance()->g_mapData->pHandler);
    m_createPrimitive->beginHandle();
}

#ifndef MAP_CONTROLLER_PRIMITIVECONFIGCONTROLLER_H
#define MAP_CONTROLLER_PRIMITIVECONFIGCONTROLLER_H

#include "map_controller/map_controller_templatecontroller.h"
#include "map_dlg/map_dlg_primitiveconfigdialog.h"
#include "map_gr/map_gr_createprimitive.h"
#include <osgViewer/View>

/**
 * @brief The MAP_CONTROLLER_PrimitiveConfigController class
 * 该类负责管理关于绘制图元参数初始化以及通信协作
 */
class MAP_CONTROLLER_PrimitiveConfigController : public MAP_CONTROLLER_TemplateController
{
public:
    MAP_CONTROLLER_PrimitiveConfigController();
    void registerWidget(QWidget *dialog);

    /**
     * @brief initConfig
     * 入口的初始化函数，通过调用该方法配置合适的参数配置界面；
     * 前置条件：Mode和Viewer在global_data中的设置。
     */
    void initConfig();
    void deRegister();

public slots:
    void exitDrawing();

private:
    /**
     * @brief m_dialog
     * 注册的界面指针，使用前记得判定nullptr或者isRegister
     */
    MAP_DLG_PrimitiveConfigDialog *m_dialog;
    /**
     * @brief m_createPrimitive
     * 用于绘制图元的工具类
     */
    MAP_GR_CreatePrimitive *m_createPrimitive;

    /**
     * @brief initDrawingPoint
     * 具体初始化绘制点的功能
     */
    void initDrawingPoint();
    /**
     * @brief initDrawingLine
     * 具体初始化绘制线的功能
     */
    void initDrawingLine();
};

#endif // MAP_CONTROLLER_PRIMITIVECONFIGCONTROLLER_H

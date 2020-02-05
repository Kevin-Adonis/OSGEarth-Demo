#ifndef MAP_GLOBALDATA_APPDATA_H
#define MAP_GLOBALDATA_APPDATA_H

#include <QObject>
#include "map_controller/map_controller_mainwindowcontroller.h"

/**
 * @brief The MAP_GLOBALDATA_APPData class
 * 全局使用到的数据在该类中进行交互；
 * 该类为单一实例类
 */
class MAP_GLOBALDATA_APPData
{
public:
    MAP_GLOBALDATA_APPData *getInstance();
private:
    MAP_GLOBALDATA_APPData();

    static MAP_GLOBALDATA_APPData *m_instance;
};


/**
 * @brief The MAP_GLOBALDATA_Controller class
 * 该类用于包含各个controller类的全局实例，设置为全局属性的主要原因是考虑各个controller之间的通信
 * 进一步也是两个窗口或者两个部件之间的通信，考虑通过controller进而影响界面的变化
 * 涉及属性的变化进而导致界面更新的建议通过controller之间去连接信号与槽
 */
class MAP_GLOBALDATA_Controller : public QObject
{
    Q_OBJECT

public:
    MAP_GLOBALDATA_Controller();

public:
    static MAP_CONTROLLER_MainWindowController *mainWindowController;
    static MAP_CONTROLLER_EntityViewController *entityViewController;
    static MAP_CONTROLLER_CurrentInfoViewController *currInfoViewController;
    static MAP_CONTROLLER_ShowViewController *showViewController;

};
#endif // MAP_GLOBALDATA_APPDATA_H

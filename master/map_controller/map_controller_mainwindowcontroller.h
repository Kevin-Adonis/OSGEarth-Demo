#ifndef MAP_CONTROLLER_MAINWINDOWCONTROLLER_H
#define MAP_CONTROLLER_MAINWINDOWCONTROLLER_H

#include <QObject>
#include "map_controller/map_controller_templatecontroller.h"

class MAP_GUI_MainWindow;
/**
 * @brief The MAP_CONTROLLER_MainWindowController class
 * 该类作为主界面类的Controller类。
 * Controller类用于相关的业务处理，参考MVC模式
 * sql目录下封装的api视为model，界面视为view，controller类用于和数据库和界面交流
 * controller将负责和窗口通信，和model通信，将涉及model和窗口的信息，逻辑操作放在controller中
 * 建议controller格式为：
 * 1. 为每个窗口创建一个controller文件，（为每个功能模块创建一个controller，如果预估该controller过大可考虑拆分）
 * 2. 如有需要，将对应的窗口部件传入，采用两个函数registerWidget(xxx),与isregistered
 * 在使用controller时请进行isregistered检查
 * 3. 如有需要，可设置信号finish等用于和窗口类的通信
 * 4. 目前为了获取的方便，建议当创建完一个controller类后，在相应的globaldata appdata中创建一个controller全局对象，在使用的时候对其先进行注册
 * （在全局数据开建controller变量是考虑不经过界面类进行两个model或者controller的通信)
 * controller类的最终标准是能否灵活地更换界面不影响业务逻辑
 */
class MAP_CONTROLLER_MainWindowController : public MAP_CONTROLLER_TemplateController
{
    Q_OBJECT
public:
    explicit MAP_CONTROLLER_MainWindowController();
    void registerWidget(QWidget *templateWidget);

signals:

public slots:

private:
    MAP_GUI_MainWindow *m_mainwindow;
};


class MAP_GUI_EntityInfoView;
/**
 * @brief The MAP_CONTROLLER_EntityViewController class
 * 该类为主界面中实体信息显示栏的控制类。
 * 设计准则同上
 */
class MAP_CONTROLLER_EntityViewController : public MAP_CONTROLLER_TemplateController
{
    Q_OBJECT

public:
    MAP_CONTROLLER_EntityViewController();
    void registerWidget(QWidget *entityView);

private:
    MAP_GUI_EntityInfoView *m_entityView;
};

class MAP_GUI_CurrentInfoView;
class MAP_CONTROLLER_CurrentInfoViewController : public MAP_CONTROLLER_TemplateController
{
    Q_OBJECT

public:
    MAP_CONTROLLER_CurrentInfoViewController();
    void registerWidget(QWidget *entityView);

private:
    MAP_GUI_CurrentInfoView *m_currInoView;
};

class MAP_GUI_ShowView;
class MAP_CONTROLLER_ShowViewController : public MAP_CONTROLLER_TemplateController
{
    Q_OBJECT

public:
    MAP_CONTROLLER_ShowViewController();
    void registerWidget(QWidget *showView);

private:
    MAP_GUI_ShowView *m_showView;
};
#endif // MAP_CONTROLLER_MAINWINDOWCONTROLLER_H

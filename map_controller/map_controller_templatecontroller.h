#ifndef MAP_CONTROLLER_TEMPLATECONTROLLER_H
#define MAP_CONTROLLER_TEMPLATECONTROLLER_H

#include <QObject>

/**
 * @brief The MAP_CONTROLLER_TemplateController class
 * 该类作为模板类的Controller类，所有Controller类可参考该格式。
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
class MAP_CONTROLLER_TemplateController : public QObject
{
    Q_OBJECT

public:
    MAP_CONTROLLER_TemplateController();
    /**
    * @brief isRegistered
    * 该类用于判断是否为该实体模板controller设置了窗口对象
    * @return
    */
    virtual bool isRegistered();
    /**
    * @brief registerWidget
    * 该类用于注册该实体模板类对应的窗口对象
    * 注册完后会默认刷新一次对应的窗口对象
    * @param entity
    */
    virtual void registerWidget(QWidget *templateWidget);
    /**
     * @brief deRegister
     * 用于解除绑定界面
     */
    virtual void deRegister();
    /**
    * @brief initEntity
    * 该类用于初始化和刷新模板类controller对应的窗口对象
    */
    virtual void init();
    /**
     * @brief getRegisterWidget
     * 用于获取注册的控件。
     * 注意：使用前请先使用isRegistered确定有无控件。
     * @return
     */
    virtual QWidget *getRegisterWidget();

public:


signals:
    /**
    * @brief finish
    * 可能会用到的和窗口通信的信号
    */
    void finish();

protected:
    QWidget *m_templateWidget;

};


#endif // MAP_CONTROLLER_TEMPLATECONTROLLER_H

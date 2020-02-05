#ifndef MAP_DLG_TEMPLATEDIALOG_H
#define MAP_DLG_TEMPLATEDIALOG_H

#include <QDialog>
#include <QLayout>

namespace Ui {
    class MAP_DLG_TemplateDialog;
}

/**
 * @brief The MAP_DLG_TemplateDialog class
 * 对话框模板类，可作为大部分对话框的父类；
 * 提供了一套对话框的自定义框架，暂时包括：
 * 1.自定义标题栏，具体API参见自定义标题栏头文件
 * @see map_gui\map_gui_titlebar
 * 2.底部button box，提供“确定”，“取消”功能。
 * 3.边框样式以及相关QSS设置，详情参见ui文件的样式。
 * @see map_dlg\map_dlg_templateDialog.ui
 * 用法：
 * 生成Qt的ui/h文件，选择QDialog父类；在生成的.h文件中更改继承父类为MAP_DLG_TemplateDialog；
 * 在构造函数（或者合适的位置），调用MAP_DLG_TemplateDialog的useFrame方法即可。
 * 参考MAP_DLG_CreateProject界面
 * @see map_dlg\map_dlg_createproject.h
 * 最后在工厂类中提供生成界面的函数，使用工厂类创建界面。
 */
class MAP_DLG_TemplateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MAP_DLG_TemplateDialog(QWidget *parent = nullptr);
    ~MAP_DLG_TemplateDialog();

    /**
     * @brief useFrame
     * 由于使用父类框架时会覆盖子类设置的大小，所以调用时最好重新传入一次想要设置的大小；
     * 当然如非必要，窗口大小尽量统一。
     * @param widget
     * @param w
     * 派生界面的宽度
     * @param h
     * 派生界面的高度
     */
    void useFrame(QWidget *widget, int w = 0, int h = 0);

    /**
     * @brief hideButtonBox
     * 隐藏底部按钮栏。
     */
    void hideButtonBox();
    /**
     * @brief showButtonBox
     * 显示底部按钮栏
     */
    void showButtonBox();
    /**
     * @brief applicationHandle
     * 用于处理“确定”按钮事件；
     * 可重写。
     */
    virtual void applicationHandle(bool);
    /**
     * @brief cancelHandle
     * 用于处理“取消”按钮事件；
     * 可重写。
     */
    virtual void cancelHandle(bool);

protected:
    Ui::MAP_DLG_TemplateDialog *m_templateUI;
};

#endif // MAP_DLG_TEMPLATEDIALOG_H

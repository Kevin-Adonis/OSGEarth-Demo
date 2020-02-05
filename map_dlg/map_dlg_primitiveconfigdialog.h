#ifndef MAP_DLG_PRIMITIVECONFIGDIALOG_H
#define MAP_DLG_PRIMITIVECONFIGDIALOG_H

#include <QDialog>
#include "map_dlg_templatedialog.h"

namespace Ui {
    class MAP_DLG_PrimitiveConfigDialog;
}

/**
 * @brief The MAP_DLG_PrimitiveConfigDialog class
 * 图元绘制参数配置界面，可通过setup系列函数设置具体的样式。
 * 需要添加更多图元时，参考相应.ui文件中的布局，把新增的控件装在widget中，
 * 放到合适的位置，然后在构造函数hide，再添加相应的setup函数显示出来即可。
 */
class MAP_DLG_PrimitiveConfigDialog : public MAP_DLG_TemplateDialog
{
    Q_OBJECT

public:
    explicit MAP_DLG_PrimitiveConfigDialog(QWidget *parent = nullptr);
    ~MAP_DLG_PrimitiveConfigDialog() override;
    /**
     * @brief setupPointUI
     * 设置绘制点的ui
     */
    void setupPointUI();
    /**
     * @brief setupLineUI
     * 设置绘制线的ui
     */
    void setupLineUI();

protected:
    /**
     * @brief closeEvent
     * 界面退出时通知控制器，解除viewer的handler绑定
     */
    void closeEvent(QCloseEvent *) override;

private:
    Ui::MAP_DLG_PrimitiveConfigDialog *ui;
};

#endif // MAP_DLG_PRIMITIVECONFIGDIALOG_H

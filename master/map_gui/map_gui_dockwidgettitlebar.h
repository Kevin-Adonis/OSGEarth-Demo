#ifndef MAP_GUI_DOCKWIDGETTITLEBAR_H
#define MAP_GUI_DOCKWIDGETTITLEBAR_H

#include <QFrame>

namespace Ui {
class MAP_GUI_DockWidgetTitleBar;
}

class MAP_GUI_DockWidgetTitleBar : public QFrame
{
    Q_OBJECT

public:
    explicit MAP_GUI_DockWidgetTitleBar(QWidget *parent = nullptr);
    ~MAP_GUI_DockWidgetTitleBar();
    /**
     * @brief setTitle
     * 设置标题栏的标题
     * @param std::string title
     */
    void setTitleBarTitle(const QString &title);
    /**
     * @brief setTitleIcon
     * 设置浮动窗口标题栏图标
     * @param icon
     */
    void setTitleIcon(const QIcon &icon);

private slots:
    void on_closePtn_clicked();

private:
    Ui::MAP_GUI_DockWidgetTitleBar *ui;
};

#endif // MAP_GUI_DOCKWIDGETTITLEBAR_H

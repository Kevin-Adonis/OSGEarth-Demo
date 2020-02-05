#ifndef SE_GUI_TITLEBAR_H
#define SE_GUI_TITLEBAR_H

/**
 * @file se_gui_titlebar.h
 * @brief
 * 该文件是窗口的自定义标题栏。
 * @see "./se_gui_titlebar.cpp"
 * @author Danniel
 * @version 0.1
 * @since 2018/11/23
 * @date 2018/11/23
 */


#include <QWidget>

namespace Ui {
class MAP_GUI_TitleBar;
}

/**
 * @brief The TitleBarButtonFlag enum
 * 用来设置标题栏显示的按钮类型
 * 通过特定的类型判断按钮的显示和隐藏
 * 需要可自己增加类型，并在setButtonStyle中
 * 通过判断和setvisible实现自己需要的显示类型
 */
enum TitleBarButtonFlag
{
    NOMAXIMIZEBUTTON = 1,
    NOHELPBUTTON,
    NOMAXIMIZEANDMINIMIZEBUTTON,
    NOFLAGICONANDMAXMINBUTTON,
    NOBUTTON
};

class MAP_GUI_TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit MAP_GUI_TitleBar(QWidget *parent = 0);
    ~MAP_GUI_TitleBar();

    void setTitleBarTitle(const QString &title, Qt::Alignment align);
    void setTitleIcon(const QIcon &icon);
    void setMinimumIcon(const QIcon &icon);
    void setMaximumIcon(const QIcon &icon);
    void setCloseIcon(const QIcon &icon);
    void setTitleBarStyleSheet(const QString &styleSheet);
    void setDragable(bool isDragable);
    void setButtonStyle(TitleBarButtonFlag flags);
    void setCloseButtonAble(bool enable);

    void init();

protected:
    /* 用于实现拖拽效果 */
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *);
    void mouseDoubleClickEvent(QMouseEvent *event);


public slots:

    void minimizePtnClicked();
    void maximizePtnClicked();
    void closePtnClicked();

private:
    Ui::MAP_GUI_TitleBar *ui;
    /** 存储窗口坐标系统和桌面坐标的差值，用于转换 */
    QPoint m_Offset;
    /** 控制能否拖拽 */
    bool m_isDragable;
};

#endif // SE_GUI_TITLEBAR_H

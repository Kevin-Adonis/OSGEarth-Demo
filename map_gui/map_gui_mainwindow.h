#ifndef MAP_GUI_MAINWINDOW_H
#define MAP_GUI_MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MAP_GUI_MainWindow;
}

class QMdiArea;
class QGridLayout;
class QDockWidget;
class QPushButton;
class QMenu;
class QAction;
class QTreeWidget;
class QTabWidget;
class QSplitter;
class QTreeView;
class MAP_GUI_DockWidgetTitleBar;
class MAP_GUI_CurrentInfoView;
class MAP_GUI_ShowView;
class MAP_GUI_EntityInfoView;
class MAP_GR_TemplateLibTreeModel;
class MAP_OSG_BaseViewer;

class MAP_GUI_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MAP_GUI_MainWindow *getInstance();
    ~MAP_GUI_MainWindow() override;

public slots:
    void createProject(bool);

private slots:
    /**
     * @brief drawingPrimitivePtnClicked
     * 响应一系列绘制图元的命令，根据具体sender设定对应的Mode
     */
    void drawingPrimitivePtnClicked();

    /**
     * @brief closeEvent
     * 界面关闭时，程序自动退出
     * @param event
     */
    virtual void closeEvent(QCloseEvent *event) override;

    /**
     * @brief on_m_latlongGridPtn_clicked
     * 切换显示经纬网络
     */
    void on_m_latlongGridPtn_clicked();

	void on_m_DistancePtn_clicked();
    /**
     * @brief on_m_conventionPtn_clicked
     * 常规显示（即不能漫游）
     */
    void on_m_conventionPtn_clicked();

    /**
     * @brief on_m_romaingPtn_clicked
     * 漫游操控
     */
    void on_m_romaingPtn_clicked();

    /**
     * @brief on_m_magnifyEarthPtn_clicked
     * 放大地图
     */
    void on_m_magnifyEarthPtn_clicked();

    /**
     * @brief on_m_reduceEarthPtn_clicked
     * 缩小地图
     */
    void on_m_reduceEarthPtn_clicked();
    /**
     * @brief on_m_directionPth_clicked
     * 显示指南针
     */
    void on_m_directionPth_clicked();

    void on_m_layerControllerPtn_clicked();

private:
    explicit MAP_GUI_MainWindow(QWidget *parent = nullptr);
    Ui::MAP_GUI_MainWindow *ui;
    static MAP_GUI_MainWindow *instance;

    QMainWindow *m_centralWidget;

    QSplitter *m_centralLayout;
    QTabWidget *m_centralTab;
    QTabWidget *m_rightAttrTab;
    QMainWindow *m_central3DMapCanvas;
    MAP_OSG_BaseViewer *m_osgWidget;

    QPushButton *m_FileButton;
    QMenu *m_FileMenu;

    QAction *m_CreateAction;
    QAction *m_OpenAction;
    QAction *m_EditAction;
    QAction *m_SaveAction;

    QWidget *m_templateWidget;
    QGridLayout *m_templateGrid;
    QDockWidget *m_templateDock;
    MAP_GUI_DockWidgetTitleBar *m_templateDockTitleBar;
    QTreeWidget *m_templateTree;
    MAP_GR_TemplateLibTreeModel *m_templateTreeModel;

    QWidget *m_entityListWidget;
    QGridLayout *m_entityListGrid;
    QDockWidget *m_entityListDock;
    MAP_GUI_DockWidgetTitleBar *m_entityListDockTitleBar;
    QTreeWidget *m_entityListTree;
    //MAP_GR_EntityTreeModel* m_entityTreeModel;

    MAP_GUI_CurrentInfoView *m_currentInfoView;
    MAP_GUI_ShowView *m_showView;
    MAP_GUI_EntityInfoView *m_entityInfoView;

    QDockWidget *m_layerControlDock;
};

#endif // MAP_GUI_MAINWINDOW_H

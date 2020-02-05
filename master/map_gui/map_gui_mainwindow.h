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
    ~MAP_GUI_MainWindow();

public slots:
    void createProject(bool);

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

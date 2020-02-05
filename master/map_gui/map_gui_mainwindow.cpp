#include <QFile>
#include <QPushButton>
#include <QMenu>
#include <QSplitter>
#include <QTreeView>
#include <QDockWidget>
#include <QTreeWidget>
#include <QMdiArea>
#include <QStyleFactory>
#include <QTreeWidgetItem>
#include "map_gui_mainwindow.h"
#include "ui_map_gui_mainwindow.h"
#include "map_gui/map_gui_currentinfoview.h"
#include "map_gui/map_gui_entityinfoview.h"
#include "map_gui/map_gui_showview.h"
#include "map_gui/map_gui_dockwidgettitlebar.h"
#include "map_osg/map_osg_viewcontroller.h"
#include "map_osg/map_osg_layercontrolwidget.h"
#include "map_globaldata/map_globaldata_appdata.h"
#include "map_dlg/map_dlg_dialogfactory.h"

MAP_GUI_MainWindow *MAP_GUI_MainWindow::instance = nullptr;

MAP_GUI_MainWindow::MAP_GUI_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MAP_GUI_MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    m_centralWidget = new QMainWindow(this);
    ui->gridLayout_2->addWidget(m_centralWidget);
    ui->gridLayout_2->setRowStretch(0, 30);
    ui->gridLayout_2->setRowStretch(1, 90);
    ui->gridLayout_2->setRowStretch(2, 680);

    //中间地图显示
    m_central3DMapCanvas = new QMainWindow();
//    m_osgWidget = MAP_OSG_ViewController::addView(
//                      "F:\\QT\\build-OSG-Debug\\glider.osg");
    m_osgWidget = MAP_OSG_ViewController::addView(
                      qApp->applicationDirPath() + QString("/example_data/base.earth"));
    m_central3DMapCanvas->setCentralWidget(m_osgWidget);
    m_centralLayout = new QSplitter();

    m_centralTab = new QTabWidget();
    m_centralTab->tabBar()->setObjectName("m_centralTab");
    m_centralTab->addTab(new QWidget(), QString(u8"2D显示"));
    m_centralTab->addTab(m_central3DMapCanvas, QString(u8"3D显示"));
    m_centralTab->setCurrentIndex(1);

    //图层控制窗口
    MAP_OSG_LayerControlWidget *layer = new MAP_OSG_LayerControlWidget(m_osgWidget, this);
    m_layerControlDock = new QDockWidget(QString(u8"图层控制"), this);
    m_layerControlDock->setFloating(true);
    m_layerControlDock->setWidget(layer);

    //右侧信息栏
    m_rightAttrTab = new QTabWidget();
    m_rightAttrTab->tabBar()->setObjectName("m_rightAttrTab");

    m_entityInfoView = new MAP_GUI_EntityInfoView();
    m_rightAttrTab->addTab(m_entityInfoView, QString(u8"自身信息"));

    m_currentInfoView = new MAP_GUI_CurrentInfoView();
    m_rightAttrTab->addTab(m_currentInfoView, QString(u8"当前信息"));

    m_showView = new MAP_GUI_ShowView();
    m_rightAttrTab->addTab(m_showView, QString(u8"显示"));

    m_centralLayout->setObjectName("centralLayout");
    m_centralLayout->addWidget(m_centralTab);
    m_centralLayout->addWidget(m_rightAttrTab);
    m_centralLayout->setStretchFactor(0, 4);
    m_centralLayout->setStretchFactor(1, 1);
    m_centralLayout->setHandleWidth(6);
    m_centralWidget->setCentralWidget(m_centralLayout);

    //文件菜单栏
    m_FileButton = new QPushButton(u8"文件",this);
    m_FileButton->setObjectName("m_FilePtn");
    m_FileMenu = new QMenu(u8"文件");
    m_FileButton->setMenu(m_FileMenu);
    ui->RibbornMenu->setCornerWidget(m_FileButton, Qt::TopLeftCorner);

    m_FileMenu->setSeparatorsCollapsible(true);
    m_CreateAction = m_FileMenu->addAction(u8"新建");
    m_OpenAction = m_FileMenu->addAction(u8"打开");
    m_EditAction = m_FileMenu->addAction(u8"编辑");
    m_SaveAction = m_FileMenu->addAction(u8"保存");
    m_FileMenu->addSeparator();


    //左侧模板库浮窗
    m_templateDock = new QDockWidget(QString(u8"可部署实体模板库"), this);
    m_templateWidget = new QWidget(m_templateDock);
    m_templateGrid = new QGridLayout();
    m_templateDockTitleBar = new MAP_GUI_DockWidgetTitleBar(m_templateDock);
    m_templateDockTitleBar->setTitleBarTitle(u8"可部署实体模板库");
    m_templateDock->setTitleBarWidget(m_templateDockTitleBar);
    m_templateTree = new QTreeWidget(m_templateDock);
    m_templateTree->setHeaderHidden(true);
    m_templateGrid->setSpacing(0);
    m_templateGrid->setContentsMargins(0, 0, 2, 0);
    m_templateGrid->addWidget(m_templateTree);
    m_templateWidget->setLayout(m_templateGrid);
    m_templateDock->setWidget(m_templateWidget);

    m_entityListDock = new QDockWidget(QString(u8"已部署实体列表"), this);
    m_entityListWidget = new QWidget(m_entityListDock);
    m_entityListGrid = new QGridLayout();
    m_entityListDockTitleBar = new MAP_GUI_DockWidgetTitleBar(m_entityListDock);
    m_entityListDockTitleBar->setTitleBarTitle(u8"已部署实体列表");
    m_entityListDock->setTitleBarWidget(m_entityListDockTitleBar);
    m_entityListTree = new QTreeWidget(m_entityListDock);
    m_entityListTree->setHeaderHidden(true);
    m_entityListGrid->setSpacing(0);
    m_entityListGrid->setContentsMargins(0, 0, 2, 0);
    m_entityListGrid->addWidget(m_entityListTree);
    m_entityListWidget->setLayout(m_entityListGrid);
    m_entityListDock->setWidget(m_entityListWidget);

    m_centralWidget->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    m_centralWidget->addDockWidget(Qt::LeftDockWidgetArea, m_templateDock);
    m_centralWidget->addDockWidget(Qt::LeftDockWidgetArea, m_entityListDock);


    QFile qss(":/QSS/qss/TotalQSS.qss");
    if (qss.open(QIODevice::ReadOnly))
    {
        QString styleSheet = qss.readAll();
        setStyleSheet(styleSheet);
    }
    ui->mapTitle->maximizePtnClicked();

    MAP_GLOBALDATA_Controller::mainWindowController->registerWidget(this);
    MAP_GLOBALDATA_Controller::entityViewController->registerWidget(m_entityInfoView);
    MAP_GLOBALDATA_Controller::currInfoViewController->registerWidget(m_currentInfoView);
    MAP_GLOBALDATA_Controller::showViewController->registerWidget(m_showView);

    //connect
    connect(m_CreateAction, &QAction::triggered, this, &MAP_GUI_MainWindow::createProject);


    //添加测试item
    m_templateTree->setStyle(QStyleFactory::create("windows"));
    m_entityListTree->setStyle(QStyleFactory::create("windows"));

    QTreeWidgetItem *templateRoot = new QTreeWidgetItem(m_templateTree);
    templateRoot->setText(0, QString(u8"Demo模型"));
    QTreeWidgetItem *templateNode1 = new QTreeWidgetItem(templateRoot);
    templateNode1->setText(0, QString(u8"Demo雷达站"));
    QTreeWidgetItem *templateNode2 = new QTreeWidgetItem(templateRoot);
    templateNode2->setText(0, QString(u8"Demo预警机"));
    QTreeWidgetItem *templateNode3 = new QTreeWidgetItem(templateRoot);
    templateNode3->setText(0, QString(u8"Demo战斗机"));
    QTreeWidgetItem *templateNode4 = new QTreeWidgetItem(templateRoot);
    templateNode4->setText(0, QString(u8"Demo指挥所"));
    QTreeWidgetItem *templateNode5 = new QTreeWidgetItem(templateRoot);
    templateNode5->setText(0, QString(u8"Simplieplane"));


    QTreeWidgetItem *entityListRoot = new QTreeWidgetItem(m_entityListTree);
    entityListRoot->setText(0, QString(u8"红方"));
    QTreeWidgetItem *entityListNode1 = new QTreeWidgetItem(entityListRoot);
    entityListNode1->setText(0, QString(u8"通用指挥所"));
    QTreeWidgetItem *entityListNode2 = new QTreeWidgetItem(entityListRoot);
    entityListNode2->setText(0, QString(u8"机场"));
    QTreeWidgetItem *entityListNode3 = new QTreeWidgetItem(entityListRoot);
    entityListNode3->setText(0, QString(u8"Demo雷达站32"));
    QTreeWidgetItem *entityListNode4 = new QTreeWidgetItem(entityListRoot);
    entityListNode4->setText(0, QString(u8"Demo雷达站21"));
    QTreeWidgetItem *entityListNode5 = new QTreeWidgetItem(entityListRoot);
    entityListNode5->setText(0, QString(u8"Demo雷达站33"));

    QTreeWidgetItem *entityListRoot2 = new QTreeWidgetItem(m_entityListTree);
    entityListRoot2->setText(0, QString(u8"蓝方"));
    QTreeWidgetItem *entityListNode6 = new QTreeWidgetItem(entityListRoot2);
    entityListNode6->setText(0, QString(u8"轰炸机"));
    QTreeWidgetItem *entityListNode7 = new QTreeWidgetItem(entityListRoot2);
    entityListNode7->setText(0, QString(u8"雷达站"));
    QTreeWidgetItem *entityListNode8 = new QTreeWidgetItem(entityListRoot2);
    entityListNode8->setText(0, QString(u8"通用指挥所"));
    QTreeWidgetItem *entityListNode9 = new QTreeWidgetItem(entityListRoot2);
    entityListNode9->setText(0, QString(u8"Demo雷达站1"));
    QTreeWidgetItem *entityListNode10 = new QTreeWidgetItem(entityListRoot2);
    entityListNode10->setText(0, QString(u8"Demo雷达站333"));
}

MAP_GUI_MainWindow::~MAP_GUI_MainWindow()
{
    MAP_OSG_ViewController::removeView(m_osgWidget);
    delete ui;
}

void MAP_GUI_MainWindow::createProject(bool)
{
    MAP_DLG_TemplateDialog* dialog = MAP_DLG_TemplateDialogFactory::getFactoryInstance()->createProjectDialog();
    dialog->exec();
}

MAP_GUI_MainWindow *MAP_GUI_MainWindow::getInstance()
{
    if (instance == nullptr)
        instance = new MAP_GUI_MainWindow;
    return instance;
}

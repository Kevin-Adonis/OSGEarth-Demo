#include "map_gui_titlebar.h"
#include "ui_map_gui_titlebar.h"
#include <QMouseEvent>
#include <QFile>
#include <QPaintEvent>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

#include <QDebug>

MAP_GUI_TitleBar::MAP_GUI_TitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MAP_GUI_TitleBar)
{
    ui->setupUi(this);
    ui->m_TitleBarTitleLabel->setMouseTracking(true);
    init();
}

MAP_GUI_TitleBar::~MAP_GUI_TitleBar()
{
    delete ui;
}

void MAP_GUI_TitleBar::setTitleBarTitle(const QString &title, Qt::Alignment align)
{
    ui->m_TitleBarTitleLabel->setText(title);
    ui->m_TitleBarTitleLabel->setAlignment(align);
}

void MAP_GUI_TitleBar::setTitleIcon(const QIcon &icon)
{
    ui->m_TitleBarIconBtn->setIcon(icon);
}

void MAP_GUI_TitleBar::setMinimumIcon(const QIcon &icon)
{
    ui->m_TitleBarMinimizePtn->setIcon(icon);
}

void MAP_GUI_TitleBar::setMaximumIcon(const QIcon &icon)
{
    ui->m_TitleBarMaximizePtn->setIcon(icon);
}

void MAP_GUI_TitleBar::setCloseIcon(const QIcon &icon)
{
    ui->m_TitleBarClosePtn->setIcon(icon);
}

void MAP_GUI_TitleBar::setTitleBarStyleSheet(const QString &styleSheet)
{
    setStyleSheet(styleSheet);
}

void MAP_GUI_TitleBar::setDragable(bool isDragable)
{
    m_isDragable = isDragable;
}

void MAP_GUI_TitleBar::setButtonStyle(TitleBarButtonFlag flags)
{
    switch (flags)
    {
    case NOMAXIMIZEBUTTON:
        ui->m_TitleBarMaximizePtn->setVisible(false);
        ui->m_TitleBarIconBtn2->setVisible(false);
        ui->m_TitleBarIconBtn3->setVisible(false);
        break;
    case NOHELPBUTTON:
        ui->m_TitleBarIconBtn2->setVisible(false);
        ui->m_TitleBarIconBtn3->setVisible(false);
        break;
    case NOMAXIMIZEANDMINIMIZEBUTTON:
        ui->m_TitleBarIconBtn2->setVisible(false);
        ui->m_TitleBarIconBtn3->setVisible(false);
        ui->m_TitleBarMaximizePtn->setVisible(false);
        ui->m_TitleBarMinimizePtn->setVisible(false);
        break;
    case NOFLAGICONANDMAXMINBUTTON:
        ui->m_TitleBarMaximizePtn->setVisible(false);
        ui->m_TitleBarMinimizePtn->setVisible(false);
        ui->m_TitleBarIconBtn2->setVisible(false);
        ui->m_TitleBarIconBtn3->setVisible(false);
        break;
    case NOBUTTON:
        ui->m_TitleBarIconBtn2->setVisible(false);
        ui->m_TitleBarIconBtn3->setVisible(false);
        ui->m_TitleBarMaximizePtn->setVisible(false);
        ui->m_TitleBarMinimizePtn->setVisible(false);
        ui->m_TitleBarClosePtn->setVisible(false);
    }
}

void MAP_GUI_TitleBar::setCloseButtonAble(bool enable)
{
    ui->m_TitleBarClosePtn->setEnabled(enable);
}

void MAP_GUI_TitleBar::init()
{
    m_isDragable = true;
    QFile qss(":/QSS/qss/qss_For_map_gui/mainWindowTitleBar.qss");
    if (qss.open(QIODevice::ReadOnly))
    {
        QString styleSheet = qss.readAll();
        setStyleSheet(styleSheet);
    }
    this->setMouseTracking(true);
    ui->m_TitleBarMinimizePtn->setToolTip(u8"最小化");
    ui->m_TitleBarMaximizePtn->setToolTip(u8"最大化");
    ui->m_TitleBarClosePtn->setToolTip(u8"关闭");


    connect(ui->m_TitleBarMinimizePtn, &QPushButton::clicked, this, &MAP_GUI_TitleBar::minimizePtnClicked);
    connect(ui->m_TitleBarMaximizePtn, &QPushButton::clicked, this, &MAP_GUI_TitleBar::maximizePtnClicked);
    connect(ui->m_TitleBarClosePtn, &QPushButton::clicked, this, &MAP_GUI_TitleBar::closePtnClicked);
}

void MAP_GUI_TitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_isDragable)
    {
        QWidget *l_PWindow = this->window();
        m_Offset = event->globalPos() - l_PWindow->pos();
    }
    return QWidget::mousePressEvent(event);
}

void MAP_GUI_TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    QWidget *l_PWindow = this->window();
    if (event->buttons() & Qt::LeftButton && !l_PWindow->isMaximized() && m_isDragable)
    {
        QPoint l_TargetOrdinate;
        l_TargetOrdinate = event->globalPos() - m_Offset; 
        l_PWindow->move(l_TargetOrdinate);
    }
    QWidget::repaint();
    return QWidget::mouseMoveEvent(event);
}

void MAP_GUI_TitleBar::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}

void MAP_GUI_TitleBar::minimizePtnClicked()
{
    QWidget *l_PWindow = this->window();
    l_PWindow->showMinimized();
}

void MAP_GUI_TitleBar::maximizePtnClicked()
{
    QWidget *l_PWindow = this->window();
    if (l_PWindow->isMaximized())
    {
        ui->m_TitleBarMaximizePtn->setIcon(QIcon(":/Icon/icon/maxmize-normal-black.png"));
        ui->m_TitleBarMaximizePtn->setToolTip(u8"最大化");
        l_PWindow->showNormal();
    }
    else
    {
        ui->m_TitleBarMaximizePtn->setIcon(QIcon(":/Icon/icon/maxmize-max-balck.png"));
        ui->m_TitleBarMaximizePtn->setToolTip(u8"向下还原");
        l_PWindow->showMaximized();
    }
}

void MAP_GUI_TitleBar::closePtnClicked()
{
    QWidget *l_PWindow = this->window();
    l_PWindow->close();
}

void MAP_GUI_TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    maximizePtnClicked();
}

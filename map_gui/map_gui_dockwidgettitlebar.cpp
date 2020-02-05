#include "map_gui_dockwidgettitlebar.h"
#include "ui_map_gui_dockwidgettitlebar.h"
#include <QIcon>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QStyle>
#include <QStyleOption>

MAP_GUI_DockWidgetTitleBar::MAP_GUI_DockWidgetTitleBar(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MAP_GUI_DockWidgetTitleBar)
{
    ui->setupUi(this);

    ui->titleIcon->setVisible(false);
    this->setStyleSheet("QFrame#dockFrame {border: 3px;"
                        "background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #D8E9FF, stop:1 #B7D8FF);}"
                        "QPushButton {border: none;"
                        "background: transparent;}"
                        "QPushButton:hover {background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #F7F5F4, stop:1 #EFE8CF);}"
                        "QPushButton:pressed {background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #FDCE8B, stop:1 #FDC15D);}"
                        "QLabel {color: black;}");
}

MAP_GUI_DockWidgetTitleBar::~MAP_GUI_DockWidgetTitleBar()
{
    delete ui;
}

void MAP_GUI_DockWidgetTitleBar::setTitleBarTitle(const QString &title)
{
    ui->titleLabel->setText(title);
}

void MAP_GUI_DockWidgetTitleBar::setTitleIcon(const QIcon &icon)
{
    ui->titleIcon->setIcon(icon);
}

void MAP_GUI_DockWidgetTitleBar::on_closePtn_clicked()
{
    parentWidget()->close();
}

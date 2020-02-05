#include "map_gui_entityinfoview.h"
#include "ui_map_gui_entityinfoview.h"

MAP_GUI_EntityInfoView::MAP_GUI_EntityInfoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MAP_GUI_EntityInfoView)
{
    ui->setupUi(this);
    ui->planeEntity->setVisible(true);
    ui->shipEntity->setVisible(false);
    ui->radarEntity->setVisible(false);
    ui->groundEntity->setVisible(false);
}

MAP_GUI_EntityInfoView::~MAP_GUI_EntityInfoView()
{
    delete ui;
}

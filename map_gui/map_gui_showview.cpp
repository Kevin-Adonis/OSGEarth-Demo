#include "map_gui_showview.h"
#include "ui_map_gui_showview.h"

MAP_GUI_ShowView::MAP_GUI_ShowView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MAP_GUI_ShowView)
{
    ui->setupUi(this);
}

MAP_GUI_ShowView::~MAP_GUI_ShowView()
{
    delete ui;
}

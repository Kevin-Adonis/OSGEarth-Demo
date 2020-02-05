#include "map_gui_currentinfoview.h"
#include "ui_map_gui_currentinfoview.h"

MAP_GUI_CurrentInfoView::MAP_GUI_CurrentInfoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MAP_GUI_CurrentInfoView)
{
    ui->setupUi(this);
}

MAP_GUI_CurrentInfoView::~MAP_GUI_CurrentInfoView()
{
    delete ui;
}

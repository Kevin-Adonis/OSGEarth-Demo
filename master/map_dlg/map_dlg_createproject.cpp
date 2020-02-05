#include "map_dlg_createproject.h"
#include "ui_map_dlg_createproject.h"
#include "ui_map_dlg_templatedialog.h"
#include <QFile>

MAP_DLG_CreateProject::MAP_DLG_CreateProject(QWidget *parent) :
    MAP_DLG_TemplateDialog(parent),
    ui(new Ui::MAP_DLG_CreateProject)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    MAP_DLG_TemplateDialog::useFrame(ui->m_subWidget, this->width(), this->height());

    m_templateUI->m_templateTitleBar->setTitleIcon(QIcon(":/Icon/icon/world.png"));
    m_templateUI->m_templateTitleBar->setTitleBarTitle(u8"创建项目", Qt::AlignCenter);
}

MAP_DLG_CreateProject::~MAP_DLG_CreateProject()
{
    delete ui;
}

#include "map_dlg_primitiveconfigdialog.h"
#include "ui_map_dlg_primitiveconfigdialog.h"
#include "ui_map_dlg_templatedialog.h"


MAP_DLG_PrimitiveConfigDialog::MAP_DLG_PrimitiveConfigDialog(QWidget *parent) :
    MAP_DLG_TemplateDialog(parent),
    ui(new Ui::MAP_DLG_PrimitiveConfigDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    MAP_DLG_TemplateDialog::useFrame(ui->m_configWidget, this->width(), this->height());

    m_templateUI->m_templateTitleBar->setTitleIcon(QIcon(":/Icon/icon/world.png"));
    m_templateUI->m_templateTitleBar->setTitleBarTitle(u8"添加图形", Qt::AlignCenter);

    ui->m_nameWidget->setVisible(true);
    ui->m_showModeWidget->setVisible(true);
    ui->m_groupWidget->setVisible(true);
    ui->m_modeWidget->setVisible(false);
    ui->m_heightWidget->setVisible(false);

    this->setFocus();
}

MAP_DLG_PrimitiveConfigDialog::~MAP_DLG_PrimitiveConfigDialog()
{
    delete ui;
}

void MAP_DLG_PrimitiveConfigDialog::setupPointUI()
{
    ui->m_nameWidget->setVisible(true);
    ui->m_showModeWidget->setVisible(true);
    ui->m_groupWidget->setVisible(true);
    ui->m_modeWidget->setVisible(false);
    ui->m_heightWidget->setVisible(false);
}

void MAP_DLG_PrimitiveConfigDialog::setupLineUI()
{
    ui->m_nameWidget->setVisible(true);
    ui->m_showModeWidget->setVisible(true);
    ui->m_groupWidget->setVisible(true);
    ui->m_modeWidget->setVisible(true);
    ui->m_heightWidget->setVisible(true);
}

void MAP_DLG_PrimitiveConfigDialog::closeEvent(QCloseEvent *)
{
    emit accepted();
}

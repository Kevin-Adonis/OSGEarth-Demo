#include "map_dlg_templatedialog.h"
#include "ui_map_dlg_templatedialog.h"
#include <QFile>

MAP_DLG_TemplateDialog::MAP_DLG_TemplateDialog(QWidget *parent) :
    QDialog(parent),
    m_templateUI(new Ui::MAP_DLG_TemplateDialog)
{
}

MAP_DLG_TemplateDialog::~MAP_DLG_TemplateDialog()
{
    delete m_templateUI;
}

void MAP_DLG_TemplateDialog::useFrame(QWidget *widget, int w, int h)
{
    m_templateUI->setupUi(this);
    m_templateUI->m_extendableLayout->addWidget(widget);
    if(w != 0 && h != 0)
        this->resize(w, h);

    QFile qss(":/QSS/qss/TotalQSS.qss");
    if (qss.open(QIODevice::ReadOnly))
    {
        QString styleSheet = qss.readAll();
        setStyleSheet(styleSheet);
    }
    m_templateUI->m_templateTitleBar->setButtonStyle(TitleBarButtonFlag::NOFLAGICONANDMAXMINBUTTON);
    m_templateUI->m_templateTitleBar->setTitleIcon(QIcon(":/Icon/icon/world.png"));
    m_templateUI->m_templateTitleBar->setTitleBarTitle(u8"标题栏", Qt::AlignCenter);
    m_templateUI->m_templateTitleBar->setDragable(true);
    this->setWindowFlag(Qt::FramelessWindowHint);

    connect(m_templateUI->m_applicationButton, &QPushButton::clicked,
            this, &MAP_DLG_TemplateDialog::applicationHandle);
    connect(m_templateUI->m_cancelButton, &QPushButton::clicked,
            this, &MAP_DLG_TemplateDialog::cancelHandle);
}

void MAP_DLG_TemplateDialog::hideButtonBox()
{
    if(!m_templateUI->m_applicationButton)
        return;
    m_templateUI->m_applicationButton->setHidden(true);
    m_templateUI->m_cancelButton->setHidden(true);
}

void MAP_DLG_TemplateDialog::showButtonBox()
{
    if(!m_templateUI->m_applicationButton)
        return;
    m_templateUI->m_applicationButton->setHidden(false);
    m_templateUI->m_cancelButton->setHidden(false);
}

void MAP_DLG_TemplateDialog::applicationHandle(bool)
{
    this->accept();
}

void MAP_DLG_TemplateDialog::cancelHandle(bool)
{
    this->reject();
}

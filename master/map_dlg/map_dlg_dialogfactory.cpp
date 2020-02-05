#include "map_dlg_dialogfactory.h"
#include "map_dlg/map_dlg_createproject.h"
#include "map_dlg/map_dlg_templatedialog.h"
#include <QDialog>

MAP_DLG_TemplateDialogFactory * MAP_DLG_TemplateDialogFactory::instance = nullptr;

MAP_DLG_DialogFactory::MAP_DLG_DialogFactory(QObject *parent) : QObject(parent)
{

}

MAP_DLG_TemplateDialogFactory::MAP_DLG_TemplateDialogFactory(QObject *parent)
{

}

QDialog *MAP_DLG_TemplateDialogFactory::createDialog(QWidget *parent)
{
    QDialog *dialog =  new QDialog(parent);
    return dialog;
}

MAP_DLG_TemplateDialog *MAP_DLG_TemplateDialogFactory::createProjectDialog(QWidget *parent)
{
    MAP_DLG_TemplateDialog *dialog =  new MAP_DLG_CreateProject(parent);
    return dialog;
}

MAP_DLG_TemplateDialog *MAP_DLG_TemplateDialogFactory::createTemplateDialog(QWidget *parent)
{
    MAP_DLG_TemplateDialog *dialog =  new MAP_DLG_TemplateDialog(parent);
    return dialog;
}

MAP_DLG_TemplateDialogFactory *MAP_DLG_TemplateDialogFactory::getFactoryInstance()
{
    if (instance == nullptr)
        instance = new MAP_DLG_TemplateDialogFactory();
    return instance;
}

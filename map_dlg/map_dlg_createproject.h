#ifndef MAP_DLG_CREATEPROJECT_H
#define MAP_DLG_CREATEPROJECT_H

#include <QDialog>
#include "map_dlg_templatedialog.h"

namespace Ui {
class MAP_DLG_CreateProject;
}

class MAP_DLG_CreateProject : public MAP_DLG_TemplateDialog
{
    Q_OBJECT

public:
    explicit MAP_DLG_CreateProject(QWidget *parent = nullptr);
    ~MAP_DLG_CreateProject();

private:
    Ui::MAP_DLG_CreateProject *ui;
};

#endif // MAP_DLG_CREATEPROJECT_H

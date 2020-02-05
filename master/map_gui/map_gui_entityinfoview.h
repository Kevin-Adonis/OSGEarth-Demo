#ifndef MAP_GUI_ENTITYINFOVIEW_H
#define MAP_GUI_ENTITYINFOVIEW_H

#include <QWidget>

namespace Ui {
    class MAP_GUI_EntityInfoView;
}

class MAP_GUI_EntityInfoView : public QWidget
{
    Q_OBJECT

public:
    explicit MAP_GUI_EntityInfoView(QWidget *parent = nullptr);
    ~MAP_GUI_EntityInfoView();

private:
    Ui::MAP_GUI_EntityInfoView *ui;
};

#endif // MAP_GUI_ENTITYINFOVIEW_H

#ifndef MAP_GUI_CURRENTINFOVIEW_H
#define MAP_GUI_CURRENTINFOVIEW_H

#include <QWidget>

namespace Ui {
    class MAP_GUI_CurrentInfoView;
}

class MAP_GUI_CurrentInfoView : public QWidget
{
    Q_OBJECT

public:
    explicit MAP_GUI_CurrentInfoView(QWidget *parent = nullptr);
    ~MAP_GUI_CurrentInfoView();

private:
    Ui::MAP_GUI_CurrentInfoView *ui;
};

#endif // MAP_GUI_CURRENTINFOVIEW_H

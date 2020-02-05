#ifndef MAP_GUI_SHOWVIEW_H
#define MAP_GUI_SHOWVIEW_H

#include <QWidget>

namespace Ui {
    class MAP_GUI_ShowView;
}

class MAP_GUI_ShowView : public QWidget
{
    Q_OBJECT

public:
    explicit MAP_GUI_ShowView(QWidget *parent = nullptr);
    ~MAP_GUI_ShowView();

private:
    Ui::MAP_GUI_ShowView *ui;
};

#endif // MAP_GUI_SHOWVIEW_H

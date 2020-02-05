#ifndef MAP_GUI_DROPPABLECANVAS_H
#define MAP_GUI_DROPPABLECANVAS_H

#include <QMainWindow>

class MAP_GUI_DroppableCanvas : public QMainWindow
{
    Q_OBJECT
public:
    explicit MAP_GUI_DroppableCanvas(QWidget *parent = nullptr);

signals:

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

public slots:
};

#endif // MAP_GUI_DROPPABLECANVAS_H

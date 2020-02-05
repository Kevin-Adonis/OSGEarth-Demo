#include <QMimeData>
#include <QApplication>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QTreeWidgetItem>

#include "map_gui_droppablecanvas.h"
#include "map_gui_testtreeview.h"
#include "map_globaldata/map_globaldata_appdata.h"

MAP_GUI_DroppableCanvas::MAP_GUI_DroppableCanvas(QWidget *parent) : QMainWindow(parent)
{
    setAcceptDrops(true);
}

void MAP_GUI_DroppableCanvas::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat(MAP_GUI_TestTreeView::draggableTestTreeType()))
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MAP_GUI_DroppableCanvas::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat(MAP_GUI_TestTreeView::draggableTestTreeType()))
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MAP_GUI_DroppableCanvas::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat(MAP_GUI_TestTreeView::draggableTestTreeType()))
    {
        QByteArray test = event->mimeData()->data(MAP_GUI_TestTreeView::draggableTestTreeType());
        QDataStream dataStreamTest(&test, QIODevice::ReadOnly);

        QString l_svgPath;
        while (true)
        {
            QString temp;
            dataStreamTest >> temp;
            if (temp.isEmpty())
                break;
            l_svgPath = temp;
        }

        MAP_GLOBALDATA_Controller::svgController->addSVG(
                    l_svgPath, event->pos().x(), this->height() - event->pos().y());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
        event->ignore();
}

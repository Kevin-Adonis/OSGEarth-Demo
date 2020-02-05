#include "map_gui_testtreeview.h"
#include <QMimeData>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QByteArray>
#include <QDataStream>
#include <QTreeWidgetItem>
#include <QApplication>
#include <QDebug>

MAP_GUI_TestTreeView::MAP_GUI_TestTreeView(QWidget *parent):QTreeWidget (parent)
{
    setDragEnabled(true);
    //setAcceptDrops(true);
    //setDropIndicatorShown(true);
}

void MAP_GUI_TestTreeView::dragEnterEvent(QDragEnterEvent *event)
{
    MAP_GUI_TestTreeView *l_Source = qobject_cast<MAP_GUI_TestTreeView*>
                                           (event->source());
    if (l_Source == this)
        return;
    if (event->mimeData()->hasFormat(
                MAP_GUI_TestTreeView::draggableTestTreeType()))
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MAP_GUI_TestTreeView::dragMoveEvent(QDragMoveEvent *event)
{
    MAP_GUI_TestTreeView *l_Source = qobject_cast<MAP_GUI_TestTreeView *>
                                            (event->source());
    if (l_Source == this)
        return;
    if (event->mimeData()->hasFormat(
                MAP_GUI_TestTreeView::draggableTestTreeType()))
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MAP_GUI_TestTreeView::dropEvent(QDropEvent *event)
{
    MAP_GUI_TestTreeView *l_Source = qobject_cast<MAP_GUI_TestTreeView *>
                                           (event->source());
    if (l_Source == this)
        return;
    if (event->mimeData()->hasFormat(
                MAP_GUI_TestTreeView::draggableTestTreeType()))
        event->accept();
    else
        event->ignore();
}

void MAP_GUI_TestTreeView::startDrag(Qt::DropActions supportedActions)
{
    Q_UNUSED(supportedActions);

    QTreeWidgetItem *l_Item = this->currentItem();

    if (l_Item == nullptr)
        return;

    QByteArray l_ItemData;
    QDataStream l_ItemDataStream(&l_ItemData, QIODevice::WriteOnly);

    QString l_svgPath = qApp->applicationDirPath() + u8"/Military/F_空警2000.svg";
    l_ItemDataStream << l_svgPath;

    QMimeData *l_ItemMimeData = new QMimeData;
    l_ItemMimeData->setData(MAP_GUI_TestTreeView::draggableTestTreeType(), l_ItemData);

    QDrag *l_Drag = new QDrag(this);
    l_Drag->setMimeData(l_ItemMimeData);
    //l_Drag->setHotSpot();
    //l_Drag->setPixmap();

    l_Drag->exec(Qt::MoveAction);
//    if (l_Drag->exec(Qt::MoveAction) == Qt::MoveAction);
//        qDebug()<<"drag successed";
}

#ifndef MAP_GUI_TESTTREEVIEW_H
#define MAP_GUI_TESTTREEVIEW_H

#include <QObject>
#include <QTreeView>
#include <QTreeWidget>

class MAP_GUI_TestTreeView : public QTreeWidget
{
    Q_OBJECT
public:
    MAP_GUI_TestTreeView(QWidget *parent = nullptr);


    static QString draggableTestTreeType() {return QStringLiteral("test/TestTreeView");}

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void startDrag(Qt::DropActions supportedActions) override;

};

#endif // MAP_GUI_TESTTREEVIEW_H

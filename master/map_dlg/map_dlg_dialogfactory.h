#ifndef MAP_DLG_DIALOGFACTORY_H
#define MAP_DLG_DIALOGFACTORY_H

#include <QObject>
#include "map_dlg/map_dlg_templatedialog.h"

class QDialog;
/**
 * @brief The MAP_DLG_DialogFactory class
 * 采用抽象工厂模式创建dlg类，目的是尽可能实现dlg的复用
 * 每一类对话框对应一个工厂，继承自DialogFactory
 * 建议相近的对话框可通过在相应的工厂创建时对同一个dialog类进行不同的调整实现复用
 * 其余部件创建对话框时建议采用工厂类创建对话框
 * 每次新对话框创建后建议添加工厂类
 * 每个工厂类建议是单例类
 */
class MAP_DLG_DialogFactory : public QObject
{
    Q_OBJECT
public:
    explicit MAP_DLG_DialogFactory(QObject *parent = nullptr);

    virtual QDialog* createDialog(QWidget *parent=nullptr) = 0;

signals:

public slots:
};

class MAP_DLG_TemplateDialogFactory : public MAP_DLG_DialogFactory
{
    Q_OBJECT

public:
    virtual QDialog* createDialog(QWidget *parent=nullptr);
    MAP_DLG_TemplateDialog* createTemplateDialog(QWidget *parent=nullptr);
    MAP_DLG_TemplateDialog* createProjectDialog(QWidget *parent=nullptr);

    static MAP_DLG_TemplateDialogFactory* getFactoryInstance();

private:
    explicit MAP_DLG_TemplateDialogFactory(QObject *parent = nullptr);
    static MAP_DLG_TemplateDialogFactory* instance;
};

#endif // MAP_DLG_DIALOGFACTORY_H

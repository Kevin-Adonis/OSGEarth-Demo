#include "map_osg_layercontrolwidget.h"
#include <QCheckBox>
#include <QLayout>
#include <osg/Notify>
#include <osgViewer/CompositeViewer>
#include <osgEarth/MapNode>

MAP_OSG_LayerControlWidget::MAP_OSG_LayerControlWidget(MAP_OSG_BaseViewer *viewer, QWidget *parent):
    QWidget(parent), m_viewer(viewer)
{
    if(m_viewer != nullptr)
        m_viewer->setControllWidget(this);

    setLayout(new QVBoxLayout);
    osgEarth::LayerVector vec;
    osgEarth::MapNode *node = osgEarth::MapNode::get(m_viewer->getView()->getSceneData());
    node->getMap()->getLayers(vec);

    for(const auto &layer : vec)
    {
        QCheckBox *checkBox = new QCheckBox(this);
        checkBox->setText(QString::fromStdString(layer->getName()));
        checkBox->setCheckable(true);
        checkBox->setChecked(layer->getEnabled());
        layout()->addWidget(checkBox);
        connect(checkBox, &QCheckBox::clicked, this, &MAP_OSG_LayerControlWidget::checkBoxStateChange);
    }
}

MAP_OSG_LayerControlWidget::~MAP_OSG_LayerControlWidget()
{
    m_viewer->setControllWidget(nullptr);
}

void MAP_OSG_LayerControlWidget::checkBoxStateChange(bool enabled)
{
    QCheckBox *checkBox = static_cast<QCheckBox *>(sender());
    osgEarth::MapNode *node = osgEarth::MapNode::get(m_viewer->getView()->getSceneData());
    osgEarth::Layer *layer = node->getMap()->getLayerByName(checkBox->text().toStdString());
    layer->setEnabled(enabled);
}

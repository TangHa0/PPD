#include "obstacle.h"

#include <QBrush>
#include <QLine>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

Obstacle::Obstacle(const QPolygonF &polygon, QGraphicsItem *parent, QGraphicsScene *scene) :
    QGraphicsPolygonItem(polygon, parent, scene)
{
    this->setBrush(QBrush(Qt::SolidPattern));
    this->setFlags(QGraphicsPolygonItem::ItemIsMovable);
}

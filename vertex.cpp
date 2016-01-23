#include "vertex.h"

#include <QBrush>

Vertex::Vertex(qreal x, qreal y, qreal w, qreal h, QColor color) :
    QGraphicsEllipseItem(x, y, w, h)
{
    this->setBrush(QBrush(color, Qt::SolidPattern));
    this->setFlags(QGraphicsPolygonItem::ItemIsMovable);
}

#ifndef VERTEX_H
#define VERTEX_H

#include <QGraphicsEllipseItem>

class Vertex : public QGraphicsEllipseItem
{
public:
    Vertex(qreal x, qreal y, qreal w, qreal h, QColor color);
};

#endif // VERTEX_H

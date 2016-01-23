#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsPolygonItem>

class Obstacle : public QGraphicsPolygonItem
{
public:
    Obstacle(const QPolygonF &polygon, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
};

#endif // OBSTACLE_H

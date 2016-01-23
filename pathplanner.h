#ifndef PATHPLANNER_H
#define PATHPLANNER_H

#include <vector>

#include <QPointF>
#include <QPolygonF>
#include <QGraphicsScene>

class PathPlanner
{
public:
    typedef std::vector<QPointF> Path;

    PathPlanner();

    virtual bool plan(const QPointF &source,
              const QPointF &terminal,
              const std::vector<QPolygonF> &polygons,
              const QGraphicsScene *scene,
              Path &path) = 0;
};

#endif // PATHPLANNER_H

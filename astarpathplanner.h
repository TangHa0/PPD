#ifndef ASTARPATHPLANNER_H
#define ASTARPATHPLANNER_H

#include "gridpathplanner.h"

class AStarPathPlanner : public GridPathPlanner
{
public:
    AStarPathPlanner();

    QString getName() const;

protected:
    bool plan(
            const QPoint &source,
            const QPoint &terminal,
            const GridMap &grid_map,
            const int rows,
            const int cols,
            const QGraphicsScene *scene,
            PathI &path);

private:
    double distance(const QPoint &p1, const QPoint &p2);
};

#endif // ASTARPATHPLANNER_H

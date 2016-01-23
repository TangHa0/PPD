#include "dijkstrapathplanner.h"

#include <QDebug>
#include <iostream>

DijkstraPathPlanner::DijkstraPathPlanner()
{
}

bool DijkstraPathPlanner::plan(const QPoint &source,
        const QPoint &terminal,
        const GridMap &grid_map, const int rows, const int cols,
        const QGraphicsScene *scene,
        PathI &path)
{

#if 1
    qDebug() << source;
    qDebug() << terminal;

    for (int j = 0; j < cols; ++j)
    {
        for (int i = 0; i < rows; ++i)
            std::cout << (grid_map[i][j] ? 1 : 0) << " ";
        std::cout << std::endl;
    }
#endif

    return true;
}

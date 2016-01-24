#include "visibilitygraphpathplanner.h"

#include <limits>

#include <QLine>

VisibilityGraphPathPlanner::VisibilityGraphPathPlanner()
{
}

bool VisibilityGraphPathPlanner::plan(const QPointF &source, const QPointF &terminal, const std::vector<QPolygonF> &polygons, const QGraphicsScene *scene, Path &path)
{
    std::vector<QLineF> polygon_lines;
    int N = 2;

    for (uint pg = 0; pg < polygons.size(); ++pg)
    {
        QPolygonF poly = polygons[pg];
        QPointF p1 = poly[poly.size()-1];
        for (int i = 0; i < poly.size(); ++i)
        {
            QPointF p2 = poly[i];
            polygon_lines.push_back(QLineF(p1, p2));
            p1 = p2;
            N++;
        }
    }

    std::vector<QPointF> vertex(N);
    std::vector<std::vector<double> > weight(N, std::vector<double>(N, -1));
    vertex[0] = source;
    vertex[1] = terminal;
    int first = 2;
    for (uint pg = 0; pg < polygons.size(); ++pg)
    {
        QPolygonF poly = polygons[pg];
        QPointF p1 = poly[poly.size() - 1];
        int last_i = poly.size() - 1;
        for (int i = 0; i < poly.size(); ++i)
        {
            QPointF p2 = poly[i];
            vertex[first + i] = p2;
            weight[first + i][first + last_i] = weight[first + last_i][first + i] = QLineF(p1, p2).length();
            p1 = p2;
        }

        first += poly.size();
    }

    QPointF tmp;
    for (uint i = 0; i < N; ++i)
    {
        for (uint j = i + 1; j < N; ++j)
        {
            QLineF ll(vertex[i], vertex[j]);
            QLineF nn = ll.unitVector();
            QPointF pp = nn.p2() - nn.p1();
            ll = QLineF(vertex[i] + pp, vertex[j] - pp);
            bool intersect = false;
            for (uint k = 0; k < polygon_lines.size(); ++k)
            {
                if (ll.intersect(polygon_lines[k], &tmp) == QLineF::BoundedIntersection)
                {
                    intersect = true;
                    break;
                }
            }
            if (!intersect)
                weight[j][i] = weight[i][j] = ll.length();
        }
    }

    std::vector<int> pathi;
    dijkstra(weight, 0, 1, pathi);

    path.resize(pathi.size());
    for (uint i = 0; i < pathi.size(); ++i)
    {
        path[i] = vertex[pathi[i]];
    }

    return true;
}

QString VisibilityGraphPathPlanner::getName() const
{
    return "Visibility Graph";
}

void VisibilityGraphPathPlanner::dijkstra(const std::vector<std::vector<double> > &weight_matrix, int source, int terminal, std::vector<int> &path)
{
    int N = weight_matrix.size();

    std::vector<bool> visited(N, false);
    std::vector<double> best(N, std::numeric_limits<double>::max());
    std::vector<double> parent(N, -1);
    best[source] = 0;

    for (int k = 0; k < N; ++k)
    {
        double min_dist = std::numeric_limits<double>::max();
        int min_index = -1;
        for (int i = 0; i < N; ++i)
        {
            if (!visited[i] && (min_dist > best[i]))
            {
                min_dist = best[i];
                min_index = i;
            }
        }

        visited[min_index] = true;

        if (min_index == terminal)
            break;

        for (int i = 0; i < N; ++i)
        {
            if (!visited[i] &&
                    weight_matrix[min_index][i] > 0 &&
                    min_dist + weight_matrix[min_index][i] < best[i])
            {
                best[i] = min_dist + weight_matrix[min_index][i];
                parent[i] = min_index;
            }
        }
    }

    std::vector<int> tmp_path;
    int cur = terminal;
    while (cur != -1)
    {
        tmp_path.push_back(cur);
        cur = parent[cur];
    }

    int n = tmp_path.size();
    path.resize(n);
    for (int i = 0; i < n; ++i)
        path[n - 1 - i] = tmp_path[i];
}

#include "polygonpathplanner.h"

#include <limits>

PolygonPathPlanner::PolygonPathPlanner()
{
}


void PolygonPathPlanner::dijkstra(const std::vector<std::vector<double> > &weight_matrix, int source, int terminal, std::vector<int> &path)
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

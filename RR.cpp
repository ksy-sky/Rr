#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
int max_distance = 0;
int farthest_node = 0;

// Функция DFS для нахождения дальнего узла
void dfs(int node, int distance, vector<bool>& visited) {
    visited[node] = true;

    if (distance > max_distance) {
        max_distance = distance;
        farthest_node = node;
    }

    for (int neighbor = 0; neighbor < graph[node].size(); neighbor++) {
        if (graph[node][neighbor] && !visited[neighbor]) {       //проверяем сущ ли ребро между точкой и соседней
            dfs(neighbor, distance + 1, visited);               // +1 переходим на один уровень в графе
        }
    }
}

// Функция для вычисления диаметра графа
int diameter(const vector<vector<int>>& adj_matrix) {
    graph = adj_matrix;
    max_distance = 0;
    vector<bool> visited(graph.size(), false);      //показывает какие узлы были посещены
    dfs(0, 0, visited);                  //находим мах раст и дальнюю точку от 0

    max_distance = 0;
    visited.assign(graph.size(), false);
    dfs(farthest_node, 0, visited);      // находим мах раст и дальнюю точку от дальней точки до всех возможных точек находящимся на мах расстоянии 

    return max_distance;
}

// Функция для поиска всех путей длиной диаметра
void findAllPaths(int curr, int end, vector<int>& path, vector<vector<int>>& all_paths, const vector<vector<int>>& adj_matrix, int d) {
    if (curr == end && path.size() - 1 == d) {          //curr==end достигает ли текущая точка конечную, -1 потому что считает и начальную точку
        all_paths.push_back(path);
        return;
    }

    for (int neighbor = 0; neighbor < adj_matrix.size(); neighbor++) {
        if (adj_matrix[curr][neighbor] && find(path.begin(), path.end(), neighbor) == path.end()) {          //есть ли ребро и добавлен ли узел в текущий путь
            path.push_back(neighbor);
            findAllPaths(neighbor, end, path, all_paths, adj_matrix, d);
            path.pop_back(); // Возврат к предыдущему состоянию
        }
    }
}

// Функция для построения графа пересечения диаметральных цепей
vector<vector<int>> intersection_of_diametral_chains(const vector<vector<int>>& adj_matrix) {
    int n = adj_matrix.size();
    int d = diameter(adj_matrix);
    vector<vector<int>> result(n, vector<int>(n, 0));

    // Проход по всем парам вершин
    for (int start = 0; start < n; ++start) {
        for (int end = 0; end < n; ++end) {
            if (start != end) {
                vector<vector<int>> all_paths;
                vector<int> path = { start };
                findAllPaths(start, end, path, all_paths, adj_matrix, d);

                // Проверка всех найденных путей
                cout << "Все пути длиной диаметра от " << start << " до " << end << ":" << endl;
                for (const auto& p : all_paths) {
                    cout << "Путь: ";
                    for (int v : p) {
                        cout << v << " ";
                    }
                    cout << endl;
                }

                // Добавляем рёбра, если они присутствуют в любом из всех путей
                for (const auto& path : all_paths) {
                    for (int i = 0; i < path.size() - 1; i++) {
                        int u = path[i], v = path[i + 1];
                        result[u][v] = 1;
                        result[v][u] = 1;
                    }
                }
            }
        }
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "RU");
    vector<vector<int>> adj_matrix = {
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0, 1},
        {0, 0, 1, 0, 1, 0},
        {1, 1, 0, 1, 0, 1},
        {0, 0, 1, 0, 1, 0}
    };

    int d = diameter(adj_matrix);
    cout << "Диаметр: " << d << endl;

    vector<vector<int>> result = intersection_of_diametral_chains(adj_matrix);
    cout << "Граф, являющийся пересечением множества всех диаметральных цепей:" << endl;
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Функция для вычисления диаметра графа
int diameter(const vector<vector<int>>& adj_matrix) {
    int n = adj_matrix.size();
    int diameter = 0;

    for (int i = 0; i < n; i++) {
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(i);             //добавление в очередь
        visited[i] = true;    //добавили = посетили
        int level = 0;      //расстояние

        while (!q.empty()) {
            int size = q.size();
            for (int j = 0; j < size; j++) {
                int u = q.front();     //изначальная вершина
                q.pop();               //удаляем из очереди
                for (int v = 0; v < n; v++) {      //находим её соседей      
                    if (adj_matrix[u][v] && !visited[v]) {
                        q.push(v);
                        visited[v] = true;
                    }
                }
            }
            level++;
        }

        diameter = max(diameter, level - 1);     //-1 потому что изначальная точка тоже учитывается
    }

    return diameter;
}

// Функция для построения графа, являющегося пересечением множества всех диаметральных цепей
vector<vector<int>> intersection_of_diametral_chains(const vector<vector<int>>& adj_matrix) {
    int n = adj_matrix.size();
    int d = diameter(adj_matrix);
    vector<vector<int>> result(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(i);
        visited[i] = true;
        int level = 0;

        while (!q.empty()) {
            int size = q.size();
            for (int j = 0; j < size; j++) {
                int u = q.front();
                q.pop();
                for (int v = 0; v < n; v++) {
                    if (adj_matrix[u][v] && !visited[v]) {
                        q.push(v);
                        visited[v] = true;
                    }
                }
            }

            // Проверяем, добавляются ли рёбра на уровне d
            if (level == d) {
                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < n; k++) {
                        if (adj_matrix[j][k]){
                            result[j][k] = 1;
                        }
                    }
                }
            }

            level++;
        }
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "RU");
    vector<vector<int>> adj_matrix = {
    {0, 1, 1, 0, 0},
    {1, 0, 0, 1, 0},
    {1, 0, 0, 0, 1},
    {0, 1, 0, 0, 1},
    {0, 0, 1, 1, 0}
    };
    vector<vector<int>> result = intersection_of_diametral_chains(adj_matrix);
    int d = diameter(adj_matrix);
    cout << "Диаметр: " << d << endl;

    cout << "Граф, являющийся пересечением множества всех диаметральных цепей:" << endl;
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

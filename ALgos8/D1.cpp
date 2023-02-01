#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

class Graph {
    int num_vertices;
    std::vector<int> *adc_matrix;
    bool *visited;
    int *group;
    int count;
public:
    Graph(int vertices) {
        num_vertices = vertices;
        adc_matrix = new std::vector<int>[vertices];
        visited = new bool[vertices];
        for (int i = 0; i < vertices; i++) {
            visited[i] = 0;
        }
        group = new int[vertices];
        count = 0;
    }
    void add_edge(int v1, int v2) {
        adc_matrix[v1].push_back(v2);
        adc_matrix[v2].push_back(v1);
    }
    void BFS() {
        for (int i = 0; i < num_vertices; i++) {
            if (visited[i] == 0) {
                count++;
                std::queue<int> q;
                q.push(i);
                visited[i] = 1;
                group[i] = count;

                while(!q.empty()) {
                    int v = q.front();
                    q.pop();

                    for (int j = 0; j < adc_matrix[v].size(); j++) {
                        if (visited[adc_matrix[v][j]] == 0) {
                            visited[adc_matrix[v][j]] = 1;
                            group[adc_matrix[v][j]] = count;
                            q.push(adc_matrix[v][j]);
                        }
                    }
                }
            }
        }
    }
    void print(std::ofstream &fout) {
        fout << count << std::endl;
        for (int i = 0; i < num_vertices; i++) {
            fout << group[i] << " ";
        }
    }
    ~Graph() {
        delete[] adc_matrix;
        delete[] visited;
        delete[] group;
    }
};

int main() {
    int n, m, x, y, count;
    count = 0;

    std::ifstream fin("components.in");
    std::ofstream fout("components.out");

    fin >> n >> m;
    Graph g(n);

    for (int i = 0; i < m; i++) {
        fin >> x >> y;
        g.add_edge(x-1, y-1);
    }
    
    g.BFS();

    g.print(fout);

    fin.close();
    fout.close();

    return 0;
}
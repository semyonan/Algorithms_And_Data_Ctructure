#include <cstring>
#include <vector>
#include <queue>
#include <fstream>

class Graph {
    int num_vertices;
    std::vector<int> *adc_matrix;
    bool *visited;
    int *dist;
public:
    Graph(int vertices) {
        num_vertices = vertices;
        adc_matrix = new std::vector<int>[vertices];
        visited = new bool[vertices];
        memset(visited, 0, sizeof(bool)*vertices);
        dist = new int[vertices];
        memset(dist, 0, sizeof(bool)*vertices);
    }
    void add_edge(int v1, int v2) {
        adc_matrix[v1].push_back(v2);
        adc_matrix[v2].push_back(v1);
    }
    void BFS() {
        std::queue<int> q;
        q.push(0);
        visited[0] = 1;
        dist[0] = 0;

        while(!q.empty()) {
            int v = q.front();
            q.pop();

            for (int j = 0; j < adc_matrix[v].size(); j++) {
                if (visited[adc_matrix[v][j]] == 0) {
                    if ((dist[adc_matrix[v][j]] > dist[v] + 1) || (dist[adc_matrix[v][j]] == 0)){
                        dist[adc_matrix[v][j]] = dist[v] + 1;
                    }
                        visited[adc_matrix[v][j]] = 1;
                        q.push(adc_matrix[v][j]);
                }
            }
        }
    }
    void print(std::ofstream &fout) {
        for (int i = 0; i < num_vertices; i++) {
            fout << dist[i] << " ";
        }
    }
    ~Graph() {
        delete[] adc_matrix;
        delete[] visited;
        delete[] dist;
    }
};

int main() {
    int n, m, x, y, count;
    count = 0;

    std::ifstream fin("pathbge1.in");
    std::ofstream fout("pathbge1.out");

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
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>

using namespace std;

class Graph {
    int height;
    int width;
    int *parent;
    vector<int> *adc_matrix;
    bool *visited;
    int *dist;
public:
    Graph(int h, int w) {
        height = h;
        width = w;
        adc_matrix = new vector<int>[h*w];
        visited = new bool[h*w];
        memset(visited, 0, sizeof(bool)*h*w);
        dist = new int[h*w];
        parent = new int[h*w];
        memset(dist, 0, sizeof(bool)*h*w);
    }

    void add_edge(int v1, int v2) {
        adc_matrix[v1].push_back(v2);
    }

    int BFS(int start, int end) {
        queue<int> q;
        q.push(start);
        visited[start] = 1;
        dist[start] = 0;
        parent[start] = -1;

        while(!q.empty()) {
            int v = q.front();
            q.pop();

            for (int j = 0; j < adc_matrix[v].size(); j++) {
                if (visited[adc_matrix[v][j]] == 0) {
                    if ((dist[adc_matrix[v][j]] > dist[v] + 1) || (dist[adc_matrix[v][j]] == 0)){
                        dist[adc_matrix[v][j]] = dist[v] + 1;
                    }
                    parent[adc_matrix[v][j]] = v;
                    visited[adc_matrix[v][j]] = 1;
                    q.push(adc_matrix[v][j]);
                    if (adc_matrix[v][j] == end) {
                        return 1;
                    }
                }
            }
        }
        return 0;
    }

    void print(std::ofstream &fout, int end) {
        fout << dist[end] << endl;
        stack<char> result;
        int i = end;
        while (parent[i] != -1) {
            if ((i == parent[i] + 1) && (width != 1)) {
                result.push('R');
            } else if ((i == parent[i] - 1) && (width != 1)) {
                result.push('L');
            } else if (i == parent[i] + width) {
                result.push('D');
            } else if (i == parent[i] - width) {
                result.push('U');
            }
            i = parent[i];
        }
        while (!result.empty()) {
            fout << result.top();
            result.pop();
        }
    }
    ~Graph() {
        delete[] parent;
        delete[] adc_matrix;
        delete[] visited;
        delete[] dist;
    }
};

int main() {
    int h, w, start, end;
    char c;

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
  
    fin >> h >> w;
    Graph g(h, w);

    char **matrix = new char*[h+2];
    for (int i = 0; i < h+2; i++) {
        matrix[i] = new char[w+2];
    }

    for (int i = 0; i < h+2; i++) {
        for (int j = 0; j < w+2; j++) {
            if ((i == 0) || (j == 0) || (i == h + 1) || (j == w + 1)) {
                matrix[i][j] = '#';
            } else {
                fin >> c;
                matrix[i][j] = c;
            }
        }
    }
    
    for (int i = 1; i < h + 1; i++) {
        for (int j = 1; j < w + 1; j++) {
            if (matrix[i][j] != '#') {
                if (matrix[i][j+1] != '#') {
                    g.add_edge((i-1)*w + j-1, (i-1)*w + j);
                }
                if (matrix[i+1][j] != '#') {
                    g.add_edge((i-1)*w + j-1, i*w + j-1);
                }
                if (matrix[i-1][j] != '#') {
                    g.add_edge((i-1)*w + j-1, (i-2)*w + j-1);
                }
                if (matrix[i][j-1] != '#') {
                    g.add_edge((i-1)*w + j-1, (i-1)*w + j - 2);
                }
                if (matrix[i][j] == 'S') {
                    start = (i-1)*w + j-1;
                }
                if (matrix[i][j] == 'T') {
                    end = (i-1)*w + j-1;
                }
            }
        }
    }
    
    if (!g.BFS(start, end)) {
        fout << -1;
    } else {
        g.print(fout, end);
    }

    fin.close();
    fout.close();

    return 0;
}
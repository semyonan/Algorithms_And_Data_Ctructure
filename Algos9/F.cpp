#include <vector>
#include <stack>
#include <fstream>
#include <iostream>
 
class Graph {
    int num_vertices;
    std::vector<std::vector<int>> adc_matrix;
    std::vector<bool> visited;
    std::vector<bool> svd_win;
public:
    Graph(int vertices) {
        num_vertices = vertices;
        adc_matrix.resize(vertices);
        visited.resize(vertices, 0);
        svd_win.resize(vertices, 0);
    }
    void add_edge(int v1, int v2) {
        adc_matrix[v1].push_back(v2);
    }
    void GFS(std::ofstream &fout, int v) {
        if (visit(v, true)) {
            fout << "First player wins" << std::endl;
        } else {
            fout << "Second player wins" << std::endl;
        }
    }
    bool visit(int v, bool color) {
        bool count;
        visited[v] = true;
        if (adc_matrix[v].size() == 0) {
            svd_win[v] = false;
            return !color;
        }
        for (int j = 0; j < adc_matrix[v].size(); j++) {
            if (visited[adc_matrix[v][j]] == 0) {
                count = visit(adc_matrix[v][j], !color);
            } else {
                if (svd_win[adc_matrix[v][j]] == false) {
                    count = color;
                } else {
                    count = !color;
                }
            }
            if (color == count)  {
                svd_win[v] = true;
                return color;
            }
        }
        svd_win[v] = false;
        return !color;
    }
};
  
int main() {
    int n, m, s, x, y;
  
    std::ifstream fin("game.in");
    std::ofstream fout("game.out");
  
    fin >> n >> m >> s;
    Graph g(n);
  
    for (int i = 0; i < m; i++) {
        fin >> x >> y;
        g.add_edge(x-1, y-1);
    }
      
    g.GFS(fout, s-1);
  
    fin.close();
    fout.close();
  
    return 0;
}
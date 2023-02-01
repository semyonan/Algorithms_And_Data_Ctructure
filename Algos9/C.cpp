#include <vector>
#include <stack>
#include <fstream>
#include <iostream>

class Graph {
    int num_vertices;
    std::vector<std::vector<int>> adc_matrix;
    std::vector<int> color;
public:
    Graph(int vertices) {
        num_vertices = vertices;
        adc_matrix.resize(vertices);
        color.resize(vertices);
        color.assign(vertices, 0);
    }
    void add_edge(int v1, int v2) {
        adc_matrix[v1].push_back(v2);
        adc_matrix[v2].push_back(v1);
    }
    int invert(int c) {
        if (c == 1) {
            return 2;
        } else {
            return 1;
        }
    }
    void GFS(std::ofstream &fout) {
        for(int i = 0; i < num_vertices; i++) {
            if (color[i] == 0) {
                if (visit(i,1)) {
                    fout << "NO" << std::endl;
                    return;
                }
            }
        }
        fout << "YES" << std::endl;
    }
    bool visit(int v, int c) {
        color[v] = c;
        for (int j = 0; j < adc_matrix[v].size(); j++) {
            if (color[adc_matrix[v][j]] == 0) {
                if (visit(adc_matrix[v][j], invert(c))) {
                    return true;
                }
            }  else if (color[adc_matrix[v][j]] == c) {
                return true;
            }
        }
        return false;
    }
};
 
int main() {
    int n, m, x, y;
 
    std::ifstream fin("INPUT.TXT");
    std::ofstream fout("OUTPUT.TXT");
 
    fin >> n >> m;
    Graph g(n);
 
    for (int i = 0; i < m; i++) {
        fin >> x >> y;
        g.add_edge(x-1, y-1);
    }
     
    g.GFS(fout);
 
    fin.close();
    fout.close();
 
    return 0;
}
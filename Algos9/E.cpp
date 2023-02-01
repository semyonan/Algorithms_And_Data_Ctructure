#include <vector>
#include <stack>
#include <fstream>
#include <iostream>

class Graph {
    int num_vertices;
    std::vector<int> *adc_matrix;
    std::vector<int> *trans_adc_matrix;
    bool *color;
    std::vector<int> order, component;
    int *res;
    bool hamilt;
public:
    Graph(int vertices) {
        num_vertices = vertices;
        hamilt = false;
        adc_matrix = new std::vector<int>[vertices];
        color = new bool[vertices];
        for (int i = 0; i < vertices; i++) {
            color[i] = false;
        }
    }
    void add_edge(int v1, int v2) {
        if (v1 != v2) {
            adc_matrix[v1].push_back(v2);
        }
    }
    void GFS(std::ofstream &fout) {
        for(int i = 0; i < num_vertices; i++) {
            visit_1(i, 1);
            if (hamilt) {
                fout << "YES" << std::endl;
                return;
            }
        }
        fout << "NO" << std::endl;    
    }
    void visit_1(int v, int num) {
        if (num == num_vertices) {
            hamilt = true;
        }
        color[v] = true;
        for (int j = 0; j < adc_matrix[v].size(); j++) {
            if (color[adc_matrix[v][j]] == false) {
                visit_1(adc_matrix[v][j], num + 1);
            }
        }
    }
};
 
int main() {
    int n, m, x, y;
 
    std::ifstream fin("hamiltonian.in");
    std::ofstream fout("hamiltonian.out");
 
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
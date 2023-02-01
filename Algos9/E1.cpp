#include <vector>
#include <stack>
#include <fstream>
#include <iostream>
 
class Graph {
    int num_vertices;
    std::vector<std::vector<int>> adc_matrix;
    std::vector<int> visited;
    std::stack<int> topsort;
public:
    Graph(int vertices) {
        num_vertices = vertices;
        adc_matrix.resize(vertices);
        visited.resize(vertices, 0);
    }
    void add_edge(int v1, int v2) {
        adc_matrix[v1].push_back(v2);
    }
    void GFS(std::ofstream &fout) {
        for(int i = 0; i < num_vertices; i++) {
            if (visited[i] == 0) {
                if (visit(i)) {
                    fout << "NO" << std::endl;
                    return;
                }
            }
        }
        if (topsort.size() == num_vertices) {
            visit_sort(topsort.top());
            if (topsort.empty()) {
                fout << "YES" << std::endl;
                return;
            }
        }
        fout << "NO" << std::endl;
    }
    bool visit(int v) {
        visited[v] = 1;
        for (int j = 0; j < adc_matrix[v].size(); j++) {
            if (visited[adc_matrix[v][j]] == 0) {
                if (visit(adc_matrix[v][j])) {
                    return true;
                }
            }  else if (visited[adc_matrix[v][j]] == 1) {
                return true;
            }
        }
        visited[v] = 2;
        topsort.push(v);
        return false;
    }
    void visit_sort(int v) {
        topsort.pop();
        if (!topsort.empty()) {
            for (int j = 0; j < adc_matrix[v].size(); j++) {
                if (adc_matrix[v][j] == topsort.top()) {
                    visit_sort(adc_matrix[v][j]);
                    return;
                }
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
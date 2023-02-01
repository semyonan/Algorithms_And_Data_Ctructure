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
                    fout << "-1" << std::endl;
                    return;
                }
            }
        }
        print_sort(fout);
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
        topsort.push(v+1);
        return false;
    }
    void print_sort(std::ofstream &fout) {
        while (!topsort.empty()) {
            fout << topsort.top() << ' ';
            topsort.pop();
        }
    }
};
  
int main() {
    int n, m, x, y;
  
    std::ifstream fin("topsort.in");
    std::ofstream fout("topsort.out");
  
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
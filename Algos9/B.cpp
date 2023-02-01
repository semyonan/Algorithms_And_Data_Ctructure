#include <vector>
#include <stack>
#include <fstream>
#include <iostream>
#include <algorithm>

class Graph {
    int num_vertices;
    std::vector<std::vector<int>> adc_matrix;
    std::vector<int> visited;
    std::vector<int> parent;
    int cycle_st;
    int cycle_end;
public:
    Graph(int vertices) {
        num_vertices = vertices;
        adc_matrix.resize(vertices);
        visited.resize(vertices);
        parent.resize(vertices);
        visited.assign(vertices, 0);
        parent.assign(vertices, -1);
        cycle_st = -1;
        cycle_end = -1;
    }
    void add_edge(int v1, int v2) {
        adc_matrix[v1].push_back(v2);
    }
    void GFS(std::ofstream &fout) {
        for(int i = 0; i < num_vertices; i++) {
            if (visited[i] == 0) {
                if (visit(i)) {
                    print_cycle(fout);
                    break;
                }
            }
        }
        if (cycle_st == -1) {
            fout << "NO" << std::endl;
        }
    }
    bool visit(int v) {
        visited[v] = 1;
        for (int j = 0; j < adc_matrix[v].size(); j++) {
            if (visited[adc_matrix[v][j]] == 0) {
                parent[adc_matrix[v][j]] = v;
                if (visit(adc_matrix[v][j])) {
                    return true;
                }
            }  else if (visited[adc_matrix[v][j]] == 1) {
                cycle_st = adc_matrix[v][j];
                cycle_end = v;
                return true;
            }
        }
        visited[v] = 2;
        return false;
    }
    void print_cycle(std::ofstream &fout) {
        fout << "YES" << std::endl;
        std::vector<int> cycle;
        cycle.push_back(cycle_st);
        for (int v=cycle_end; v!=cycle_st; v = parent[v]) {
            cycle.push_back(v);
        }
        reverse(cycle.begin(), cycle.end());
        for (size_t i=0; i<cycle.size(); ++i) {
            fout << cycle[i]+1 << ' ';
        }
    }
};
 
int main() {
    int n, m, x, y;
 
    std::ifstream fin("cycle.in");
    std::ofstream fout("cycle.out");
 
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
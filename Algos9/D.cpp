#include <vector>
#include <stack>
#include <fstream>
#include <iostream>

class Graph {
    int num_vertices;
    int num;
    std::vector<std::vector<int>> adc_matrix;
    std::vector<std::vector<int>> trans_adc_matrix;
    std::vector<bool> color;
    std::vector<int> order, component, res;
public:
    Graph(int vertices) {
        num_vertices = vertices;
        num = 1;
        adc_matrix.resize(vertices);
        trans_adc_matrix.resize(vertices);
        color.resize(vertices, false);
        res.resize(vertices);
    }
    void add_edge(int v1, int v2) {
        adc_matrix[v1].push_back(v2);
        trans_adc_matrix[v2].push_back(v1);
    }
    void GFS(std::ofstream &fout) {
        for(int i = 0; i < num_vertices; i++) {
            if (color[i] == false) {
                visit_1(i);
            }
        }

        for (int i = 0; i < num_vertices; i++) {
            color[i] = false;
        }

        for (int i=0; i<num_vertices; i++) {
            int v=order[num_vertices-1-i];
            if (color[v] == false) {
                visit_2(v);
                for(auto I=component.begin(); I != component.end(); I++)
                    res[*I] = num;
                num++;
                component.clear();
            }
        }
        fout << num-1 << std::endl;
        for (int i=0; i<num_vertices; i++) {
            fout << res[i] << " ";
        }
        fout << std::endl;
    }
    void visit_1(int v) {
        color[v] = true;
        for (int j = 0; j < adc_matrix[v].size(); j++) {
            if (color[adc_matrix[v][j]] == false) {
                visit_1(adc_matrix[v][j]);
            }
        }
        order.push_back(v);
    }
    void visit_2(int v) {
        color[v] = true;
        component.push_back(v);
        for (int j = 0; j < trans_adc_matrix[v].size(); j++) {
            if (color[trans_adc_matrix[v][j]] == false) {
                visit_2(trans_adc_matrix[v][j]);
            }
        }
    }
};
 
int main() {
    int n, m, x, y;
 
    std::ifstream fin("cond.in");
    std::ofstream fout("cond.out");
 
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
#include <vector>
#include <stack>
#include <fstream>
#include <iostream>
  
class Graph {
    int num_vertices;
    std::vector<std::vector<int>> adc_matrix;
public:
    Graph(int vertices) {
        num_vertices = vertices;
        adc_matrix.resize(vertices);
    }
    void add_edge(int v1, int v2) {
        adc_matrix[v1].push_back(v2);
        adc_matrix[v2].push_back(v1);
    }
 
    void print_deg(std::ofstream &fout) {
        for(int i = 0; i < num_vertices; i++) {
            fout << adc_matrix[i].size() << " ";
        }
    }
};
   
int main() {
    int n, m, x, y;
   
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
   
    fin >> n >> m;
    Graph g(n);
   
    for (int i = 0; i < m; i++) {
        fin >> x >> y;
        g.add_edge(x-1, y-1);
    }
       
    g.print_deg(fout);
   
    fin.close();
    fout.close();
   
    return 0;
}
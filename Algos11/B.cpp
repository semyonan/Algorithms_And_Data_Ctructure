#include <vector>
#include <stack>
#include <fstream>
#include <iostream>
#include <utility>
#include <limits>
#include <algorithm>

bool comp(std::pair<std::pair<int,long long>, bool> p1, std::pair<std::pair<int,long long>, bool> p2) {
    if ((p1.first.second >= p2.first.second)) {
        return true;
    } else {
        return false;
    }
}

class Graph {
    int num_vertices;
    std::vector  <std::vector<int>> d;
public:
    Graph(int vertices) {
        num_vertices = vertices;
        d.resize(vertices); 
        for(int i = 0; i < vertices; i++) {
            d[i].resize(vertices, 10001);
        }
    }

    void add_edge(int v1, int v2, int weight) {
        d[v1][v2] = weight;
    }
    
    void floyd(std::ofstream &fout) {
        for(int i = 0; i < num_vertices; i++) {
            for(int u = 0; u < num_vertices; u++) {
                for(int v = 0; v < num_vertices; v++) { 
                    d[u][v] = std::min(d[u][v], d[u][i] + d[i][v]);
                }
            }
        }
        for (int i = 0; i < num_vertices; i++) {
            for(int j = 0; j < num_vertices; j++) {
                if(i == j) {
                    fout << 0 << " ";
                } else {
                    fout << d[i][j] << " ";
                }
            }
            fout << std::endl;
        }
    }
};
    
int main() {
    int n, m, x, y, w;
    std::ifstream fin("pathsg.in");
    std::ofstream fout("pathsg.out");
    
    fin >> n >> m ;
    Graph g(n);
    
    for (int i = 0; i < m; i++) {
        fin >> x >> y >> w;
        g.add_edge(x-1, y-1, w);
    }
        
    g.floyd(fout);
    
    fin.close();
    fout.close();
    
    return 0;
}
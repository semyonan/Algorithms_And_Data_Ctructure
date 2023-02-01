#include <vector>
#include <stack>
#include <fstream>
#include <iostream>
#include <utility>
#include <limits>
#include <algorithm>

const long long INF = 8e18;

class Graph {
    int num_vertices;
    std::vector  <long long> dist;
    std::vector  <long long> parents;
    std::vector <bool> used_1;
    std::vector <bool> used_2;
    std::vector <std::vector<std::pair<int, long long>>> e;
public:
    Graph(int vertices) {
        num_vertices = vertices;
        e.resize(vertices);
        parents.resize(vertices, -1);
        dist.resize(vertices, INF);
        used_1.resize(vertices, 0);
        used_2.resize(vertices, 0);
    }

    void add_edge(int v1, int v2, long long weight) {
        e[v1].push_back(std::pair<int, long long> (v2, weight));
    }
    
    void relax(int v1, int v2, long long weight, int &i) {
        if ((dist[v1] > dist[v2] + weight) && (dist[v2] < INF)){
            dist[v1] = std::max(-INF, dist[v2] + weight);
            if ((i == num_vertices - 1) && (used_1[v1])) {
                dfs_2(v1);
            }
        }
    }

    void dfs_1(int v) {
        used_1[v] = 1;
        for(int i = 0; i < e[v].size(); i++) {
            int to = e[v][i].first;
            if (!used_1[to]) dfs_1(to);
        }
    }

    void dfs_2(int v) {
        used_2[v] = 1;
        for(int i = 0; i < e[v].size(); i++) {
            int to = e[v][i].first;
            if (!used_2[to]) dfs_2(to);
        }
    }

    void bellman(std::ofstream &fout, int s) {
        dfs_1(s);
        dist[s] = 0;
        
        for (int i = 0; i < num_vertices; ++i) {
            for(int j = 0; j < num_vertices; ++j) {
                for(auto I = e[j].begin();I != e[j].end(); ++I) {
                    relax((*I).first, j, (*I).second, i);
                }
            }
        }

        for(int i = 0; i < num_vertices; i++) {
            if ((dist[i] <= -INF) || (used_2[i])) fout << "-\n";
            else if (!used_1[i]) fout << "*\n";
            else fout << dist[i] << "\n";
        }
    }
};
    
int main() {
    int n, m, s, x, y;
    long long w;
    std::ifstream fin("path.in");
    std::ofstream fout("path.out");
    
    fin >> n >> m >> s;
    Graph g(n);
    
    for (int i = 0; i < m; i++) {
        fin >> x >> y >> w;
        g.add_edge(x-1, y-1, w);
    }
        
    g.bellman(fout, s-1);
    
    fin.close();
    fout.close();
    
    return 0;
}
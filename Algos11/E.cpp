#include <fstream>
#include <iostream>
#include <utility>
#include <limits>
#include <vector>
#include <algorithm>
#include <math.H>

class Graph {
    int num_vertices;
    std::vector<int> dist;
    std::vector<int> parent;
    std::vector <std::vector<std::pair<int, int>>> e;
public:
    Graph(int vertices) {
        num_vertices = vertices;
        parent.resize(vertices, -1);
        dist.resize(vertices,1000000000);
        e.resize(vertices);
    }
 
    void add_edge(int v1, int v2, int weight) {
        if ((weight != 1000000000)) {
            e[v1].push_back(std::pair<int, int>(v2, weight));
        }
    }
     
    void relax(int v1, int v2, int weight, int &x) {
        if (dist[v1] > dist[v2] + weight) {
            dist[v1] = dist[v2] + weight;
            parent[v1] = v2;
            x = v1;
        }
    }
 
    void bellman(std::ofstream &fout) {
        int x;
        for (int i = 0; i < num_vertices; ++i) {
            x = -1;
            for(int j = 0; j < num_vertices; ++j) {
                for(auto I = e[j].begin();I != e[j].end(); ++I) {
                    relax((*I).first, j, (*I).second, x);
                }
            }
        }

        if (x == -1) {
            fout << "NO" << std::endl;
            return;
        }

        print_cycle(x, fout);
    }

    void print_cycle(int start, std::ofstream &fout) {
        int v = start;
		for (int i=0; i<num_vertices; ++i) {
			v = parent[v];
        }

		std::vector<int> path;

		for (int cur = v; ;cur = parent[cur]) {
			path.push_back(cur);
			if (cur == v && path.size() > 1)  break;
		}

		reverse(path.begin(), path.end());
 
		fout << "YES\n" << path.size() << std::endl;
		for (size_t i=0; i<path.size(); ++i)
			fout << path[i]+1 << ' ';
    }
};
     
int main() {
    int n, s, f;
    int w;
    std::ifstream fin("negcycle.in");
    std::ofstream fout("negcycle.out");
     
    fin >> n;
    Graph g(n);
     
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            fin >> w;
            g.add_edge(i, j, w);
        }   
    }
         
    g.bellman(fout);
     
    fin.close();
    fout.close();
     
    return 0;
}
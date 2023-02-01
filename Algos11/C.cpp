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
    std::vector <std::pair<std::pair<int,long long>, bool>> dist_heap;
    std::vector  <long long> dist;
    std::vector <std::vector<std::pair<int, long long>>> e;
public:
    Graph(int vertices) {
        num_vertices = vertices;
        e.resize(vertices);
        dist.resize(vertices, __LONG_LONG_MAX__);
        dist_heap.push_back(std::pair<std::pair<int,long long>, bool> (std::pair<int, long long> (0 , 0), false));
        for(int i = 1; i < vertices; i++) {
            dist_heap.push_back(std::pair<std::pair<int,long long>, bool> (std::pair<int, long long> (i , __LONG_LONG_MAX__), false));
        }
        make_heap(dist_heap.begin(), dist_heap.end(), comp);
    }

    void add_edge(int v1, int v2, long long weight) {
        if (v2 != 0) {
            e[v1].push_back(std::pair<int, long long> (v2, weight));
        }
        if (v1 != 0) {
            e[v2].push_back(std::pair<int, long long> (v1, weight));
        }
        
    }
    
    void relax(int v1, int v2, long long weight) {
        if ((dist[v1] > dist[v2] + weight) && (dist[v2] != __LONG_LONG_MAX__)){
            dist[v1] = dist[v2] + weight;
            dist_heap.push_back(std::pair<std::pair<int,long long>, bool> (std::pair<int, long long> (v1 , dist[v1]), false));
            push_heap(dist_heap.begin(), dist_heap.end(), comp);
        }
    }

    void bellman(std::ofstream &fout) {
        dist[0] = 0;
        
        while (!dist_heap.empty()) {
            
            int v = dist_heap.front().first.first;
            pop_heap(dist_heap.begin(), dist_heap.end(), comp);
            dist_heap.pop_back();
            for(int j = 0; j < e[v].size(); j++) {
                relax(e[v][j].first, v, e[v][j].second);
            }
            //dist_heap.pop_back();
        }

        for (int i = 0; i < num_vertices; i++) {
            if(dist[i] != __LONG_LONG_MAX__) {
                fout << dist[i] <<" ";
            }
            
        }
    }
};
    
int main() {
    int n, m, x, y;
    long long w;
    std::ifstream fin("pathbgep.in");
    std::ofstream fout("pathbgep.out");
    
    fin >> n >> m ;
    Graph g(n);
    
    for (int i = 0; i < m; i++) {
        fin >> x >> y >> w;
        g.add_edge(x-1, y-1, w);
    }
        
    g.bellman(fout);
    
    fin.close();
    fout.close();
    
    return 0;
}
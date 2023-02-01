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
    Graph(int vertices, int start) {
        num_vertices = vertices;
        e.resize(vertices);
        dist.resize(vertices, __LONG_LONG_MAX__);
        for(int i = 0; i < vertices; i++) {
            if (i == start) {
                dist_heap.push_back(std::pair<std::pair<int,long long>, bool> (std::pair<int, long long> (i , 0), false));
            } else {
                dist_heap.push_back(std::pair<std::pair<int,long long>, bool> (std::pair<int, long long> (i , __LONG_LONG_MAX__), false));
            }
        }
        make_heap(dist_heap.begin(), dist_heap.end(), comp);
        /*for(auto I = dist_heap.begin(); I != dist_heap.end(); ++I) {
            std::cout << (*I).first.first << std::endl;
        }*/
    }

    void add_edge(int v1, int v2, long long weight) {
        e[v1].push_back(std::pair<int, long long> (v2, weight));
    }
    
    void relax(int v1, int v2, long long weight, int i) {
        if ((dist[v1] > dist[v2] + weight) && (dist[v2] != __LONG_LONG_MAX__)){
            dist[v1] = dist[v2] + weight;
            dist_heap.push_back(std::pair<std::pair<int,long long>, bool> (std::pair<int, long long> (v1 , dist[v1]), false));
            push_heap(dist_heap.begin(), dist_heap.end(), comp);
        }
    }

    void bellman(std::ofstream &fout, int start, int end) {
        dist[start] = 0;
        
        
        for (int i = 0; i < num_vertices; i++) {
            
            int v = dist_heap.front().first.first;
            pop_heap(dist_heap.begin(), dist_heap.end(), comp);
            if (v == end) {
                break;
            }
            dist_heap.pop_back();
            for(int j = 0; j < e[v].size(); j++) {
                relax(e[v][j].first, v, e[v][j].second, j);
            }
            //dist_heap.pop_back();
        }

        if (dist[end] == __LONG_LONG_MAX__) {
            fout << -1 << std::endl;
        } else {
            fout << dist[end] << std::endl;
        }
    }
};
    
int main() {
    int n, s, f;
    long long w;
    std::ifstream fin("pathmgep.in");
    std::ofstream fout("pathmgep.out");
    
    fin >> n >> s >> f;
    Graph g(n, s-1);
    
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            fin >> w;
            if ((j != s-1) && (w != 0) && (w!= -1)) {
                g.add_edge(i, j, w);
            }
        }   
    }
        
    g.bellman(fout, s-1, f-1);
    
    fin.close();
    fout.close();
    
    return 0;
}
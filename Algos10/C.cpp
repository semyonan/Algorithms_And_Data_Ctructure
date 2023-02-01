#include <vector>
#include <stack>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <utility>

int get(const int &n, std::vector<int> &subtree) {
        if (subtree[n] == n) {
            return n;
        }
        return subtree[n] = get(subtree[n], subtree);  
    }
 
void merge(const int &a, const int &b, std::vector<int> &subtree, std::vector<int> &vertex_rank) {
    int ra = get(a, subtree), rb = get(b, subtree);
    if (vertex_rank[ra] < vertex_rank[rb]) {
        subtree[ra] = rb;
    } else if (vertex_rank[rb] < vertex_rank[ra]) {
        subtree[rb] = ra;
    } else {
        subtree[ra] = rb;
        vertex_rank[rb]++;
    }
}

class Graph {
    int num_vertices;
    std::vector <std::pair<int, std::pair<int, int>>> v;
public:
    Graph(int vertices, int edges) {
        num_vertices = vertices;
        v.resize(edges);
    }

    void push_edge (int a, int b, int weight) {
        static int ind = 0;
        v[ind].second.first = a-1;
        v[ind].second.second = b-1;
        v[ind].first = weight;
        ind++;
    }

    long long min_tree () {
        sort(v.begin(), v.end());
        std::vector<int> subtree(num_vertices);
        std::vector<int> vertex_rank(num_vertices, 1);
        for (int i = 0; i < num_vertices; i++) {
            subtree[i] = i;
        }
        long long spanning_tree_weight = 0;
        for (int i = 0; i < v.size(); ++i) {
            if (get(v[i].second.first, subtree) != get(v[i].second.second, subtree)) {
                spanning_tree_weight += v[i].first;
                merge(v[i].second.first, v[i].second.second, subtree, vertex_rank);
            }
        }
        return spanning_tree_weight;
    }

    
};
  
int main() {
    int n, m, w, x, y;
    std::ifstream fin("spantree3.in");
    std::ofstream fout("spantree3.out");
  
    fin >> n >> m;

    Graph g(n,m);
  
    for (int i = 0; i < m; i++) {
        fin >> x >> y >> w;
        g.push_edge(x, y, w);
    }

    fout << g.min_tree() << std::endl;
  
    fin.close();
    fout.close();

  
    return 0;
}
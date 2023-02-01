#include <vector>
#include <stack>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <utility>
#include <limits>
 
void visit(int v, std::vector<bool> &color, std::vector<std::vector<int>> adc_matrix) {
    color[v] = true;
    for (int j = 0; j < adc_matrix[v].size(); j++) {
        if (color[adc_matrix[v][j]] == false) {
            visit(adc_matrix[v][j],color, adc_matrix);
        }
    }
}
 
bool dfs(int root, std::vector <std::pair<long long, std::pair<int, int>>> e, int n) {
    std::vector<bool> color(n);
    color.assign(n ,0);
    std::vector<std::vector<int>> adc_matrix(n);
 
    for (int i = 0; i < e.size(); i++) {
        adc_matrix[e[i].second.first].push_back(e[i].second.second);
    }
    visit(root, color, adc_matrix);
 
    for (int i = 0; i < n; i ++) {
        if (color[i] == false) {
            return false;
        }
    }
    return true;
}
 
void visit_1(int v, std::vector<bool> &color, std::vector<int> &order, std::vector<std::vector<int>> adc_matrix) {
    color[v] = true;
    for (int j = 0; j < adc_matrix[v].size(); j++) {
        if (color[adc_matrix[v][j]] == false) {
            visit_1(adc_matrix[v][j],color ,order, adc_matrix);
        }
    }
    order.push_back(v);
}
 
void visit_2(int v, std::vector<bool> &color, std::vector<int> &component, std::vector<std::vector<int>> trans_adc_matrix) {
    color[v] = true;
    component.push_back(v);
    for (int j = 0; j < trans_adc_matrix[v].size(); j++) {
        if (color[trans_adc_matrix[v][j]] == false) {
            visit_2(trans_adc_matrix[v][j], color, component, trans_adc_matrix);
        }
    }
}
 
std::vector<int> condensation(std::vector <std::pair<long long, std::pair<int, int>>> e, int &n) {
    std::vector<bool> color(n, false);
    std::vector<std::vector<int>> adc_matrix(n);
    std::vector<std::vector<int>> trans_adc_matrix(n);
    std::vector<int> order, component, res(n);
 
    for (int i = 0; i < e.size(); i++) {
        adc_matrix[e[i].second.first].push_back(e[i].second.second);
        trans_adc_matrix[e[i].second.second].push_back(e[i].second.first);
    }
    for(int i = 0; i < n; i++) {
        if (color[i] == false) {
            visit_1(i, color, order, adc_matrix);
        }
    }
 
    color.assign(n, 0);
    int num = 0;
    for (int i=0; i<n; i++) {
        int v = order[n-1-i];
 
        if (color[v] == false) {
            visit_2(v, color,component, trans_adc_matrix);
            for(auto I=component.begin(); I != component.end(); ++I) {
                res[*I] = num;
            }
            num++;
            component.clear();
        }
    }
    n = num;
    return res;
}
 
class Graph {
    int num_vertices;
    int num_edges;
    std::vector <std::pair<long long , std::pair<int, int>>> e;
public:
    Graph(int vertices, int edges) {
        num_vertices = vertices;
        num_edges = edges;
        e.resize(edges);
    }
 
    std::vector <std::pair<long long , std::pair<int, int>>> get_edges() {
        return e;
    }
 
    void push_edge (int a, int b, long long weight) {
        static int ind = 0;
        e[ind].second.first = a-1;
        e[ind].second.second = b-1;
        e[ind].first = weight;
        ind++;
    }
 
    long long find_MST(int n, int root) {
        long long res = 0;
        std::vector<long long> min_edge(n);
        for (int i = 0; i < n; i++) {
            min_edge[i] = __LONG_LONG_MAX__;
        }
        for(int i = 0; i < e.size(); i++) {
            min_edge[e[i].second.second] = std::min(e[i].first, min_edge[e[i].second.second]);
        }
 
        for(int i = 0; i < n; i++) {
            if (i != root) {
                res += min_edge[i];
            }
        }
 
        std::vector <std::pair<long long, std::pair<int, int>>> e_1;
 
        for(int i = 0; i < e.size(); i++) {
            if (e[i].first == min_edge[e[i].second.second]) {
                e_1.push_back(e[i]);
                e_1[e_1.size()-1].first = 0;
            }
        }
         
        if (dfs(root, e_1, n)) {
            return res;
        }
 
        std::vector<int> components = condensation(e_1, n);
 
        std::vector <std::pair<long long, std::pair<int, int>>> e_2;
 
        for(int i = 0; i < e.size(); i++) {
            if (components[e[i].second.first] != components[e[i].second.second]) {
                e_2.push_back(e[i]);
                e_2[e_2.size()-1].second.first = components[e[i].second.first];
                e_2[e_2.size()-1].second.second = components[e[i].second.second];
                e_2[e_2.size()-1].first -= min_edge[e[i].second.second];
            }
        }
        e = e_2;
        res += find_MST(n, components[root]);
        return res;
    }
};
   
int main() {
    int n, m, x, y;
    long long  w;
    std::ifstream fin("chinese.in");
    std::ofstream fout("chinese.out");
   
    fin >> n >> m;
 
    Graph g(n,m);
   
    for (int i = 0; i < m; i++) {
        fin >> x >> y >> w;
        g.push_edge(x, y, w);
    }
     
    if (dfs(0, g.get_edges(), n)) {
        fout << "YES" << "\n" << g.find_MST(n, 0) << std::endl;
    } else {
        fout << "NO" << std::endl;
    }
     
    fin.close();
    fout.close();
 
    return 0;
}
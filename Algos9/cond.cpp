#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>


std::vector<int> order;
std::vector<int> component;
std::vector<int> visited;
std::vector<int> trans_visited;
int counter = 1;

class Graph
{
private:
    std::vector<std::vector<int> > adj;
    std::vector<std::vector<int> > trans_adj;

public:
    Graph(int n) {
        adj.resize(n);
        trans_adj.resize(n);
    }

    void add_edge(int v, int w) {
        adj[v].push_back(w);
        trans_adj[w].push_back(v);
    }

    void DFS1(int v) {
        visited[v] = true;

        for (int i=0; i<adj[v].size(); i++) {
            if (!visited[adj[v][i]])
                DFS1(adj[v][i]);
        }
        order.push_back(v);
    }

    void DFS2(int v) {
        trans_visited[v] = true;
        component[v] = counter;

        for (int i = 0; i < trans_adj[v].size(); i++) {
            if (!trans_visited[trans_adj[v][i]]) {
                DFS2(trans_adj[v][i]);
            }
        }
    }

};





int main(int argc, char **argv)
{
    std::ifstream fin("cond.in");
    std::ofstream fout("cond.out");

    int n, m, x, y;
    fin >> n >> m;
    Graph graph(n);

    for (int i=0; i<m; i++) {
        fin >> x >> y;
        graph.add_edge(x-1, y-1);
    }
    for (int i = 0; i < n; ++i)
        visited.push_back(false);
    for (int i = 0; i < n; ++i)
        trans_visited.push_back(false);
    
    for (int i=0; i<n; i++) {
        if (!visited[i])
            graph.DFS1(i);
    }

    component.resize(n);
    reverse(order.begin(), order.end());

    for (int i=0; i<n; i++) {
        int v = order[i];
        if (!trans_visited[v]) {
            graph.DFS2(v);
            counter++;
        }
    }

    fout << counter-1 << "\n";
    for (int i=0; i<component.size(); i++) 
        fout << component[i] << " ";
    fout << std::endl;

    fin.close();
    fout.close();
    return 0;
}

#include <iostream>
#include <limits.h>
#include <queue>
#include <fstream>

class Graph{
    private:
        int num_vertices, s_, t_;
        std::vector<std::vector<int>> adj_matrix;
        std::vector<bool> visited;
        std::vector<int> parent;
    public:
        Graph(int vertices, int s, int t) {
            num_vertices = vertices;
            s_ = s;
            t_ = t;
            adj_matrix.resize(vertices, std::vector<int>(vertices, 0));
            visited.resize(vertices, false);
            parent.resize(vertices, -1);
        }

        void add_edge(int v1, int v2, int w) {
            adj_matrix[v1][v2] = w;
        }

        bool bfs() {
            visited.assign(num_vertices, false);
            std::queue<int> q;
            q.push(s_);
            visited[s_] = true;
            parent[s_] = -1;

            while (!q.empty()) {
                int v = q.front();
                q.pop();

                for (int i = 0; i < num_vertices; i++) {
                    if ((visited[i] == false) && (adj_matrix[v][i] > 0)) {
                        if (i == t_) {
                            parent[i] = v;
                            return true;
                        }
                        q.push(i);
                        parent[i] = v;
                        visited[i] = true;
                    }
                }
            }

            return false;
        }

        int fulkerson() {
            int u, v;

            int max_flow = 0;

            while (bfs()) {
                int path_flow = INT_MAX;
                for (v = t_; v != s_; v = parent[v]) {
                    u = parent[v];
                    path_flow = std::min(path_flow, adj_matrix[u][v]);
                }

                for (v = t_; v != s_; v = parent[v]) {
                    u = parent[v];
                    adj_matrix[u][v] -= path_flow;
                    adj_matrix[v][u] += path_flow;
                }

                max_flow += path_flow;
            }

            return max_flow;
        }
};

int main() {
    int n, m, x, y, w;

    std::ifstream fin("maxflow.in");
    std::ofstream fout("maxflow.out");
    
    fin >> n >> m;

    Graph g(n , 0, n-1);

    for (int i = 0; i < m; i++) {
        fin >> x >> y >> w;
        g.add_edge(x-1, y-1, w);
    }

	fout << g.fulkerson() << std::endl;

	return 0;
}


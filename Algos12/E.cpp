#include <iostream>
#include <vector>
 
class Tree {
    private:
        int num_vertices;
        int root;
        std::vector<std::vector<int>> adj_matrix;
        std::vector<std::vector<int>> answer;
    public:
        Tree(int vertices) {
            num_vertices = vertices;
            root = 0;
            adj_matrix.resize(vertices);
            answer.resize(vertices, std::vector<int>(2, 0));
        }
 
        void add_edge(int p, int v) {
            if (p != 0) {
                adj_matrix[p-1].push_back(v);
            } else {
                root = v;
            }
        }
 
        void solution() {
            search(root);
            std::cout << std::max(answer[root][0], answer[root][1]);
        }
 
        void search(int v) {
            answer[v][0] = 0;
            answer[v][1] = 1;
 
            for (int i = 0; i < adj_matrix[v].size(); i++) {
                search(adj_matrix[v][i]);
            }
 
            for (int i = 0; i < adj_matrix[v].size(); i++) {
                answer[v][0] += std::max(answer[adj_matrix[v][i]][0], answer[adj_matrix[v][i]][1]);
                answer[v][1] += answer[adj_matrix[v][i]][0];
            }
        }
};
 
int main() {
    int n, pred;
    std::cin >> n;
    Tree tree(n);
 
    for (int i = 0; i < n; ++i) {
        std::cin >> pred;
        tree.add_edge(pred, i);
    }
     
    tree.solution();
 
    return 0;
}
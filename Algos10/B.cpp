#include <vector>
#include <stack>
#include <fstream>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <utility>
#include <limits>
#include <iomanip>
 
class point {
    private:
        int x_, y_;
    public:
        point(int x, int y): x_(x), y_(y) {}
 
        point() 
            : x_(0),
              y_(0) {}
 
        point(const point &p) 
            : x_(p.x_),
              y_(p.y_) {}
         
        int getX() const{
            return this->x_;
        }
 
        int getY() const{
            return this->y_;
        }
};
 
double distance(const point &A, const point &B) {
    return sqrt((B.getX() - A.getX())*(B.getX() - A.getX()) + (B.getY() - A.getY())*(B.getY() - A.getY()));
}
 
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
    std::vector <std::pair<double, std::pair<int, int>>> v;
public:
    Graph(int vertices) {
        num_vertices = vertices;
        v.resize(vertices*(vertices-1)/2);
    }
 
    void get_weights (std::vector<point> p) {
        int ind = 0;
        for (int i = 0; i < num_vertices; i++) {
            for(int j = i + 1; j < num_vertices; j++ ) {
                v[ind].second.first = i;
                v[ind].second.second = j;
                v[ind].first = distance(p[i], p[j]);
                ind++;
            }
        }
        sort(v.begin(), v.end());
    }
 
    double min_tree () {
        std::vector<int> subtree(num_vertices);
        std::vector<int> vertex_rank(num_vertices, 1);
        for (int i = 0; i < num_vertices; i++) {
            subtree[i] = i;
        }
        double spanning_tree_weight = 0;
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
    int n, x, y;
    std::ifstream fin("spantree.in");
    std::ofstream fout("spantree.out");
   
    fin >> n;
    std::vector<point> p;
 
    Graph g(n);
   
    for (int i = 0; i < n; i++) {
        fin >> x >> y;
        p.push_back(point(x,y));
    }
       
    g.get_weights(p);
 
    fout << std::setprecision(10) <<g.min_tree() << std::endl;
   
    fin.close();
    fout.close();
 
   
    return 0;
}
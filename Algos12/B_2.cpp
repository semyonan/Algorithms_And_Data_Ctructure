#include <fstream>
#include <vector>
#include <iostream>

class Graph {
    int vert_1;
    int vert_2;
    std::vector <std::vector<int>> e;
    std::vector<int> mt;
    std::vector<bool> used;
public:
    Graph(int num_v1, int num_v2, int num_egdes) {
        vert_1 = num_v1;
        vert_2 = num_v2;
        e.resize(num_v1);
        mt.assign (num_v2, -1);
        used.resize(num_v1);
    }
 
    void add_edge(int v1, int v2) {
        e[v1].push_back(v2); 
    }

    void parasoch(std::ofstream& fout) {
        int count = 0;
        for(int v = 0; v < vert_1; v++) {
            used.assign(vert_1, false);
            if (kuhn(v)) {
                count++;
            }
        }
        
        fout << count;
    }
     
    bool kuhn(int v) {
        if (used[v]) {
            return false;
        }
        used[v] = true;
        for (int i = 0; i < e[v].size(); i++) {
            int to = e[v][i];
            if ((mt[to] == -1) || (kuhn (mt[to]))) {
                mt[to] = v;
                return true;
            }
        }
        return false;
    }
};
 
int main() {
	int n, m, k, x, y;
    std::ifstream fin("matching.in");
    std::ofstream fout("matching.out");
     
    fin >> n >> m >> k;
    Graph g(n, m, k);
     
    for (int i = 0; i < k; i++) {
        fin >> x >> y;
        g.add_edge(x-1, y-1);
    }
         
    g.parasoch(fout);
     
    fin.close();
    fout.close();
     
    return 0;
}
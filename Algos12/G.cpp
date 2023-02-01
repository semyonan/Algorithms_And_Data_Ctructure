#include <fstream>
#include <vector>

std::vector<std::vector<int>> ks;
std::vector<int> weights;
std::vector<int> values;
static int m, n, answer;

void knapsack_solution() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                ks[i][j] = 0;
            } else {  
                if (weights[i - 1] > j) {
                    ks[i][j] = ks[i - 1][j];
                } else {
                    ks[i][j] = std::max(ks[i - 1][j], values[i - 1] + ks[i - 1][j - weights[i - 1]]);
                }
            }
        }
    }
};
void find_answer(int i, int j) {
    if (ks[i][j] == 0) {
        return;
    }
    if (ks[i - 1][j] == ks[i][j]) {
        find_answer(i - 1, j);
    } else {
        find_answer(i - 1, j - weights[i]);
        answer += weights[i-1];
    }
};

int main() {
    std::ifstream fin("knapsack.in");
    std::ofstream fout("knapsack.out");

    fin >> m >> n;
    answer = 0;
    weights.resize(n);
    values.resize(n,1);

    for (int i = 0; i < n; i++) {
        fin >> weights[i];
    }

    ks.resize(n+1, std::vector<int>(m+1));
    knapsack_solution();
    find_answer(n, m);
    fout << answer;

    fin.close();
    fout.close();

    return 0; 
}

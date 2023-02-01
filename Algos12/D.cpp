#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::vector<long long>> desk;
static int n, m;

int solution(int i, int j) {
    if (((i >= 0) && (i < n)) && ((j >= 0) && (j < m))) {
        if (desk[i][j] == 0) {
            desk[i][j] = solution(i - 2, j - 1) + solution(i - 2, j + 1) + solution(i - 1, j - 2) + solution(i + 1, j - 2);
        }
    } else {
        return 0;
    } 
    return desk[i][j];
}


int main() {
    std::ifstream fin("knight2.in");
    std::ofstream fout("knight2.out");

    fin >> n >> m;

    desk.resize(n, std::vector<long long>(m, 0));
    desk[0][0] = 1;

    fout << solution(n-1,m-1) << std::endl;

    return 0;
}
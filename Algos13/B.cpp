#include <fstream>
#include <iostream>
#include <vector>
#include <string>

std::vector<int> prefix_function(const std::string& str) {
    std::vector<int> p(str.length(), 0);

    for (int i = 1; i < str.length(); i++) {
        int j = p[i - 1];

        while ((j > 0) && (str[i] != str[j])) {
            j = p[j - 1];
        }

        if (str[i] == str[j]) {
            p[i] = j + 1;
        } else {
            p[i] = j;
        }
    }

    return p;
}

int main() {
    std::ifstream fin("prefix.in");
    std::ofstream fout("prefix.out");
    std::string str;
    fin >> str;
    std::vector<int> p = prefix_function(str);

    for (int i = 0; i < str.length(); i++) {
       fout << p[i] << ' ';
    }

    fin.close();
    fout.close();

    return 0;
}
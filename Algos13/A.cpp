#include <fstream>
#include <iostream>
#include <vector>
#include <string>

void find_substr(std::string &substring, std::string &string, std::ofstream &fout) {
    int count = 0;
    std::vector<int> result;

    if (substring.size() > string.size()) {
        fout << 0;
        return;
    }
    
    for(int i = 0; i < string.size() - substring.size() + 1; i++) {
        bool flag = true;
        for (int j = 0; j < substring.size(); j++) {
            if (string[i+j] != substring[j]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            result.push_back(i+1);
            count++;
        }
    }
    fout << count << std::endl;
    for(int i = 0; i < count; i++) {
        fout << result[i] << ' ';
    }
}

int main() {
    std::ifstream fin("search1.in");
    std::ofstream fout("search1.out");

    std::string substr;
    std::string str;

    fin >> substr >> str;
    find_substr(substr, str, fout);

    fin.close();
    fout.close();

    return 0;
}
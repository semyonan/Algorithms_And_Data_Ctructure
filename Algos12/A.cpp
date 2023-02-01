#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
 
const int64_t INF = 6e18;
 
void find_LIS(std::vector<int64_t> a) {
    int n = a.size();
    std::vector<int64_t> d(n+1, INF);
    std::vector<int64_t> pos(n+1, 0);
    std::vector<int64_t> prev(n, 0);
    
 
    pos[0] = -1;
    d[0] = -INF;
    int length = 0;
 
    for (int i = 0; i < n; i++) {
        int j = int (upper_bound (d.begin(), d.end(), a[i]) - d.begin());
        if ((d[j - 1] < a[i]) && (a[i] < d[j])) {
           d[j] = a[i];
           prev[i] = pos[j - 1];
           pos[j] = i;
           length = std::max(length, j);
        }
    }
 
    std::vector<int64_t> answer;
    int64_t p = pos[length];
    while (p != -1) {
       answer.push_back(a[p]);
       p = prev[p];
    }
    std::reverse(answer.begin(), answer.end());
    std::cout << length << std::endl;
    for (int i = 0; i < length; i++) {
        std::cout << answer[i] << ' ';
 
    }
    std::cout << std::endl;
}
 
int main() {
    int n;
 
    std::cin >> n;
    std::vector<int64_t> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    find_LIS(a);
 
    return 0;
}
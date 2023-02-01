#include <fstream>
 
using namespace std;
 
int main ()
{
  int a, b;
  ifstream fin("sum.in");
  ofstream fout("sum.out");
  fin >> a >> b;
  fout << a + b << endl;
  fin.close();
  fout.close();
  return 0;
}
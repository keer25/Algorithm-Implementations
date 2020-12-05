#include <iostream>
#include <vector>
using namespace std;

long combcalc(int n) {
  if (n < 3) return 0;
  double a = n -1;
  double b = n;
  double c = n -2;
  return (a*b*c)/6;
}

int main() {
	//code
    int nt;
    cin>>nt;
    vector<int> ans(nt);
    for (int i=0; i<nt; i++) {
      long count = 0;
      int n;
      cin>>n; // Number of rows
      vector<int> colc(n);
      vector<int> ld(2*n - 1);
      vector<int> rd(2*n - 1);
      for (int j=0; j<n; j++) {
        int rowc = 0;
        char c;
        for (int k=0; k<n; k++)  {
          cin>>c;
          if(c != '.') {
            rowc++;
            colc[k]++;
            ld[k + j]++;
            rd[k - j + (n - 1)]++;
          }
        }
        count += combcalc(rowc);
      }
      for (int p=0; p<n; p++) {
        count += combcalc(colc[p]);
      }
      for (int p=0; p< (2*n -1); p++) {
        count += combcalc(ld[p]);
        count += combcalc(rd[p]);
      }
      ans[i] = count;
    }

    for (int i=0; i<nt; i++) {
      cout<<ans[i]<<'\n';
    }
	return 0;
}

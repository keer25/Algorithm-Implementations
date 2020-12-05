#include <iostream>
# include<vector>
using namespace std;

long dist(long i, long j, long n) {
    if (i <= j) {
        return (j - i);
    } else {
        return (n - 1 - i) + j;
    }
}

int main() {
    long nt;
    cin>>nt;
    vector<int> ans(nt);
    for (long i=0; i<nt; i++) {
        long n;
        long mini = -1;
        long minind = -1;
        cin>>n;
        for (int j=0; j<n; j++) {
            long c;
            cin>>c;
            long temp = c + dist(c%n, j, n);
            if (mini == -1) {mini =temp; minind = j + 1;}
            else if (temp < mini) {mini = temp; minind = j+1;}
        }
        ans[i] = minind;
    }

    for (long i=0; i<nt; i++) {
      cout<<'\n'<<ans[i];
    }
    cout<<'\n';
	return 0;
}

# include <iostream>
# include <cmath>
# include <vector>
using namespace std;

void constructrec(vector<int>& segtree, vector<int>& arr, int s, int e, int ind) {
  if ( s > e ) return;
  if (s == e) {
    segtree[ind] = arr[s];
    return;
  }
  int m = (s + e)/2;
  constructrec(segtree, arr, s, m, 2*ind + 1);
  constructrec(segtree, arr, m+1, e, 2*ind + 2);
  segtree[ind] = segtree[2*ind + 1] + segtree[2*ind + 2];
}

int sumToRec(int l, int r, vector<int>& segtree, int s, int e, int ind) {
  if (s >= l && e <= r) return segtree[ind];
  if ( l > e || r < s ) return 0;
  int m = (s + e)/2;
  return sumToRec(l, r, segtree, s, m, 2*ind + 1) + sumToRec(l, r, segtree, m + 1, e, 2*ind +2);
}

struct SegTree {
  vector<int> arr;
  int n;

  SegTree(vector<int>& a) {
    n = a.size();
    arr.resize(2*ceil(log2(n)));
    constructrec(arr, a, 0, n-1, 0);
  }

  void updatevalue(int ind, int delta) {
    int s = 0; int e = n-1; int m = (s + e)/2;
    int segind = 0;
    arr[segind] += delta;
    while (s < e) {
      m = (s + e)/2;
      if (ind <= m) {
        segind = 2*segind + 1;
        e = m;
      } else {
        segind = 2*segind + 2;
        s = m + 1;
      }
      arr[segind] += delta;
   }
  }

  int sumTo(int ind) {
    return sumToRec(0, ind, arr, 0, n-1, 0);
  }
};


void print_vec(vector<int>& arr) {
  for (int i=0; i<arr.size(); i++) {
    cout<<arr[i]<<' ';
  }
  cout<<'\n';
}

int main() {
  int n = 5;
//  vector<int> segtree(2*ceil(log2(n))); // Size of the seg tree
  vector<int> arr;
  arr.push_back(1);
  arr.push_back(1);
  arr.push_back(1);
  arr.push_back(1);
  arr.push_back(1);

  SegTree segtree = *(new SegTree(arr));

  //constructrec(0, n-1, 0, segtree, arr);
  print_vec(segtree.arr);
  cout<<segtree.sumTo(4)<<'\n';
  segtree.updatevalue(19, 2);
  cout<<segtree.sumTo(3)<<'\n';
  return 0;
}

# include <iostream>
# include <vector>
using namespace std;
//Using a one indexed tree for simplicity

// We also need the initial array to fid delta but we can also update hte interface to just accept delta
void updateTree(vector<int>& fenwick, vector<int>& arr, int ind, int val) {
  int delta = val - arr[ind];
  arr[ind] = val;
  ind += 1;
  while(ind < fenwick.size()) {
    fenwick[ind] += delta;
    ind += (ind)&(-1*ind);
  }
}

int sumTo(vector<int>& fenwick, int ind) {
  ind += 1;
  int ans = 0;
  while (ind > 0) {
    ans += fenwick[ind];
    ind -= (ind)&(-1*ind);
  }
  return ans;
}

// fenwick size = arr size + 1
void costructFenwick(vector<int>& fenwick, vector<int>& arr) {
  vector<int> temp(arr.size()); // Initializing a zero array to be considered as init
  for (int i=0; i<arr.size(); i++) {
    updateTree(fenwick, temp, i, arr[i]);
  }
}

int main() {
  vector<int> arr;
  arr.push_back(1);
  arr.push_back(1);
  arr.push_back(1);
  arr.push_back(1);
  arr.push_back(1);
  arr.push_back(1);
  vector<int> fenwick(7);
  costructFenwick(fenwick, arr);
  cout<<sumTo(fenwick, 4)<<'\n';
  updateTree(fenwick, arr, 2, 20);
  cout<<sumTo(fenwick, 5)<<'\n';
  return 0;
}

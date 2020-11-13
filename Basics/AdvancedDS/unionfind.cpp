# include <iostream>
# include <vector>
using namespace std;

// Union find structure for values 0.....1
struct DS{
  vector<int> parent;
  // height is just a upper bound as we dont modify the height on path compression
  vector<int> height;

  DS(int n) {
    for (int i=0; i<n; i++) {
      parent.push_back(i);
      height.push_back(1);
    }
  }

  int find(int x) {
    int node = x;
    while (node != parent[x]) {
      node = parent[node];
    }
    int root = node;
    node = x;
    // Relink node to parents
    while (node != parent[x]) {
      int temp = parent[node];
      parent[node] = root;
      node = temp;
    }
    return root;
  }

  int merge(int x, int y) {
    int s1 = find(x);
    int s2 = find(y);
    if (s1 == s2) return s1;
    if (height[s2] > height[s1]) {
      int temp = s2;
      s2 = s1;
      s1 = temp;
    }

    // increase height based on the two trees, if both heights are equal it incerases by 1
    int newheight = max(height[s1], height[s2] + 1);
    parent[s2] = s1;
    height[s1] = newheight;
    return s1;
  }

  void print() {
    for (int i=0; i<parent.size(); i++) {
      cout<<parent[i]<<' ';
    }
    cout<<'\n';
  }
};

int main() {
  int n = 5;
  DS ds = *(new DS(n));
  ds.print();
  cout<<ds.find(1)<<'\n';
  ds.print();
  cout<<ds.merge(1, 2)<<'\n';
  cout<<ds.merge(3, 4)<<'\n';
  cout<<ds.merge(1, 3)<<'\n';
  ds.print();
  cout<<ds.find(4)<<'\n';

  return 0;
}

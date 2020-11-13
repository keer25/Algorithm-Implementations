# include <iostream>
# include <vector>
using namespace std;
// The Below example is a max har with parent >= decscendants
struct Node {
  int val;
  Node* left;
  Node* right;

  Node(int val) {
    this->val = val;
  }
};
void print_heap(vector<int>& arr) {
  for (int i=1; i<arr.size(); i++) {
    cout<<arr[i]<<' ';
  }
  cout<<'\n';
}
// Heapifies a subtree at index i, when the value at i decreases (its subtrees follow heap structure)
void heapify(vector<int>& arr, int i, int n) {
  if (i > n) return;
  int left = 2*i;
  int right = 2*i + 1;
  int maxi = arr[i];  // New value of the i
  int nextind = i; // Next index to be processed
  if (left > n) return;
  if (arr[left] > maxi) {
    maxi = arr[left];
    nextind = left;
  }
  if (right <= n) {
    if (arr[right] > maxi) {
      maxi = arr[right];
      nextind = right;
    }
  }
  arr[nextind] = arr[i];
  arr[i] = maxi; // Swap parent node with child node
  if (nextind == i) return;
  else {
    heapify(arr, nextind, n); // Heapify that node as that is decreased
  }
}

void build_heap(vector<int>& arr, int lastind) {
  int n = lastind; // Important Step! arr has n + 1 elements, but only the last n are the heap elements
  for (int i=n/2; i >= 1; i--) { // only n/2 has atlseat one child in the heap
    heapify(arr, i, n);
  }
}

void build_heap(vector<int>& arr) { // it will be an 1 indexed vecor of N+1 elements and has O(n) complecit!
  build_heap(arr, arr.size() - 1);
}

Node* build_heap_tree_rec(vector<int>& arr, int i, int n) {
  if (i > n) return NULL;
  Node* root = new Node(arr[i]);
  root->left = build_heap_tree_rec(arr, 2*i, n);
  root->right = build_heap_tree_rec(arr, 2*i + 1, n);
  return root;
}
Node* build_heap_tree(vector<int>& arr, int n) {
  if (n < 1) return NULL;
  build_heap(arr, n);
  return build_heap_tree_rec(arr, 1, n);
}

void heap_sort(vector<int>& arr) {
  for (int i=arr.size() -1; i>= 2; i--) {
    build_heap(arr, i);
    int temp = arr[1];
    arr[1] = arr[i];
    arr[i] = temp;
  }
}

//Bubbles up an element in heap where the value is increased at an index to the appropriate position
void bubbleup(vector<int>& arr, int i) {
  while (arr[i/2] < arr[i] && i!=1) {
    int temp = arr[i];
    arr[i] = arr[i/2];
    arr[i/2] = temp;
    bubbleup(arr, i/2);
  }
}

void push(vector<int>& arr, int elem) {
  if (arr.size() == 0) arr.push_back(-1);
  arr.push_back(elem);
  bubbleup(arr, arr.size() -1);
}

void pop(vector<int>& arr) {
  if (arr.size() < 2) return;
  int elem = arr.back();
  arr.pop_back();
  arr[1] = elem;
  heapify(arr, 1, arr.size() - 1);
}
void preorder(Node* root) {
  if (root == NULL) return;
  cout<<root->val<<' ';
  preorder(root->left);
  preorder(root->right);
}

int main() {
  vector<int> vec; vec.push_back(-1);
  int size = 7;
  int arr[] = {1, 11, 3, 4, 12, 6, 7};
  for (int i=0; i<size; i++) {
    vec.push_back(arr[i]);
  }
  build_heap(vec);
  print_heap(vec);
  //heap_sort(vec);
  //print_heap(vec);
  Node* root = build_heap_tree(vec, vec.size() - 1);
  preorder(root);cout<<'\n';
  push(vec, 69);
  print_heap(vec);
  pop(vec);
  print_heap(vec);
  return 0;
}

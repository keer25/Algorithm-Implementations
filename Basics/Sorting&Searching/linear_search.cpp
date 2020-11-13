# include <iostream>
# include <vector>
using namespace std;

// Given an array and the element to find returns the index or - 1 if the element is not found in O(n)
int linear_search(vector<int> arr, int elem) {
  int i;
  for (i=0; i<arr.size(); i++) {
    if (arr[i] == elem) {
      break;
    }
  }
  if (i < arr.size()) return i;
  else return -1;
}

int main() {
  int size = 9;
  int arr[] = {235, 4363, 636, 35637, 6 ,7 , 2, 4, 10};
  int elem = 90;
  vector<int> inp;
  for (int i=0; i<size; i++) {
    inp.push_back(arr[i]);
  }
  cout<<linear_search(inp, elem);
  return 0;
}

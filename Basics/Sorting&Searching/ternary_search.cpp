# include <iostream>
# include <vector>
using namespace std;

// Algorithm for search by splitting into three parts, at every time 1/3 of the array is processed in the next step
int ternary_search(vector<int> arr, int elem) {
  int low = 0;
  int high = arr.size() - 1;
  int mid1;
  int mid2;
  while (low <= high) {
    mid1 = low + (high - low)/3;
    mid2 = high - (high - low)/3;
    if (elem < arr[mid1] ) {
      high = mid1 - 1;
    } else if (elem > arr[mid2]) {
      low = mid2 + 1;
    } else if (elem == arr[mid1]) return mid1;
      else if (elem == arr[mid2]) return mid2;
      else {
        high = mid1 + 1;
        low = mid2 - 1;
      }
  }
  return -1;
}

int main() {
  int size = 9;
  int arr[] = {2, 5, 10, 45, 56 ,57 , 57, 58, 75};
  int elem = 75;
  vector<int> inp;
  for (int i=0; i<size; i++) {
    inp.push_back(arr[i]);
  }
  cout<<ternary_search(inp, elem);
  return 0;
}

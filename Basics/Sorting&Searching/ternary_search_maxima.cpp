# include <iostream>
# include <vector>
using namespace std;

// Algorithm for search by splitting into three parts, at every time 1/3 of the array is processed in the next step
int ternary_search(vector<int> arr) {
  int low = 0;
  int high = arr.size() - 1;
  int mid1;
  int mid2;
  while (low<=high) {
    mid1 = low + (high - low)/3;
    mid2 = high - (high - low)/3; // This allocation makes sure that low < high does not happend before low == high, which happend with bsearch
    if (mid1 == mid2) return mid1; //  This definitely means low == high
    if (arr[mid1] < arr[mid2]) {
      low = mid1 + 1;
    } else {
      high = mid2 - 1;
    }
  }
  return -1;
}

int binary_search(vector<int> arr) {
  int low = 0;
  int high = arr.size() - 1;
  int mid;
  while (low <= high) {
    mid = (low + high)/2;
    if (mid == arr.size() - 1) {
      if (arr[mid - 1] < arr[mid]) return mid;
      else high = mid - 1;
    } else if (arr[mid + 1] > arr[mid]) {
      low = mid + 1;
    } else {
      if (mid == 0) return 0;
      if (arr[mid - 1] < arr[mid]) {
        return mid;
      }
      high = mid - 1;
    }
  }
  return arr.size() - 1;
}

int main() {
  int size = 5;
  int arr[] = {1, 2, 3, 4, 89};
  vector<int> inp;
  for (int i=0; i<size; i++) {
    inp.push_back(arr[i]);
  }
  cout<<ternary_search(inp);
  cout<<binary_search(inp);
  return 0;
}

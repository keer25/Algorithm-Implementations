# include <iostream>
# include <vector>
using namespace std;

// Returns the index of the elem just greater or equal to the elem to find out where to insert the elem. Algorithm is O(logn)
int binary_search(vector<int> arr, int elem) {
   int low = 0;
   int high = arr.size() - 1;
   int mid;
   while ( low <= high) {
      mid  = (low + high)/2;
      if (elem < arr[mid]) {
        if (mid == 0) return 0;
        else {
          if (arr[mid - 1] < elem) return mid;
        }
        high = mid - 1;
      } else if (elem > arr[mid]) {
        low = mid + 1;
      } else {
        return mid;
      }
   }
   return arr.size();
}

int main() {
  int size = 9;
  int arr[] = {2, 5, 10, 45, 56 ,57 , 57, 58, 75};
  int elem = 769;
  vector<int> inp;
  for (int i=0; i<size; i++) {
    inp.push_back(arr[i]);
  }
  cout<<binary_search(inp, elem);
  return 0;
}

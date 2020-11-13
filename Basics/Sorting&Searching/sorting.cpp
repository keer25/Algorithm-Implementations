# include <iostream>
# include <vector>
# include <random>
# include <queue>
using namespace std;

void printarr(vector<int> arr) {
  for (int i=0; i<arr.size(); i++) {
    cout<<arr[i]<<' ';
  }
  cout<<'\n';
}

// Always has n*(n-1)/2 comparisons
vector<int> bubble_sort(vector<int> arr) {
  for (int i=0; i<arr.size(); i++) {
    for (int j=0; j<arr.size() - (i + 1); j++) {
      if (arr[j] > arr[j+1]) {
        int temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;
      }
    }
  }
  return arr;
}

// If it is a partially sorted array this minimises the comparisons
vector<int> insertion_sort(vector<int> arr) {
  for (int i=1; i<arr.size(); i++) {
    int elem = arr[i];
    int j = i - 1;
    while (arr[j] > elem && j >= 0) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j+1] = elem;
  }
  return arr;
}

//n*(n-1)/2 cpmparison i addition to moving the array array for insertion
// If the array is already sorted teh moving around complexity i sless
vector<int> selection_sort(vector<int> arr) {
  for (int i=0; i<(arr.size() - 1); i++) {
    int min = arr[i];
    int minind = i;
    for (int j=i+1; j<arr.size(); j++) {
      if (arr[j] < min) {
        min = arr[j];
        minind = j;
      }
    }
    for (int j = minind; j>i; j--) {
      arr[j] = arr[j - 1];
    }
    arr[i] = min;
  }
  return arr;
}

void merge(vector<int>& arr, int st, int mid, int en) {
// Initialize variables to track the index and an auxillary vector
  int i = st;
  int j = mid;
  vector<int> temp;
  while (i < mid && j < en) {
    if (arr[i] <= arr[j]) { // = required for stable sort
      temp.push_back(arr[i]);
      i++;
    } else {
      temp.push_back(arr[j]);
      j++;
    }
  }
  while(i < mid) {
    temp.push_back(arr[i]);
    i++;
  }
  while(j < en) {
    temp.push_back(arr[j]);
    j++;
  }
  for (int k = 0; k < temp.size(); k++) {
    arr[st + k] = temp[k];
  }
}

void merge_sort_rec(vector<int>& arr, int st, int en) {
  if ((en - st ) == 1) return;
  int mid = (st + en)/2;
  merge_sort_rec(arr, st, mid);
  merge_sort_rec(arr, mid, en);
  merge(arr, st, mid, en);
}

//  This algorithm s worst case O(nlogn) and space complexity O(n)
vector<int> merge_sort(vector<int> arr) {
  merge_sort_rec(arr, 0, arr.size());
  return arr;
}

void quick_sort_rec(vector<int>& arr, int st, int en) {
  if ((en - st) <= 1) return;
  //int mid = (st + en)/2;
  int mid = st + rand()%(en - st);
  int pelem = arr[mid];
  int i = st + 1;
  int j = en - 1;
  int temp;
  arr[mid] = arr[st];
  arr[st] = pelem; // !Imp swap the first element with the mid to prevent never ending recursion with leftside elements being 0
  while (i <= j) { // stop when i <= j, we know all element <i are <pelem so i is the start of left partition
    if (arr[i] >= pelem) { // Follow this pattern of putting all the right side elements with == condition to avoid recursion with right side elements beign and to avoid complexity of all e;ements are equal
      temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
      j--; // Subtract j after swapping
    } else {
      i++; // Go to the next element
    }
  }
  // Edge case when all elements < pelem, no elements in the right side or i = en
  // Always make sure no partition is empty
  if (i == en) {
    //Swap arr[st] = pelem and the last element
    arr[st] = arr[en - 1];
    arr[en - 1] = pelem;
    i = en - 1;
  }
  quick_sort_rec(arr, st, i);
  quick_sort_rec(arr, i, en);
}

// O(Nlogn) average case and O(n*n) worst case time complexity and constant memory!
vector<int> quick_sort(vector<int> arr) {
  quick_sort_rec(arr, 0, arr.size());
  return arr;
}

//O(N + K) IS THE TIME complexity with space complexity O(K). K is the size of the range of elements
vector<int> counting_sort(vector<int> arr, int start, int range) {
  int offset = -1*start;
  vector<int> counter(range - start + 1);
  for (int i=0; i<arr.size(); i++) {
    counter[arr[i] + offset]++;
  }
  int ind = 0;
  for (int i=0; i < counter.size(); i++) {
    while (counter[i] > 0) {
      arr[ind] = i - offset;
      counter[i]--;
      ind ++;
    }
  }
  return arr;
}

void radix_sort_helper(vector<int>& arr, long mul) {
  vector<vector<int> > counter(10);
  for (int i=0; i<arr.size(); i++) {
    counter[(arr[i]/mul)%10].push_back(arr[i]);
  }
  int ind = 0;
  for (int i=0; i<10; i++) {
    int counterind = 0;
    while (counterind < counter[i].size()) {
      arr[ind] = counter[i][counterind];
      ind ++;
      counterind++;
    }
  }
}

void radix_sort_negative_helper(vector<int>& arr) {
  int negative = 0;
  int positive = 0;
  vector<int> out(arr.size());
  for (int i=0; i<arr.size(); i++) {
    if (arr[i] < 0) negative++;
    else positive++;
  }
  positive = negative;
  negative-= 1; // negative numbers should be in reverse
  for (int i=0; i<arr.size(); i++) {
    if (arr[i] < 0) {
      out[negative] = arr[i];
      negative--; // // negative numbers should be in reverse
    } else {
      out[positive] = arr[i];
      positive++;
    }
  }
  for (int i=0; i<out.size(); i++) {
    arr[i] = out[i];
  }
}

void radix_sort_helperwotwod(vector<int>& arr, long mul) {
  vector<int> counter(10);
  vector<int> out(arr.size());
  for (int i=0; i<arr.size(); i++) {
    counter[abs((arr[i]/mul)%10)]++; // mod value for a negative numner is just negative so
  }
  int countsum = 0;
  for(int i=0; i<10; i++) {
    int temp = counter[i];
    counter[i] = countsum;
    countsum += temp;
  }
  for (int i=0; i<arr.size(); i++) {
      out[counter[abs((arr[i]/mul)%10)]] = arr[i];
      counter[abs((arr[i]/mul)%10)]++;
  }
  for (int i=0; i<out.size(); i++) {
    arr[i] = out[i];
  }
}

// Time complexity will be O((n + b)*log_b(range)) and the space complexity O(b + n) Used in manbers and DCp
vector<int> radix_sort(vector<int> arr, int range) {
    long mul = 1;
    while(range > 0) {
      radix_sort_helperwotwod(arr, mul);
      mul*=10;
      range/=10;
    }
    return arr;
}

// Same as the time complexity for the positive numbers
vector<int> radix_sort_negative(vector<int> arr, int range) {
  long mul = 1;
  while(range > 0) {
    radix_sort_helperwotwod(arr, mul);
    mul*=10;
    range/=10;
  }
  radix_sort_negative_helper(arr);
  return arr;
}

// O(nlogn) complexity here with O(n) extra space but can be implemented without that with heapify on a vector
vector<int> heap_sort(vector<int> arr) {
  priority_queue<int, vector<int>, greater<int> >  pq;
  for (int i=0; i<arr.size(); i++) {
    pq.push(arr[i]);
  }
  int ind = 0;
  while (pq.size() > 0) {
    arr[ind] = pq.top();
    pq.pop();
    ind++;
  }
  return arr;
}

vector<int> bucket_sort(vector<int> arr, int start, int range) {
  int offset = -1*start;
  int bucketsize = 5;
  int nbuckets = (range + offset)/bucketsize + 1; // total no of poss elems (range - offset + 1) and ceil is (n - 1)/div + 1
  vector<vector<int> > buckets(nbuckets);
  for (int i=0; i<arr.size(); i++) {
    buckets[(arr[i] +  offset)/bucketsize].push_back(arr[i]);
  }
  int ind = 0;
  for (int i=0; i<buckets.size(); i++) {
    if (buckets[i].size() > 0) {
      vector<int> temp = quick_sort(buckets[i]);
      for (int i=0; i<temp.size(); i++) {
        arr[ind] = temp[i];
        ind++;
      }
    }
  }
  return arr;
}

int main() {
  int size = 10;
  int arr[]  = {1, -2, 3, 4, 5, -2, 3, 0, 7, 10};
  vector<int> vec;
  for (int i=0; i<size; i++) {
    vec.push_back(arr[i]);
  }
  printarr(bubble_sort(vec));
  printarr(selection_sort(vec));
  printarr(insertion_sort(vec));
  printarr(merge_sort(vec));
  printarr(quick_sort(vec));
  printarr(heap_sort(vec));

  // Below is for restricted sorting for only non negative integers with a range of 100
  int size1 = 11;
  int arr1[] = {0, 9, 89, 3, 56, 27, 90, 90, 90, 0, 100};
  vector<int> vec1;
  for (int i=0; i<size1; i++) {
    vec1.push_back(arr1[i]);
  }
  printarr(counting_sort(vec1, 0, 100));
  printarr(radix_sort(vec1, 100));
  printarr(bucket_sort(vec1, 0, 100));

  // Restricted integer testing with negative integers from -100 to 100
  int size2 = 12;
  vector<int> vec2;
  int arr2[] = {0, 0, 4, -4, -50, 45, -90, -85, 36, 90, 100, -100};
  for (int i=0; i<size2; i++) {
    vec2.push_back(arr2[i]);
  }
  printarr(counting_sort(vec2, -100, 100));
  printarr(radix_sort_negative(vec2, 100));
  printarr(bucket_sort(vec2, -100, 100));
  return 0;
}

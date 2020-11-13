# include <iostream>
# include <vector>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
  return a.second < b.second;
}

void print_vec(vector<pair<int, int> >& arr) {
  for (int i=0; i<arr.size(); i++) {
    cout<<arr[i].first<<", "<<arr[i].second<<"  ";
  }
  cout<<'\n';
}

void print_vec(vector<int>& arr) {
  for (int i=0; i<arr.size(); i++) {
    cout<<arr[i]<<' ';
  }
  cout<<'\n';
}

// Rank the suffixes based on the sorting order and the approx ranks in suf arr
void simplerank(vector<pair<int, int> >& sufarr, vector<int>& prevrank) {
  int prev = sufarr[0].second;
  for (int i=0; i<sufarr.size(); i++) {
    cout<<prev<<' '<<sufarr[i].second<<'\n';
    int sufpos = sufarr[i].first;
    if (i == 0) prevrank[sufpos] = 0;
    else if (sufarr[i].second == prev) prevrank[sufpos] = sufarr[i - 1].second;
    else      prevrank[sufpos] = sufarr[i - 1].second + 1;
    prev = sufarr[i].second;
    sufarr[i].second = prevrank[sufpos];
  }
  print_vec(prevrank);
}

// one with pairs of both index and value
// And the other to store any idex specific information to access by index
void constructSufArray(string& text, vector<pair<int, int> >& sufarr) {
  int base = text.size(); // choosing this as because ranks are at most size -1
  vector<int> prevrank(text.size()); // Stores the rank in the previous iteration
  for (int i=0; i<text.size(); i++) {
    sufarr[i].second = text[i];
    sufarr[i].first = i; // Index is also attached to infer from pos after sort
  }
  sort(sufarr.begin(), sufarr.end(), cmp);

  int offset = 1;
  while (offset < text.size()) {
    simplerank(sufarr, prevrank); // Reassigns ranks and pushes current rank to prevrank
    for (int i=0; i<text.size(); i++) {
      sufarr[i].first = i;
      if ((i + offset) >= text.size()) sufarr[i].second = base*prevrank[i] + 0;
      else sufarr[i].second = base*prevrank[i] +  prevrank[i + offset];
    }
    sort(sufarr.begin(), sufarr.end(), cmp); // prevrank indexed on sufpos and sufarr on rank/sorting index
    offset = 2*offset;
    print_vec(sufarr);
  }
}

int main() {

  string text = "aaaaa";
  vector<pair<int, int> > sufarr(text.size());
  constructSufArray(text, sufarr);
  print_vec(sufarr);

  return 0;
}

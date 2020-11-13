# include <iostream>
# include <vector>
using namespace std;

// prefix can be defined to be the longes length prefix of pattern which is a suffix of
// 0.....i
void preprocess(vector<int>& prefix, string& pattern) {
  prefix[0] = 0;
  int k = 0;
  for (int i=1; i<pattern.size(); i++) {
    while (pattern[k] != pattern[i] && k > 0) {
      k = prefix[k];
    }
    if (pattern[k] == pattern[i]) {
      k++;
    }
    prefix[i] = k;
  }
}

// O(m + n) algorithm to find pattern in a text
void findPattern(string& text, string& pattern) {
  vector<int> prefix(pattern.size());
  preprocess(prefix, pattern);
  int k = 0;
  for (int i=0; i<text.size(); i++) {
    while (text[i] != pattern[k] && k > 0) {
      k = prefix[k];
    }
    if (text[i] == pattern[k]) {
      k++;
    }
    if (k == pattern.size()) {
      cout<<"Pattern found at "<<(i + 1 - pattern.size())<<"\n";
      k = prefix[pattern.size() - 1];
    }
  }
}

// Look at how simple it is!
void findPatternZ(string& text, string& pattern) {
  string jux = pattern + '$' + text; // Use a unique delimitter
  vector<int> prefix(jux.size());
  int k = 0;
  prefix[0] = 0;
  for (int i=1; i<jux.size(); i++) {
    k = prefix[i-1];
    while(jux[k] != jux[i] && k > 0) {
      k = prefix[k];
    }
    if (jux[k] == jux[i]) {
      k++; // k increments ny atmost one in every iteration
    }
    prefix[i] = k; // If above condition does not hold then prefix[i] is basically 0
    if (k == pattern.size()) {
      cout<<"Pattern found at "<<(i - 2*pattern.size())<<"\n";
      k = prefix[pattern.size() - 1];
    }
  }
}

int main() {
  string text = "Quick Brown Fox jumped over a lazy Brown fox";
  string pattern = "Brown";
  findPattern(text, pattern);
  findPatternZ(text, pattern);
  return 0;
}

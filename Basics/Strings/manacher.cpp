# include <iostream>
# include <vector>
using namespace std;

// O(n) algorithm to return the longest palindrome string
int manacher(string& str) {
  string strmod = "";
  strmod.push_back('$');
  for (int i=0; i<str.size(); i++) {
    strmod.push_back(str[i]);
    strmod.push_back('$'); //Special character not present in the string. Formed string is line $a$b$c$d$
  }
  vector<int> palsize(strmod.size());

  int cen = 0;
  int rightext = 0;

  int longestpal = 1;
  int anscen = 0;
  for (int i=0 ; i<strmod.size(); i++) {
    int mirror = 2*cen - i;
    int pallength = 0;
    if (mirror >= 0) pallength = palsize[mirror]; // Imp to add mirror >= 0, as cen < i mirror < i

    if ((i + pallength) >= rightext) {
      cen = i;
      rightext = min(i + pallength, rightext); // Update the rightext and corresponding centre
      int templength = pallength + 1; // Start from next ind to expand around new centre
      while ((cen - templength) >= 0 && (cen + templength) < strmod.size()) {
        if (strmod[cen - templength] != strmod[cen + templength]) break;
        rightext = cen + templength;
        pallength = templength; // rightext and pallength moves right incrementally
        templength++;
      }
    }

    palsize[i] = pallength;
    if (pallength > longestpal) { // Update with longest
      longestpal = pallength;
      anscen = i;
    }
  }
  cout<<"Longest palindrome at centre "<<anscen<<" with length "<<longestpal<<'\n';
  return longestpal; // longest pal same as the half pal size!
}

int main() {
  string str = "palindromemordnilap";
  string str1 = "wrongmissisippipalindromeemordnilap";
  string str2 = "fwdfjpalindromemordnilapqqqkfw";
  string str3 = "aaaaaaaaaa";
  string str4 = "aaaaabaaaaasfkfwe";
  manacher(str);
  manacher(str1);
  manacher(str2);
  manacher(str3);
  manacher(str4);
  return 0;
}

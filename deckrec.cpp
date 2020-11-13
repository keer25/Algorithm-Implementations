# include <iostream>
# include <vector>
# include <deque>
# include <algorithm>
using namespace std;

inline int fsize(vector<int>::iterator st, vector<int>::iterator en) {
        return en - st;
    }

    void deckSortRec(vector<int>::iterator st, vector<int>::iterator en) {
        int size = fsize(st, en);
        if (size == 1) return;
        // Sprt all the elements
        int mid = (size + 1)/2;
        //sort(st, st + mid);
        deckSortRec(st + mid, en);
        vector<int> ans;
        vector<int>::iterator temp;
        int flag;
        for(temp = st; temp< (st + mid) && (mid + temp) < en; temp++) {
            ans.push_back(*temp);
            if (size%2 == 1 && temp == st) {
              ans.push_back(*(st + size - 1));
              flag = 1;
            }
            else ans.push_back(*(temp + mid - flag));
        }
        if (temp < (st + mid)) ans.push_back(*temp);
        for (int i = 0;(st + i) < en  ; i++) {
            *(st + i) = ans[i];
            cout<<ans[i]<<' ';
        }
        cout<<'\n';
    }

    vector<int> deckRevealedIncreasing(vector<int>& deck) {
       // vector<int> dq;
        deckSortRec(deck.begin() ,deck.end());
        return deck;
    }

int main() {
  int myints[] = {17,13,11,2,3,5,7};
  vector<int> deck(myints, myints + sizeof(myints) / sizeof(int));
  sort(deck.begin(), deck.end());
  deckRevealedIncreasing(deck);
  for (int i=0; i<deck.size(); i++) {
  cout<<deck[i]<<' ';
  }
   return 0;
}

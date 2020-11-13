# include <iostream>
# include <list>
using namespace std;

class HashTable {
  //  int capacity;
    list<pair<int, int> > table[1000]; // It is important to store pairs in the table!!

    int hash(int key) {
      return key%1000;
    }
    public :
    void insert(int key, int value) {
      int ind = hash(key);
      table[ind].push_back(make_pair(key, value));
    }
    void erase (int key) {
      int ind = hash(key);
      list<pair<int, int> >::iterator it = findit(key);
      if (it != table[ind].end()) table[ind].erase(it);
      else cout<<"Key Not Found\n";
    }
    int find(int key) {
      int ind = hash(key);
      list<pair<int, int> >::iterator it = findit(key);
      if (it != table[ind].end()) return it->second;
      cout<<"Key Not Found\n";
      return -1;
    }

    list<pair<int, int> >::iterator findit(int key) {
      int ind = hash(key);
      list<pair<int, int> >::iterator it = table[ind].begin();
      while (it != table[ind].end()) {
        if (it->first == key) return it;
        it++;
      }
      return table[ind].end();
    }

    bool isexists(int key) {
      int ind = hash(key);
      list<pair<int, int> >::iterator it = findit(key);
      if (it != table[ind].end()) return true;
      return false;
    }
};

int main() {
  HashTable ht = *(new HashTable());
  ht.insert(1, 2);
  cout<<ht.find(1)<<'\n';
  cout<<ht.find(1)<<'\n';
  ht.erase(1);
  ht.find(1);
  return 0;
}

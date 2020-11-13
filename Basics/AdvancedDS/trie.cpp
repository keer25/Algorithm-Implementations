# include <iostream>
# include <vector>
# include <string>
using namespace std;

struct TrieNode {
  char c;
  vector<TrieNode*> children;
  bool isEndOfWord;

  TrieNode(char c) {
    this->c = c;
    children.resize(26);
    for (int i=0; i<26; i++) {
      this->children[i] = NULL;
    }
    this->isEndOfWord = false;
  }
};

void addWordRec(TrieNode* root, string& word, int ind) {
  if (ind == word.size()) {
    root->isEndOfWord = true;
    return;
  }
  if (root->children[word[ind] - 'a'] == NULL) {
    root->children[word[ind] - 'a'] = new TrieNode(word[ind]);
  }
  addWordRec(root->children[word[ind] - 'a'], word, ind + 1);
}

TrieNode* addWord(TrieNode* root, string& word) {
  addWordRec(root, word, 0);
  return root;
}

TrieNode* constructTrie(vector<string>& dict) {
  TrieNode* root = new TrieNode('*');
  for (int i=0; i<dict.size(); i++) {
    addWord(root, dict[i]);
  }
  return root;
}

bool isWord(TrieNode* root, string& word) {
  TrieNode* tempNode = root;
  int i = 0;
  while (i < word.size()) {
    if (tempNode->children[word[i] - 'a'] == NULL) return false;
    cout<<"Found "<<word[i]<<'\n';
    tempNode = tempNode->children[word[i] - 'a'];
    i++;
  }
  return tempNode->isEndOfWord;
}

bool isSuffix(TrieNode* root, string& word) {
  TrieNode* tempNode = root;
  int i = 0;
  while (i < word.size()) {
    if (tempNode->children[word[i] - 'a'] == NULL) return false;
    cout<<"Found "<<word[i]<<'\n';
    tempNode = tempNode->children[word[i] - 'a'];
    i++;
  }
  return true;
}

int main() {
  vector<string> dict;
  dict.push_back("hello");
  dict.push_back("helloworld");
  dict.push_back("garage");
  dict.push_back("india");
  TrieNode* root = constructTrie(dict);
  string temp = "hello";
  cout<<isWord(root, temp)<<'\n';
  temp = "hell";
  cout<<isWord(root, temp)<<'\n';
  cout<<isSuffix(root, temp)<<'\n';
  temp = "helloworld";
  cout<<isWord(root, temp)<<'\n';
  return 0;
}

# include <iostream>
int giveVal(char c){
    return (int)  c - 'a';
}

 class TrieNode {
     public :

    char c;
    TrieNode* children[26];
    bool isEnd;

    TrieNode() {
        for (int i=0; i<26; i++) {
            children[i] = nullptr;
        }
    }

    TrieNode(char c) {
        this->c = c;
        this->isEnd = false;
        for (int i=0; i<26; i++) {
            children[i] = nullptr;
        }
    }
};
 // The code can be much simpler
void pushTrieNodes(string& s, int ind, TrieNode *node) {
        int val = giveVal(s.at(ind));
        if (node->children[val] == nullptr) {
            TrieNode *newNode = new TrieNode(s.at(ind));
            node->children[val] = newNode;
            if (ind < s.size() - 1) {
            pushTrieNodes(s, ind + 1, newNode);
            } else {
                node->children[val]->isEnd = true;
            }
        } else {
            if (ind < s.size() - 1) {
            pushTrieNodes(s, ind + 1, node->children[val]);
            } else {
                node->children[val]->isEnd = true;
            }
        }
}

TrieNode* generateTrie(vector<string>& wordDict) {
    TrieNode *root = new TrieNode('*');
    for (int i=0; i<wordDict.size(); i++) {
        pushTrieNodes(wordDict[i], 0, root);
    }
    return root;
}

int main() {
  //generateTrie(wordDict);
  return 0;
}

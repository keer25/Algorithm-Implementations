# include <iostream>
# include <queue>
using namespace std;

struct TreeNode {
  int val;
  vector<TreeNode*> children;
// Sometimes TreeNode can have additional value stored or even have a link to the parent node
  TreeNode(int val) {
    this->val = val;
  }
};

// No need to track visited in a tree as there are no cycles! Each element has one parent
void bfs(TreeNode* root) {
  queue<TreeNode*> bfsq;
  bfsq.push(root);
  while (bfsq.size() > 0) {
    TreeNode* elem = bfsq.front();
    bfsq.pop(); // Don't forset to pop to avoid recusion!
    cout<<elem->val<<' ';
    for (int i=0; i<elem->children.size(); i++) {
      bfsq.push(elem->children[i]); // Push the node not just the value!
    }
  }
}

void dfs(TreeNode* root) {
  if (root == NULL) return;
  cout<<root->val<<' ';
  for (int i=0; i<root->children.size(); i++) {
    dfs(root->children[i]);
  }
}

vector<TreeNode*> newNodes(int arr[], int size) {
  vector<TreeNode*> nodes;
  for (int i=0; i<size; i++) {
    nodes.push_back(new TreeNode(arr[i]));
  }
  return nodes;
}

int main() {
  TreeNode* root = new TreeNode(1);
  int size = 5;
  int arr[] = {1, 2, 3, 4, 5};
  root->children = newNodes(arr, size);
  root->children[1]->children = newNodes(arr, size);
  bfs(root);cout<<'\n';
  dfs(root);cout<<'\n';
  return 0;
}

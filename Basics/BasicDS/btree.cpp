# include <iostream>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left = NULL;
  TreeNode* right = NULL;
  TreeNode(int val) {
    this->val = val;
  }
  TreeNode(int val, TreeNode* left, TreeNode* right) {
    this->val = val;
    this->left = left;
    this->right = right;
  }
};

void preorder(TreeNode* root) {
  if (root == NULL) return;
  cout<<root->val<<' ';
  preorder(root->left);
  preorder(root->right);
}

void inorder(TreeNode* root) {
  if (root == NULL) return;
  inorder(root->left);
  cout<<root->val<<' ';
  inorder(root->right);
}

void postorder(TreeNode* root) {
  if (root == NULL) return;
  postorder(root->left);
  postorder(root->right);
  cout<<root->val<<' ';
}

int main() {
  TreeNode* root = new TreeNode(1);
  root->right = new TreeNode(3, new TreeNode(4), new TreeNode(5));
  root->left = new TreeNode(2);
  preorder(root);
  cout<<'\n';
  inorder(root);
  cout<<'\n';
  postorder(root);
  cout<<'\n';
  return 0;
}

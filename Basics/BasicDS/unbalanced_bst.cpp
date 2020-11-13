# include <iostream>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left = NULL;
  TreeNode* right = NULL;
  TreeNode(int val) {
    this->val = val;
  }
};

// Only in case where left child exists
TreeNode* findInorder(TreeNode* root) {
  while (root->left != NULL) root = root->left;
  return root;
}

// Important to return the root node for all algorithms to make a smooth implementation
TreeNode* insert(TreeNode* root, int elem) {
  if (root == NULL) return new TreeNode(elem);
  else if (elem <= root->val) { // <= and > criterial depends on the definition of the binary tree
    root->left = insert(root->left, elem); // I1mportant to assign to the appropriate pointer for when new nodes are created, this is a elegant approach to generalised ti for all scenarios
  } else {
    root-> right = insert(root->right, elem);
  }
  return root;
}

TreeNode* find(TreeNode* root, int elem) {
  if (root == NULL) return NULL;
  else if (elem < root->val) {
    return find(root->left, elem);
  } else if (elem > root->val) {
    return find(root->right, elem);
  } else {
    return root;
  }
}

TreeNode* erase(TreeNode* root, int elem) {
  if (root == NULL) return root;
  else if (elem < root->val) {
    root->left = erase(root->left, elem);
  } else if (elem > root->val){
    root->right = erase(root->right, elem);
  } else {
    TreeNode* temp;
    if (root->left == NULL || root->right == NULL) {
      if (root->left != NULL) {
        temp = root->left;
        delete root;
        root = temp;
      } else if (root->right != NULL) {
        temp = root->right;
        delete root;
        root = temp;
      } else {
        delete root;
        return NULL;
      }
    }
    else {
      temp = findInorder(root->right);
      root->val = temp->val;
      root->right = erase(root->right, temp->val);
    }
  }
  return root;
}

void inorder(TreeNode* root) {
  if (root == NULL) return;
  inorder(root->left);
  cout<<root->val<<' ';
  inorder(root->right);
}

int main() {
  TreeNode* root = NULL;
  root = insert(root, 50);
	root = insert(root, 30);
	root = insert(root, 20);
	root = insert(root, 40);
	root = insert(root, 70);
	root = insert(root, 60);
	root = insert(root, 80);
  inorder(root); cout<<'\n';
  root = erase(root, 50);
  root = erase(root, 30);
  inorder(root); cout<<'\n';

  root = erase(root, 70);
  inorder(root); cout<<'\n';
  root = erase(root, 50);
  inorder(root); cout<<'\n';


  return 0;
}

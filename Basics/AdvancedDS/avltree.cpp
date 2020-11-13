# include <iostream>
using namespace std;

struct TreeNode {
  TreeNode* parent;
  TreeNode* left;
  TreeNode* right;
  int key;
  int height;

  TreeNode(int key) {
    this->key = key;
    height = 1; // height is 1 for leaf nodes
    left = NULL;
    right = NULL;
    parent = NULL;
  }
};

void inorder(TreeNode* root) {
  //cout<<"Printing\n";
  if (root == NULL) return;
  inorder(root->left);
  int parentkey = (root->parent!=NULL) ?root->parent->key : -1;
  cout<<root->key<<", "<<root->height<<", "<<parentkey<<"    ";
  inorder(root->right);
}

int height(TreeNode* root) {
  if (root == NULL) return 0;
  return root->height;
}

// Inorder is least element >= the element
// Only in case where right child exists hence we find the minimum value in the right tree
// Other wise inorder element will be the first ancestor in which subtree is a left child
TreeNode* findInorder(TreeNode* root) {
  while (root->left != NULL) root = root->left;
  return root;
}

TreeNode* leftRotate(TreeNode* root) {
  if (root->right == NULL) {cout<<"Invalid Rotation\n"; return root; }
  TreeNode* temp = root;

  // Reassign parents
  root->right->parent = root->parent;
  root->parent = root->right;
  if (root->right->left!= NULL)root->right->left->parent = root; // This could be null

  // Change the bonds
  root = root->right;
  temp->right = root->left;
  root->left = temp;

  // Recalculate height, remomber to do it for subtree first
  root->left->height = max(height(root->left->left), height(root->left->right)) + 1;
  root->height = max(height(root->left), height(root->right)) + 1;
  return root;
}

TreeNode* rightRotate(TreeNode* root) {
  if (root->left == NULL) {cout<<"Invalid Rotation\n"; return root;}
  TreeNode* temp = root;
  root->left->parent = root->parent;
  root->parent = root->left;
  if (root->left->right != NULL) root->left->right->parent = root;

  root = root->left;
  temp->left = root->right;
  root->right = temp;

  root->right->height = max(height(root->right->left), height(root->right->right)) + 1;
  root->height = max(height(root->left), height(root->right)) + 1;
  return root;
}

TreeNode* getbalance(TreeNode* root) {
  if (abs(height(root->left) - height(root->right)) > 1) {
    TreeNode* z = root;
    TreeNode* y = (height(z->left) > height(z->right)) ? z->left : z->right;
    TreeNode* x = (height(y->left) > height(y->right)) ? y->left : y->right;

    //Case 1 , y left child, x right child -> Case 2
    if (y == z->left && x == y->right) y = leftRotate(y);
    // Case 2, y left child, x left child
    if (y == z->left && x == y->left) {z = rightRotate(z); return z;}

    // Case 3, y right child, x left child -> Case 4
    if (y == z->right && x == y->left) y = rightRotate(y);
    // Case 4, y right chile, x right child
    if (y == z->right && x == y->right) {z = leftRotate(z); return z;}
  }
  return root;
}

TreeNode* insertNode(TreeNode* root, int key) {
  if (root == NULL) return new TreeNode(key);
  if (key <= root->key) {
    root->left = insertNode(root->left, key);
    //if (root->left != NULL)
    root->left->parent = root;
  } else {
    root->right = insertNode(root->right, key);
    //if (root->right != NULL)
    root->right->parent = root;
  }
  root->height = max(height(root->left), height(root->right)) + 1; // Update height then rebalance
  return getbalance(root); // Balancing automatically reassigns parents and heights
}

TreeNode* deleteNode(TreeNode* root, int key) {
  if (root == NULL) return NULL;
  if (key < root->key) {
    root->left = deleteNode(root->left, key);
  } else if (key > root->key) {
    root->right = deleteNode(root->right, key);
  } else { // Found a match
    TreeNode* temp;
    if (root->left == NULL || root->right == NULL) { // Assigning parents taken care here
      if (root->left != NULL) {
        root->left->parent = root->parent;
        temp = root->left;
        delete root;
        root = temp;
      } else if (root->right != NULL) {
        root->right->parent = root->parent;
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
      root->key = temp->key;
      root->right = deleteNode(root->right, temp->key);
    }
  }
  root->height = max(height(root->left), height(root->right)) + 1; // standard formula for height
  return getbalance(root);
}

int main() {
  TreeNode* root = NULL;
  root = insertNode(root, 20);
  root = insertNode(root, 30);
  root = insertNode(root, 40);
  root = insertNode(root, 10);
  root = insertNode(root, 8);
	root = insertNode(root, 6);
	root = insertNode(root, 80);
  inorder(root);cout<<'\n';
  root = deleteNode(root, 10);
  inorder(root);cout<<'\n';
  root = deleteNode(root, 6);
  root = deleteNode(root, 8);
  inorder(root);cout<<'\n';
  return 0;
}

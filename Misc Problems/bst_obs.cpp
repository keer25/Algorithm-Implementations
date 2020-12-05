# include <iostream>
#include <utility>

using namespace std;
template <typename T>
struct TreeNode {
	T data;
	TreeNode* left = NULL;
	TreeNode* right = NULL;
};

template <typename T>
void insert(TreeNode<T>* root, const T& value) {
	if (root == NULL) {
		return;
	} else {
		if (value <= root->data) {
      if (root-> left == NULL) {
        root->left = new TreeNode<T>;
        root->left->data = value;
        return;
      }
			insert(root->left, value);
		} else {
    if (root-> right == NULL) {
      root->right = new TreeNode<T>;
      root->right->data = value;
      return;
    }
			insert(root->right, value);
		}
	}
}

template <typename T>
TreeNode<T>* find(TreeNode<T>* root, T value) {
	if(root == NULL) return NULL;
	if ( root->data == value) return root;
	if (value < root->data) return find(root->left, value);
	else return find(root->right, value);
}

template <typename T>
pair<TreeNode<T>*, TreeNode<T>*> findWithParent(TreeNode<T>* parent, TreeNode<T>* root, T value) {
  TreeNode<T>* n = nullptr;
	if(root == NULL) return make_pair(n, n);
  cout<<"dat ="<<root->data<<'\n';
	if ( root->data == value) {
  //cout<<"Data Fount"<<parent->data<<'\n';
  return make_pair(parent, root);
  }
	if (value <= root->data) return findWithParent(root, root->left, value);
	else return findWithParent(root, root->right, value);
}

template <typename T>
TreeNode<T>* findLeafNode(TreeNode<T>* node) {
	TreeNode<T>* temp = node;
	while(temp->left != NULL) {
		temp = node -> left;
	}
  cout<<"Found Place at :"<<temp->data<<'\n';
	return temp;
}

// The operation is bad because you can just copy the next element in inorder to the node space and delete that element
template <typename T>
void remove(TreeNode<T>* root, T value) {
  TreeNode<T>* n = nullptr;
	pair<TreeNode<T>*, TreeNode<T>*> ans = findWithParent(n, root, value);
  cout<<"What shit"<<'\n';
  cout<<"Wth!"<<'\n';
  //cout<<"data found : "<<ans.second->data<<" with parent"<<ans.first->data<<'\n';

  cout<<"Whats wrong"<<'\n';
	TreeNode<T>* node = ans.second;
	if (node == NULL) return;
	TreeNode<T>* newNode = NULL;

  cout<<"Created"<<'\n';
	if (node->left != NULL &&  node->right!= NULL) {
  cout<<"Finding a place to insert"<<'\n';
TreeNode<T>* place =  findLeafNode(node->right);
		place->left = node->left;
		newNode = node->left;
}

if (node->right == NULL && node->left!= NULL) {
	newNode = node->right;
}

if (ans.first == NULL) return;
if (ans.first->left == node) ans.first->left = newNode;
if(ans.first->right == node) ans.second->left = newNode;
delete node;
}

template <typename T>
void traverseTree(TreeNode<T>* root) {
  if (root != NULL) {
  traverseTree(root->left);
  cout<<root->data<<'\n';
  traverseTree(root->right);
}
}

int main() {
  cout<<"Hello"<<'\n';
  TreeNode<int> node1;
  //TreeNode<int> node2;
  //TreeNode<int> node3;
  //node3->left = node2;
  //node2->left = node1;
  node1.data = 5;
  traverseTree(&node1);
  insert(&node1, 3);
  traverseTree(&node1);
  insert(&node1, 2);
  traverseTree(&node1);
  insert(&node1, 6);
  traverseTree(&node1);
  remove(&node1, 2);
  remove(&node1, 5);
  traverseTree(&node1);
  return 0;
}

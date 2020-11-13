# include <iostream>
using namespace std;

struct LinkedListNode {
  int val;
  LinkedListNode* right;
  LinkedListNode* left;

  LinkedListNode(int val) {
    this->val = val;
    this->right = NULL;
    this->left = NULL; // !IMP to declare them as NULL
  }
};

class LinkedList {
  LinkedListNode* head;
  LinkedListNode* tail;
  public :
  LinkedList() {
    head = NULL;
    tail = NULL;
  }

  LinkedListNode* insert(int val) {
    LinkedListNode* temp = new LinkedListNode(val);
    if (head == NULL) head = tail = temp;
    else {
      tail->right = temp;
      temp->left = tail;
      tail = temp;
    }
    return head;
  }

  LinkedListNode* erase(LinkedListNode* node) {
    if (head == NULL) return NULL;
    else if (head == tail) {
      head = tail = NULL;
    } else if (node == head) {
      head = head->right;
      head->left = NULL;
    } else if (node == tail) {
      tail = tail->left;
      tail->right = NULL;
    } else {
      node->left->right = node->right;
      node->right->left = node->left;
    }
    delete node;
    return head;
  }

  LinkedListNode* find(int val) {
    LinkedListNode* temp = head;
    while (temp != NULL) {
      if (temp->val == val) return temp;
      temp = temp->right;
    }
    return NULL;
  }

  void printlist()  {
    LinkedListNode* temp = head;
    while(temp != NULL) {
      cout<<temp->val<<' ';
      temp = temp->right;
    }
    cout<<'\n';
  }
};

int main() {
  LinkedList ll = *(new LinkedList());
  ll.insert(5);
  ll.insert(9);
  ll.printlist();
  ll.erase(ll.find(9));
  cout<<(ll.find(5))->val<<'\n';
  return 0;
}

# include <iostream>
using namespace std;

struct LinkedListNode {
  LinkedListNode* link;
  int value;
};

class LinkedList {
  LinkedListNode* head;

  public :

  LinkedList(LinkedListNode* node) {
    head = node;
  }

  LinkedList() {
    head = nullptr;
  }

  void appendAtHead(int value) {
    LinkedListNode* node = (LinkedListNode*) malloc(sizeof(LinkedListNode));
    node->value = value;
    node->link = head;
    head = node;
  }

// Delete the first node in the linkedlist
  void deleteNode(int value) {
    LinkedListNode* tempNode = head;
    LinkedListNode* tempPrevNode = nullptr;
    while (tempNode != nullptr) {
      if(tempNode->value == value) {
        if (tempPrevNode == nullptr) {
          head = head->link;
          delete tempNode;
        } else {
          tempPrevNode->link = tempNode->link;
          delete tempNode;
        }
        return;
      } else {
        tempPrevNode = tempNode;
        tempNode = tempNode->link;
      }
    }
    if (tempNode == nullptr) {
      cout<<"Value not present";
    }
  }

  LinkedListNode* searchNode(int value) {
    LinkedListNode* tempNode = head;
    while (tempNode != nullptr) {
      if (tempNode->value == value) {
        return tempNode;
      } else {
        tempNode = tempNode->link;
      }
    }
    return nullptr;
  }

  void traverseList() {
    LinkedListNode* tempNode = head;
    while (tempNode != nullptr) {
      cout<<tempNode->value<<' ';
      tempNode = tempNode->link;
    }
    cout<<'\n';
  }
};

int main() {
  LinkedListNode* head = (LinkedListNode*) malloc(sizeof(LinkedListNode));
  head->value = 1;
  head-> link = nullptr;
  LinkedList* list = new LinkedList(head);
  list->appendAtHead(2);
  list->appendAtHead(3);
  list->appendAtHead(4);
  list->traverseList();
  list->deleteNode(1);
  list->traverseList();
  list->deleteNode(3);
  list->traverseList();
  list->deleteNode(4);
  list->traverseList();
  return 0;
}

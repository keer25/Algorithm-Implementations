# include <iostream>
using namespace std;

struct KVPair{
  string value;
  int key;
};

struct LinkedListNode {
  KVPair value;
  LinkedListNode* link;
};

class LinkedList {
  LinkedListNode* head;

  public:
  void appendAtHead(KVPair pair) {
    LinkedListNode* node = (LinkedListNode*) malloc(sizeof(LinkedListNode));
    node->value = pair;
    node->link = head;
    head = node;
  }

  void deleteNode(int key) {
    LinkedListNode* tempNode = head;
    LinkedListNode* tempPrevNode;
    while(tempNode != nullptr) {
      if (tempNode->value.key == key) {
        cout<<"Key "<<tempNode->value.value<<" is deleted";
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
      cout<<"Value does not exist";
    }
  }

  void searchNode(int key) {
    LinkedListNode* tempNode = head;
    while (tempNode != nullptr) {
      if(tempNode->value.key == key) {
        cout<<"The value is "<<tempNode->value.value;
        return;
      } else {
        tempNode = tempNode->link;
      }
    }
    cout<<"Key not found";
  }
};

class HashTable {
  LinkedList table[1000];

  int hash(int key) {
    return key%1000;
  }
  public :
  void append(KVPair p) {
    table[hash(p.key)].appendAtHead(p);
  }

  void search(int key) {
    table[hash(key)].searchNode(key);
  }

  void deleteKey(int key) {
    table[hash(key)].deleteNode(key);
  }

};

int main() {
  HashTable hashTable;
  hashTable.append((KVPair) {"one", 1});
  hashTable.search(1);
  hashTable.deleteKey(1);
  return 0;
}

# include <iostream>
using namespace std;

template <typename T>
struct StackNode {
    T value;
    StackNode* link;
};

template <typename T>

class Stack {
  StackNode<T>* ref = nullptr;

  public :
  void push(T value) {
    StackNode<T>* node = new StackNode<T>;
    node->value = value;
    node->link = ref;
    ref = node;
  }

  void pop() {
    if (ref == nullptr) return;
    ref = ref->link;
  }

  T top() {
    return ref->value;
  }
};

int main() {
  Stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);

  cout<<stack.top();
  stack.pop()<<'\n';
  cout<<stack.top();
  stack.pop()<<'\n';
  cout<<stack.top();
  stack.pop()<<'\n';
  return 0;
}

# include <iostream>
# include <vector>
using namespace std;

// Stack implemetion using vectors but using linked list implemetion is more appropriate
// Can also be implemetion through a singly linked linked list
class Stack {
  vector<int> arr;
  public :
  int top() {
  if (arr.size() == 0) return -1;
  else return arr.back();
  }

  void push(int elem) {
    arr.push_back(elem);
  }

  int pop() {
  if (arr.size() == 0) {
    int temp = arr.back();
    arr.pop_back();
    return temp;
    } else return -1;
  }

  int size() {
    return arr.size();
  }
};

int main() {
  Stack st = *(new Stack());
  cout<<st.top()<<'\n';
  st.push(1);
  st.push(2);
  st.push(3);
  st.pop();
  cout<<st.top()<<'\n';
  st.pop();
  st.pop();
  st.pop();
  return 0;
}

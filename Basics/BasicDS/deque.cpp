# include <iostream>
# include <stack>
using namespace std;

// Deque implementation using two stacks
class Deque {
  stack<int> left;
  stack<int> right;

  void copy(stack<int>& from, stack<int>& to) {
    while (from.size() > 0) {
      to.push(from.top());
      from.pop();
    }
  }

  int pop(stack<int>& pri, stack<int>& sec) {
    int popped;
    if (pri.size() > 0) {
      popped = pri.top();
      pri.pop();
    } else {
      copy(sec, pri);
      if (pri.size() > 0) {
        popped = pri.top();
        pri.pop();
      } else {
        cout<<"Invalid Operation";
      }
    }
    return popped;
  }

  int top(stack<int>& pri, stack<int>& sec) {
    int val;
    if (pri.size() > 0) {
      val = pri.top();
    } else {
      copy(sec, pri);
      if (pri.size() > 0) {
        val = pri.top();
      } else {
        cout<<"Invalid Operation";
      }
    }
    return val;
  }
  public :
  void push_back(int elem) {
    right.push(elem);
  }

  int pop_back() {
    return pop(left, right);
  }

  void push_front(int elem) {
    left.push(elem);
  }

  int pop_front() {
    return pop(right, left);
  }

  int back() {
    return top(left, right);
  }

  int front() {
    return top(right, left);
  }

  int size() {
    return left.size() + right.size();
  }
};

int main() {
  Deque dq = *(new Deque());
  dq.push_back(1);
  dq.push_back(2);
  dq.pop_front();
  dq.pop_back();
  cout<<dq.back()<<'\n';
  return 0;
}

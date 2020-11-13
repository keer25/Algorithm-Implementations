# include <iostream>
using namespace std;

// Cna also be implemneted using DLLinked List
class Queue {
  int capacity = 5;
  int arr[5];
  int front = -1;
  int rear = -1;

  int incrementfront() {
    if (front == -1) {
      cout<<"Empty Queue\n";
      return -1;
    }
    if (front == rear) {
      front = -1;
      rear = -1;
      return 0;
    }
    int temp = front;
    if (front == capacity - 1) front = 0;
    else front = front + 1;
    return temp;
  }

  int incrementrear() {
    if (front == -1) {
      front = 0;
      rear = 0;
      return 0;
    }
    int temp;
    if (rear == capacity - 1) temp = 0;
    else temp = rear + 1;
    if (temp == front) {return -1; cout<<"Capacity Full\n";}
    else rear = temp;
    return rear;
  }
  public :
  void push(int elem) {
    if (incrementrear() != -1) {
      arr[rear] = elem;
    }
  }
  int pop() {
    int temp = arr[front];
    if (incrementfront() != -1)
      return temp;
    return -1;
  }
  int size() {
    if (rear >= front) return rear - front + 1;
    else return capacity - front + rear + 1;
  }
  int frontelem() {
    return arr[front];
  }
};
int main() {
  Queue arr = *(new Queue());
  arr.push(1);
  arr.push(2);
  arr.push(3);
  arr.push(4);
  cout<<arr.pop()<<'\n';
  cout<<arr.pop()<<'\n';
  arr.push(5);
  cout<<arr.size()<<'\n';
  return 0;
}

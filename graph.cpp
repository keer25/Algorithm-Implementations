# include <iostream>
using namespace std;

class Graph{
  vector<Node*> nodes;
}

template <typename T>
class Node{
  T data;
  vector<Node*> edges;
}

// Implement bfs and dfs

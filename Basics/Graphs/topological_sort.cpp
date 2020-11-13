# include <iostream>
# include <unordered_map>
# include <vector>
# include <stack>
using namespace std;
typedef unordered_map<int, vector<int> > al;

stack<int> sorted;
// Reverse of the printing is the answer
void initialize_graph(al& graph, int n) { // Graph with nodes from 0 to n-1 is a good generalization o.w have a mappign of the nodes to these indices
  for (int i=0; i<n; i++) {
    graph[i] = *(new vector<int>);
  }
}

void add_edge_d(al& graph, int u, int v) {
  graph[u].push_back(v);
}

// Simple DFS with path tracking
void dfs_rec(al& graph, int node, vector<bool>& visited, vector<bool>& grey) {
  visited[node] = true;
  grey[node] = true;
  for (int i=0; i<graph[node].size(); i++) {
    int child = graph[node][i];
    if (visited[child]) {
      if (grey[child]) {
        cout<<"No order possible\n";
      }
    } else {
      dfs_rec(graph, child, visited, grey);
    }
  }
  grey[node] = false; // back track reset
  sorted.push(node);
  cout<<node<<' ';
}

void top_sort(al& graph, int n) {
  vector<bool> visited(n);
  vector<bool> grey(n);
  if (n == 0) return;
  dfs_rec(graph, 0, visited, grey);
}

// Below is comented but can be implemented with a top sort with weighted graph
/**
void shortest_path(al& graph, int source, int n) {
  sorted.clear();
  vector<bool> visited(n);
  vector<bool> grey(n);
  dfs_rec(graph, source, visited, grey);
  dist[source] = 0;
  while (sorted.size() > 0) {
    int node = sorted.top(); // The dist of this node is now accurate because all of the inedges have been evaluated
    for (int i=0; i<graph[node].size(); i++) {
      int child = graph[node][i].first;
      int weight = graph[node][i].second;
      dist[child] = min(dist[child], dist[node] + weight);
    }
    sorted.pop();
  }
}
**/

int main() {
  al dgraph;
  initialize_graph(dgraph, 6);
  add_edge_d(dgraph, 0, 1);
  add_edge_d(dgraph, 1, 2);
  add_edge_d(dgraph, 1, 3);
  add_edge_d(dgraph, 1, 4);
  add_edge_d(dgraph, 2, 5);
  top_sort(dgraph, 6);
  return 0;
}

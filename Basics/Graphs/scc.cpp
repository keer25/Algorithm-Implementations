# include <iostream>
# include <unordered_map>
# include <vector>
# include <stack>
using namespace std;
typedef unordered_map<int, vector<int> > al;

void initialize_graph(al& graph, int n) { // Graph with nodes from 0 to n-1 is a good generalization o.w have a mappign of the nodes to these indices
  for (int i=0; i<n; i++) {
    graph[i] = *(new vector<int>);
  }
}

void add_edge_d(al& graph, int u, int v) {
  graph[u].push_back(v);
}

void print_stack(stack<int>& scc, int node) {
  while (scc.top() != node) {
    cout<<scc.top()<<' ';
    scc.pop();
  }
  cout<<node<<'\n';
  scc.pop();
}

void scc_rec(al& graph, int node, vector<bool>& visited, vector<int>& dist, vector<int>& low, stack<int>& scc) {
  visited[node] = true;
  scc.push(node);
  low[node] = dist[node]; // Important! Initially it is just the node itself
//  dist[node] = dist[node] + 1;

  for (int i=0; i<graph[node].size(); i++) {
    int child = graph[node][i];
    if (visited[child]) { // First check if there are any back edges from the current node
      if (dist[child] != 0) low[node] = min(low[node], dist[child]);
    } else {
      dist[child] = dist[node] + 1;
      scc_rec(graph, child, visited, dist, low, scc);
      low[node] = min(low[node], low[child]); // See if there are any back edges from sub node
      dist[child] = 0; // Backtracking reset dist
    }
  }
  if (low[node] == dist[node]) {
    print_stack(scc, node);
  }
}

void find_scc(al& graph, int n) {
  vector<bool> visited(n);
  vector<int> dist(n);
  vector<int> low(n);
  stack<int> scc;
  for (int i=0; i<n; i++) {
    if (!visited[i]) {
      dist[i] = 1; // Imp! Set it to 1
      scc_rec(graph, i, visited, dist, low, scc);
    }
  }
}


int main() {
  al dgraph;
  initialize_graph(dgraph, 6);
  add_edge_d(dgraph, 0, 1);
  add_edge_d(dgraph, 1, 2);
  add_edge_d(dgraph, 2, 0);
  add_edge_d(dgraph, 1, 3);
  add_edge_d(dgraph, 1, 4);
  add_edge_d(dgraph, 2, 5);
  find_scc(dgraph, 6);
  return 0;
}

# include <iostream>
# include <unordered_map>
# include <queue>
# include <stack>
# include <vector>
using namespace std;
typedef unordered_map<int, vector<int> > al;

void initialize_graph(al& graph, int n) { // Graph with nodes from 0 to n-1 is a good generalization o.w have a mappign of the nodes to these indices
  for (int i=0; i<n; i++) {
    graph[i] = *(new vector<int>);
  }
}

void add_edge_u(al& graph, int u, int v) {
  graph[u].push_back(v);
  graph[v].push_back(u);
}

void add_edge_d(al& graph, int u, int v) {
  graph[u].push_back(v);
}

void print_stack_reverse(stack<int>& path) {
  vector<int> temp;
  while (path.size() > 0) {
    temp.push_back(path.top());
    path.pop();
  }
  for (int i = temp.size() - 1; i >= 0; i--) {
    cout<<temp[i]<<' ';
  }
  cout<<'\n';
}

bool path_rec(al& graph, int node, int n,stack<int>& path, vector<bool>& in_stack) {
  if (in_stack[node]) return false;
  path.push(node);
  in_stack[node] = true;
  if (path.size() == n) {
    print_stack_reverse(path);
    return true;
  }
  for (int i=0; i<graph[node].size(); i++) {
    int child = graph[node][i];
    if (path_rec(graph, child, n, path, in_stack)) return true;
  }
  path.pop();
  in_stack[node] = false;
  return false;
}

void hamiltonian_path(al& graph, int n) {
  stack<int> path;
  vector<bool> in_stack(n);
  if (!path_rec(graph, 0, n, path, in_stack)) {
    cout<<"No hamiltonian_path found!\n";
  }
}

void print_cycle(deque<int> cycle) {
  while (cycle.size() > 0) {
    cout<<cycle.back()<<' ';
    cycle.pop_back();
  }
  cout<<'\n';
}

bool cycle_rec(al& graph, int node, int n,deque<int>& path, vector<bool>& in_stack) {
  if (in_stack[node]) {
    if (path.size() == n && path.back() == node) {
      path.push_front(node);
      print_cycle(path);
      return true;
    }
    return false;
  }
  path.push_front(node);
  in_stack[node] = true;
  for (int i=0; i<graph[node].size(); i++) {
    int child = graph[node][i];
    if (cycle_rec(graph, child, n, path, in_stack)) return true;
  }
  path.pop_front();
  in_stack[node] = false;
  return false;
}

void hamiltonian_cycle(al& graph, int n) {
  deque<int> path;
  vector<bool> in_stack(n);
  if (!cycle_rec(graph, 0, n, path, in_stack)) {
    cout<<"No Hamiltonian cycle found!\n";
  }
}


int main() {
  al ugraph;
  al dgraph;
  initialize_graph(ugraph, 6);
  initialize_graph(dgraph, 6);

  add_edge_u(ugraph, 0, 1);
  add_edge_u(ugraph, 1, 2);
  add_edge_u(ugraph, 1, 3);
  add_edge_u(ugraph, 2, 0);
  add_edge_u(ugraph, 1, 4);
  add_edge_u(ugraph, 2, 5);

  add_edge_d(dgraph, 0, 1);
  add_edge_d(dgraph, 1, 2);
  add_edge_d(dgraph, 2, 0);
  add_edge_d(dgraph, 2, 3);
  add_edge_d(dgraph, 3, 5);
  add_edge_d(dgraph, 5, 4);
  add_edge_d(dgraph, 1, 3);
  add_edge_d(dgraph, 1, 4);
  add_edge_d(dgraph, 2, 5);
  add_edge_d(dgraph, 4, 0);

  hamiltonian_path(ugraph, 6);
  hamiltonian_path(dgraph, 6);
  hamiltonian_cycle(ugraph, 6);
  hamiltonian_cycle(dgraph, 6);
  return 0;
}

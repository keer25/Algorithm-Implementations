# include <iostream>
# include <unordered_map>
# include <queue>
# include <stack>
# include <vector>
using namespace std;
typedef unordered_map<int, vector<int> > al;
typedef vector<vector<int> > am;

void initialize_graph(al& graph, int n) { // Graph with nodes from 0 to n-1 is a good generalization o.w have a mappign of the nodes to these indices
  for (int i=0; i<n; i++) {
    graph[i] = *(new vector<int>);
  }
}

void initialize_graph(am& graph, int n) {
  graph.resize(n);
  for (int i=0; i<n; i++) {
    graph[i] = *(new vector<int>(n));
  }
}

void add_edge_u(am& graph, int u, int v) {
  graph[u][v] = 1;
  graph[v][u] = 1;
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


bool path_rec(al& graph, int node, deque<int>& cycle, bool destFound) {
  if (graph[node].size() == 0) {
    if (cycle.size() == 0) return true; // Means all edges are visited
    if (node == cycle.front()) { // When the path return backs to init node, when there are no out edges it can be thought of as a cycle back to itself with no intermeidate nodes
      cout<<cycle.front()<<' ';
      cycle.pop_front();
      return path_rec(graph, cycle.front(), cycle, destFound);
    } else {
      if (!destFound) {
        destFound = true;
        return path_rec(graph, cycle.front(), cycle, destFound); // Only extra piece of code for path, for the first iteration find a path from dource to dest which is the first node which runs out of edges. Then start the algo from source again
      }
      return false; // Means it is stuck so not an eulerian graph
    }
  } else {
    int next = graph[node].back();
    graph[node].pop_back();
    cycle.push_back(next);
    return path_rec(graph, next, cycle, destFound);
  }
}

void eulerian_path(al& graph, int source, int n) {
  al graphcopy;
  for (int i=0; i<n; i++) {
    graphcopy[i] = graph[i];
  }
  deque<int> cycle;
  cycle.push_back(0);
  if (!path_rec(graphcopy, source, cycle, false)) {
    cout<<"No eulerian path from source";
  }
  cout<<'\n';
}

void print_cycle(deque<int> cycle) {
  while (cycle.size() > 0) {
    cout<<cycle.back()<<' ';
    cycle.pop_back();
  }
  cout<<'\n';
}

bool cycle_rec(al& graph, int node, deque<int>& cycle) {
  if (graph[node].size() == 0) {
    if (cycle.size() == 0) return true;
    if (node == cycle.front()) {
      cout<<cycle.front()<<' ';
      cycle.pop_front();
      return cycle_rec(graph, cycle.front(), cycle);
    } else {
      return false;
    }
  } else {
    int next = graph[node].back();
    graph[node].pop_back();
    cycle.push_back(next);
    return cycle_rec(graph, next, cycle);
  }
}

// Undirected graph is a bit more complex because when u->v is visted v->u should also be marked vissited effieciently
// So better to use AM representation for undirected graph
void eulerian_cycle(al& graph, int n) {
  al graphcopy;
  for (int i=0; i<n; i++) {
    graphcopy[i] = graph[i];
  }
  if (n == 0) return;
  deque<int> cycle;
  cycle.push_back(0);
  if (!cycle_rec(graphcopy, 0, cycle)) {
    cout<<"Not an eulerian graph";
  }
  cout<<'\n';
}

bool cycle_rec(am& graph, int node, deque<int>& cycle) {
  while (graph[node].size() > 0) { // To find where the edge is
    if (graph[node].back() == 1) break;
    graph[node].pop_back();
  }
  if (graph[node].size() == 0) {
    if (cycle.size() == 0) return true;
    if (node == cycle.front()) {
      cout<<cycle.front()<<" ";
      cycle.pop_front();
      return cycle_rec(graph, cycle.front(), cycle);
    }
    return false;
  } else {
    int next = graph[node].size() - 1; // The back of the vector is 1 and the index of back is next
    graph[next][node] = 0; // Important! When edge is remove id UD graph both u->v and v->u is removed
    graph[node].pop_back();
    cycle.push_back(next);
    return cycle_rec(graph, next, cycle);
  }
}

void eulerian_cycle(am& graph, int n) {
  am graphcopy(n);
  for (int i=0; i<n; i++) {
    graphcopy[i] = graph[i];
  }
  if (n == 0) return;
  deque<int> cycle;
  cycle.push_back(0);
  if (!cycle_rec(graphcopy, 0, cycle)) {
    cout<<"Not an eulerian graph";
  }
  cout<<'\n';
}

int main() {
  am ugraph;
  al dgraph;
  al dgraph1;
  al dgraph2;
  initialize_graph(ugraph, 6);
  initialize_graph(dgraph, 6);
  initialize_graph(dgraph1, 3);
  initialize_graph(dgraph2, 3);

  add_edge_u(ugraph, 0, 1);
  add_edge_u(ugraph, 1, 2);
  add_edge_u(ugraph, 2, 3);
  add_edge_u(ugraph, 3, 4);
  add_edge_u(ugraph, 4, 5);
  add_edge_u(ugraph, 5, 0);

  add_edge_d(dgraph, 0, 1);
  add_edge_d(dgraph, 1, 2);
  add_edge_d(dgraph, 2, 3);
  add_edge_d(dgraph, 3, 4);
  add_edge_d(dgraph, 4, 5);
  add_edge_d(dgraph, 5, 0);
  add_edge_d(dgraph, 2, 3);
  add_edge_d(dgraph, 3, 4);
  add_edge_d(dgraph, 4, 2);

  add_edge_d(dgraph1, 0, 1);
  add_edge_d(dgraph1, 1, 2);

  add_edge_d(dgraph2, 0, 1);
  add_edge_d(dgraph2, 0, 2);

  eulerian_cycle(dgraph, 6);
  eulerian_path(dgraph1, 0, 3);
  eulerian_path(dgraph2, 0, 3);
  eulerian_cycle(ugraph, 6);
  return 0;
}

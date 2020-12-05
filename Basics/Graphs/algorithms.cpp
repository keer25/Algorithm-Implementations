# include <iostream>
# include <unordered_map>
# include <queue>
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

void print_graph(al& graph, int n) {
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      cout<<graph[i][j]<<' ';
    }
    cout<<'\n';
  }
  cout<<"\n\n";
}

void print_vec(vector<int>& vec) {
  for (int i=0; i<vec.size(); i++) {
    cout<<vec[i]<<' ';
  }
  cout<<'\n';
}

void bfs(al& graph, int n) { // Does not matter if directed or undirected algorithm is same
  queue<int> bfsq;
  vector<bool> visited(n);
  if (n == 0) return;
  //visited[0] = true;
  for (int i=0; i<n; i++) {
    if (!visited[i]) {
      bfsq.push(i);
      while (bfsq.size() > 0) {
        int node = bfsq.front ();
        cout<<node<<' ';
        bfsq.pop();
        for (int i=0; i<graph[node].size(); i++) {
          if (!visited[graph[node][i]]) {
            visited[graph[node][i]] = true;
            bfsq.push(graph[node][i]);
          }
        }
      }
    }
  }
  cout<<'\n';
}

void dfs_rec(al& graph, int node, vector<bool>& visited) {
  visited[node] = true;
  cout<<node<<' ';
  for (int i=0 ;i<graph[node].size(); i++) {
    if (!visited[graph[node][i]]) {
      dfs_rec(graph, graph[node][i], visited);
    }
  }
}

void dfs(al& graph, int n) {
    if (n == 0) return;
    vector<bool> visited(n);
    for (int i=0; i<n; i++) {
      if (!visited[i])
        //visited[node] = true;
        dfs_rec(graph, 0, visited);
    }
    cout<<'\n';
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
  add_edge_d(dgraph, 1, 3);
  add_edge_d(dgraph, 1, 4);
  add_edge_d(dgraph, 2, 5);

  bfs(ugraph, 6);
  dfs(ugraph, 6);
  bfs(dgraph, 6);
  dfs(dgraph, 6);
  return 0;
}

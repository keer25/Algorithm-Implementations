# include <iostream>
# include <unordered_map>
# include <vector>
# include <queue>
# include <utility>
using namespace std;
typedef unordered_map<int, vector<pair<int, int> > > al;
typedef pair<int, pair<int, int> > wedge;

struct cmp {
  bool operator()(wedge a, wedge b) const {
    return a.second.second > b.second.second;
  }
};

void initialize_graph(al& graph, int n) { // Graph with nodes from 0 to n-1 is a good generalization o.w have a mappign of the nodes to these indices
  for (int i=0; i<n; i++) {
    graph[i] = *(new vector<pair<int, int> >);
  }
}

void add_edge_u(al& graph, int u, int v, int weight) {
  graph[u].push_back(make_pair(v, weight)); // This convention can make it easier edge is  a pair (V, weight)
  graph[v].push_back(make_pair(u, weight));
}

void print_edge(wedge edge) {
  cout<<"( "<<edge.first<<", "<<edge.second.first<<" )   ";
}

void prim(al& graph, int n) {
  vector<bool> added(n);
  priority_queue<wedge, vector<wedge>, cmp> edges;
  if (n == 0) return;
  added[0] = true;
  for (int i=0; i<graph[0].size(); i++) {
    edges.push(make_pair(0, graph[0][i])); // First add all the edges of the u, (v, weiight)
  }
  while (edges.size() > 0) {
    if (!added[edges.top().second.first]) {
      int node = edges.top().second.first; // Take the to node in the edge if it is not already added
      print_edge(edges.top());
      added[node] = true; // Mark the node
      for (int i=0; i<graph[node].size(); i++) {
        edges.push(make_pair(node, graph[node][i])); //  Push all the edges of the node
      }
    }
    edges.pop();
  }
}

int main() {
  al ugraph;
  initialize_graph(ugraph, 6);

  add_edge_u(ugraph, 0, 1, 10);
  add_edge_u(ugraph, 1, 2, 1);
  add_edge_u(ugraph, 1, 3, 1);
  add_edge_u(ugraph, 2, 0, 1);
  add_edge_u(ugraph, 1, 4, 1);
  add_edge_u(ugraph, 2, 5, 1);
  prim(ugraph, 6);
  return 0;
}

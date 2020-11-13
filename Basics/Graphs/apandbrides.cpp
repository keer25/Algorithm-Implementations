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

void print_stack(stack<pair<int, int> >& bcc, int p) {
  if (bcc.size() == 0) return;
  cout<<"BCC ";
  while (bcc.top().first != p) {
    cout<<"( "<<bcc.top().first<<", "<<bcc.top().second<<" )  ";
    bcc.pop();
    if (bcc.size() == 0) break;
  }
  if (bcc.size() > 0) bcc.pop();
  cout<<'\n';
}

void add_edge_u(al& graph, int u, int v) {
  graph[u].push_back(v);
  graph[v].push_back(u);
}

void ap_rec(al& graph, int node, int parent, vector<bool>& visited, vector<int>& dist, vector<int>& low, stack<pair<int, int> >& bcc) {
  visited[node] = true;
  low[node] = dist[node]; // Important! Initially it is just the node itself
  bool isAp = false;
  int ccount = 0;

  for (int i=0; i<graph[node].size(); i++) {
    int child = graph[node][i];
    if (visited[child]) { // First check if there are any back edges from the current node
      if (dist[child] != 0 && dist[child] != (dist[node] - 1)) low[node] = min(low[node], dist[child]); // Make sure edge to parent node considered
    } else {
      bcc.push(make_pair(node, child));
      ccount++;
      dist[child] = dist[node] + 1;
      ap_rec(graph, child, node, visited, dist, low, bcc);
      low[node] = min(low[node], low[child]); // See if there are any back edges from sub node
      if (low[child] == dist[child]) {
        isAp = true;
        cout<<"( "<<node<<", "<<child<<" )\n";
      }
      dist[child] = 0; // Backtracking reset dist
    }
  }
  if (low[node] == dist[node]) {
    print_stack(bcc, parent); // Pass the parent node to exclude the bridge
  }
  if (isAp) cout<<node<<'\n';
  else if (parent == -1 && ccount > 1) cout<<node<<'\n'; // Special case for root node only for AP
}

void find_ap(al& graph, int n) {
  vector<bool> visited(n);
  vector<int> dist(n);
  vector<int> low(n);
  stack<pair<int, int> > bcc;
  for (int i=0; i<n; i++) {
    if (!visited[i]) {
      dist[i] = 1; // Imp! Set it to 1
      ap_rec(graph, i, -1, visited, dist, low, bcc);
    }
  }
}

int main() {
  al ugraph;
  initialize_graph(ugraph, 6);
  add_edge_u(ugraph, 0, 1);
  add_edge_u(ugraph, 1, 2);
  add_edge_u(ugraph, 1, 3);
  add_edge_u(ugraph, 2, 0);
  add_edge_u(ugraph, 1, 4);
  add_edge_u(ugraph, 2, 5);
  find_ap(ugraph, 6);
  return 0;
}

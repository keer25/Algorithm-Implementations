# include <iostream>
# include <unordered_map>
# include <queue>
# include <vector>
using namespace std;
typedef vector<vector<int> > am;

struct wedge {
  int v;
  int cap;
  int cost;
  wedge(int v, int cap, int cost) {
    this->v = v;
    this->cap = cap;
    this->cost = cost;
  }
};

typedef vector<vector<wedge> > al;

// initialize the adj matrices to represent indices of the edges for direct access, it is at graph[i][adjmat[i][j]]
void initialize_adjmat(am& adjmat, int n) {
  adjmat.resize(n);
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      adjmat[i].push_back(-1);
    }
  }
}

// add a directed edge from u to v with capacity and cost
void add_edge_d(al& graph, int u, int v, int cap, int cost) {
  graph[u].push_back(*(new wedge(v, cap, cost)));
}

void print_vec(vector<int>& vec) {
  for (int i=0; i<vec.size(); i++) {
    cout<<vec[i]<<' ';
  }
  cout<<'\n';
}

void print_graph(al& graph) {
  for (int i=0; i<graph.size(); i++) {
    for (int j=0; j<graph[i].size(); j++) {
      cout<<graph[i][j].v<<", "<<graph[i][j].cap<<"   ";
    }
    cout<<'\n';
  }
  cout<<'\n';
}

bool isinf(int num) {
  if (num == numeric_limits<int>::max()) return true;
  else return false;
}

// Popuates a parentarr for direct path and returns the min edge
int bellmanford_aug(al& graph, am& adjmat, int n, int s, int t, vector<int>& parentarr) {
  vector<vector<int> > parentmat(n);
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      parentmat[i].push_back(-1);
    }
  }
  int minedge = numeric_limits<int>::max();

  vector<int> dist(n, numeric_limits<int>::max());
  dist[s] = 0; // Essential!
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      for (int k=0; k<graph[j].size(); k++)
        if (!isinf(dist[j]) && graph[j][k].cap)
          if ((dist[j] + graph[j][k].cost) < dist[graph[j][k].v]) {
            parentmat[graph[j][k].v] = parentmat[j];
            parentmat[graph[j][k].v][graph[j][k].v] = j; // Add the current edge to parent arr
            dist[graph[j][k].v] = dist[j] + graph[j][k].cost; // Cost is used to determine dist between two nodes
          }

  if (isinf(dist[t])) return -1;

  int path = t;
  parentarr = parentmat[t];
  while (path != s) {
    int parent = parentarr[path];
    cout<<parent<<" -> "<<path<<'\n';
    minedge = min(minedge, graph[parent][adjmat[parent][path]].cap); // Findign the minedge
    path = parent;
  }
  return minedge;
}

int update_rgraph(al& rgraph, am& adjmat, int n, int s, int t, vector<int>& parentarr, int minedge) {
  int path = t;
  int cost = 0;
  while (path!= s) {
    int parent = parentarr[path];
    int edgecost = rgraph[parent][adjmat[parent][path]].cost;
    cost += minedge*edgecost;

    // Reduce cap of the flow
    rgraph[parent][adjmat[parent][path]].cap -= minedge;
    if (rgraph[parent][adjmat[parent][path]].cap == 0) {
      adjmat[parent][path] = -1;
    }

    // Add the negative the flow in reverse direction Hence adding capacity
    if (adjmat[path][parent] != -1) {
      rgraph[path][adjmat[path][parent]].cap += minedge;
    } else {
      rgraph[path].push_back(*(new wedge(parent, minedge, -1*edgecost))); // New edge created with the negative of edge cost
      adjmat[path][parent] = rgraph[path].size() - 1;
    }
    path = parent; // Propagating loop
  }
  return cost;
}

pair<int, int> find_max_flow(al& graph, int n, int s, int t) {
  al rgraph(n);
  am adjmat;
  initialize_adjmat(adjmat, n);
  for (int i=0; i<n; i++) {
    for (int j=0; j<graph[i].size(); j++) {
      rgraph[i].push_back(graph[i][j]);
      adjmat[i][graph[i][j].v] = j; // Reorecenting graoh with adj mat
    }
  }
  vector<int> parentarr(n);
  int flow = 0;
  int cost = 0;

  int minedge = bellmanford_aug(rgraph, adjmat, n, s, t, parentarr);
  while (minedge > 0) {
    flow += minedge;
    cost += update_rgraph(rgraph, adjmat, n, s, t, parentarr, minedge);
    print_graph(rgraph);
    parentarr.clear();
    minedge = bellmanford_aug(rgraph, adjmat, n, s, t, parentarr);
  }
  return make_pair(flow, cost);
}

// Partition is such that 1 belongs to left and 0 belongs to right
pair<int, int> find_matchings(al& graph, int n, vector<int>& partition) {
  al flowgraph(n+2);
  for (int i=0; i<n; i++) {
    if (partition[i] == 1) {
      flowgraph[0].push_back(*(new wedge(i+1, 1, 0)));
      flowgraph[i] = graph[i];
      for (int j=0; j<flowgraph[j].size(); j++)
        flowgraph[i][j].v += 1; // Adjusting for index diff but cap and cost remains same
    } else {
      flowgraph[i+1].push_back(*(new wedge(n+1, 1, 0)));
    }
  }
  return find_max_flow(flowgraph, n+2, 0, n+1);
}

int main() {
  al graph(7);

  add_edge_d(graph, 0, 5, 4, 1);
  add_edge_d(graph, 5, 1, 3, 1);
  add_edge_d(graph, 5, 3, 5, 10);
  add_edge_d(graph, 1, 2, 4, 1);
  add_edge_d(graph, 2, 6, 3, 1);
  add_edge_d(graph, 3, 4, 4, 10);
  add_edge_d(graph, 4, 6, 3, 10);

  pair<int, int> ans = find_max_flow(graph, 7, 0, 6);
  cout<<"Flow: "<<ans.first<<", Cost: "<<ans.second<<'\n';

  al bpgraph(6);
  vector<int> partition(6);
  add_edge_d(bpgraph, 0, 3, 1, 15);
  add_edge_d(bpgraph, 0, 4, 1, 10);
  add_edge_d(bpgraph, 0, 5, 1, 9);
  add_edge_d(bpgraph, 1, 3, 1, 9);
  add_edge_d(bpgraph, 1, 4, 1, 15);
  add_edge_d(bpgraph, 1, 5, 1, 10);
  add_edge_d(bpgraph, 2, 3, 1, 10);
  add_edge_d(bpgraph, 2, 4, 1, 12);
  add_edge_d(bpgraph, 2, 5, 1, 8);
  partition[0] = 1;
  partition[1] = 1;
  partition[2] = 1;
  ans = find_matchings(bpgraph, 6, partition);
  cout<<"Matching: "<<ans.first<<", Cost: "<<ans.second<<'\n';
}

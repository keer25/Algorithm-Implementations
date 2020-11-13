# include <iostream>
# include <unordered_map>
# include <queue>
# include <vector>
using namespace std;
typedef vector<vector<int> > al; // weighted edge

void initialize_graph(al& graph, int n) { // Graph with nodes from 0 to n-1 is a good generalization o.w have a mappign of the nodes to these indices
  graph.resize(n);
  for (int i=0; i<n; i++) {
    graph[i].resize(n);
  }
}

void add_edge_d(al& graph, int u, int v, int w) {
  graph[u][v] = w;
}

void add_edge_u(al& graph, int u, int v, int w) {
  graph[u][v] = w;
  graph[v][u] = w;
}

// Returns min edge and aug path in reverse order if found
// Alternately can get parent array by ref and only ret min flow
vector<int> bfs(al& graph, int n, int s, int t) {
  vector<int> ans;
  ans.push_back(-1); // Placeholder for min value
  vector<int> parent(n);
  queue<int> bfsq;
  // Parent of source will be set as -2, if not cisited -1
  for (int i=0; i<n; i++) parent[i] = -1;
  parent[s] = -2;
  bfsq.push(s);
  while (bfsq.size() > 0) {
    int node = bfsq.front();
    bfsq.pop();
    for (int i=0; i<n; i++) {
      if (parent[i] == -1 && graph[node][i]) {
        parent[i] = node;
        if (i == t) break;
        bfsq.push(i);
      }
    }
  }
  if (parent[t] != -1) {
    int path = t;
    ans.push_back(path);
    while (path != s) {
      ans.push_back(parent[path]);
      int weight = graph[parent[path]][path];
      if (ans[0] == -1 || weight < ans[0]) {
        ans[0] = weight;
      }
      path = parent[path];
    }
  } else {
    ans.pop_back(); // Returs vec of size zero if no aug path
  }
  return ans;
}

// finds s-t cut, all the nodes reachable from s form S other form T
void bfspartition(al& graph, int n, int s, vector<int>& partition) {
  queue<int> bfsq;
  partition[s] = 1;
  bfsq.push(s);
  while (bfsq.size() > 0) {
    int node = bfsq.front();
    bfsq.pop();
    for (int i=0; i<n; i++) {
      if (graph[node][i] && !partition[i]) {
        partition[i] = 1;
        bfsq.push(i);
      }
    }
  }
}

void print_vec(vector<int>& vec) {
  for (int i=0; i<vec.size(); i++) {
    cout<<vec[i]<<' ';
  }
  cout<<'\n';
}

int find_cut_capacity(al& graph, vector<int>& sourcecut, vector<int>& sinkcut) {
  int cutcapacity = 0;
  for (int i=0; i<sourcecut.size(); i++) {
    for (int j=0; j<sinkcut.size(); j++) {
        cutcapacity += graph[sourcecut[i]][sinkcut[j]];
    }
  }
  return cutcapacity;
}

void print_cut(al& graph, vector<int>& partition) {
  vector<int> sourcecut;
  vector<int> sinkcut;
  for (int i=0; i<partition.size(); i++) {
    if (partition[i] == 0) {
      sinkcut.push_back(i);
    } else {
      sourcecut.push_back(i);
    }
  }
  cout<<"Source Cut : ";
  print_vec(sourcecut);
  cout<<"Sink Cut : ";
  print_vec(sinkcut);
  cout<<"Cut Capacity"<<find_cut_capacity(graph, sourcecut, sinkcut)<<'\n';
}



int find_max_flow(al& graph, int n, int s, int t, al& rgraph) {
  initialize_graph(rgraph, n);
  vector<int> partition(n);// value 1 for s and 0 for t
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      rgraph[i][j] = graph[i][j];
    }
  }
  int flow = 0;
  vector<int> augpath = bfs(rgraph, n, s, t);
  while (augpath.size() > 0) {
    flow += augpath[0];
    for (int i= 2; i<augpath.size(); i++) {
      rgraph[augpath[i]][augpath[i-1]] -= augpath[0];
      rgraph[augpath[i-1]][augpath[i]] += augpath[0];
    }
    augpath = bfs(rgraph, n, s, t);
  }
  bfspartition(rgraph, n, s, partition);
  print_cut(graph, partition);
  return flow;
}

//Time Complextiy O(V^3E) but O(VE^2) is poss with adj matrix Space Complextiy O(V)
int find_max_flow(al& graph, int n, int s, int t) {
  al rgraph;
  return find_max_flow(graph, n, s, t, rgraph);
}

void print_matchings(vector<pair<int, int> >& matchings) {
  for (int i=0; i<matchings.size(); i++) {
    cout<<matchings[i].first<<" , "<<matchings[i].second<<'\n';
  }
}

int bipartite_matching(al& graph, int n, vector<int>& partition) {
  // We assume it is a uniform weighted graph
  // partition 1 for  source part and 0 for sink part
  al flowgraph;
  initialize_graph(flowgraph, n + 2);
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if (graph[i][j] && partition[i]) {
        flowgraph[i+1][j+1] = 1; // Adding a directed edge from source part to sink part
      }
    }
  }
  int s = 0;
  int t = n + 1;
  for (int i=0; i<n; i++) {
    if (partition[i]) {
      add_edge_d(flowgraph, s, i+1, 1);
    } else {
      add_edge_d(flowgraph, i+1, t, 1);
    }
  }
  al rgraph;
  int maxmatching = find_max_flow(flowgraph, n + 2, s, t, rgraph);
  vector<pair<int, int> > matchings;
  for (int i=1; i<n+1; i++) {
    for (int j=1; j<n+1; j++) {
      if (!rgraph[i][j] && flowgraph[i][j]) {
        matchings.push_back(make_pair(i-1, j-1));
      }
    }
  }
  print_matchings(matchings);
  return maxmatching;
}

int main() {
  al graph;
  initialize_graph(graph, 6);

  add_edge_d(graph, 0, 1, 16);
  add_edge_d(graph, 0, 2, 13);
  add_edge_d(graph, 1, 2, 10);
  add_edge_d(graph, 2, 1, 4);
  add_edge_d(graph, 1, 3, 12);
  add_edge_d(graph, 2, 4, 14);
  add_edge_d(graph, 3, 2, 9);
  add_edge_d(graph, 4, 3, 7);
  add_edge_d(graph, 3, 5, 20);
  add_edge_d(graph, 4, 5, 4);

  al bpgraph;
  initialize_graph(bpgraph, 7);
  add_edge_u(bpgraph, 0, 4, 1);
  add_edge_u(bpgraph, 1, 4, 1);
  add_edge_u(bpgraph, 2, 5, 1);
  add_edge_u(bpgraph, 3, 5, 1);
  add_edge_u(bpgraph, 3, 6, 1);
  vector<int> partition(7);
  partition[0] = 1;
  partition[1] = 1;
  partition[2] = 1;
  partition[3] = 1;

  cout<<find_max_flow(graph, 6, 0, 5)<<'\n';
  cout<<bipartite_matching(bpgraph, 7, partition);
}

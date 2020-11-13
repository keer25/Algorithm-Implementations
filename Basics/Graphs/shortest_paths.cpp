# include <iostream>
# include <unordered_map>
# include <vector>
# include <queue>
# include <utility>
using namespace std;
typedef unordered_map<int, vector<pair<int, int> > > al;
typedef pair<int, pair<int, int> > wedge;

void initialize_graph(al& graph, int n) { // Graph with nodes from 0 to n-1 is a good generalization o.w have a mappign of the nodes to these indices
  for (int i=0; i<n; i++) {
    graph[i] = *(new vector<pair<int, int> >);
  }
}

void add_edge_u(al& graph, int u, int v, int weight) {
  graph[u].push_back(make_pair(v, weight)); // This convention can make it easier edge is  a pair (V, weight)
  graph[v].push_back(make_pair(u, weight));
}

void print_dist(vector<int>& dist) {
  for (int i=0; i<dist.size(); i++) {
    cout<<i<<" : "<<dist[i]<<'\n';
  }
}


// Complextiy O(V + E) and space O(V)
void zobfs(al& graph, int source, int n) {
  vector<int> dist(n);
  for (int i=0; i<n; i++) {
    dist[i] = numeric_limits<int>::max();
  }
  deque<int> bfsq;
  vector<bool> processed(n);
  dist[source] = 0;
  bfsq.push_back(source);

  while (bfsq.size() > 0) {
    int node = bfsq.front();
    bfsq.pop_front();
    if (!processed[node]) {
    processed[node] = true;
      for (int i=0; i<graph[node].size(); i++) {
        int child = graph[node][i].first;
        int weight = graph[node][i].second;
        if (weight == 0) {
          bfsq.push_front(child);
          dist[child] = min(dist[child], dist[node]);
        }
        else {
          bfsq.push_back(child);
          dist[child] = min(dist[child], dist[node] + 1);
        }
      }
    }
  }
  print_dist(dist);
}

void bellmanford(al& graph, int source, int n) {
  int times = n - 1;
  vector<int> dist(n);
  for (int i=0; i<n; i++) {
    dist[i] = numeric_limits<int>::max();
  }
  dist[source] = 0;
  while (times > 0) {
    for (int i=0; i<n; i++) {
      for (int j=0; j<graph[i].size(); j++) {
        int node = graph[i][j].first;
        int weight = graph[i][j].second;
        dist[node] = min((long)dist[node], ((long)weight) + ((long)dist[i]));
      }
    }
    times--;
  }
  print_dist(dist);
}

struct cmp {
  bool operator()(pair<int, int> a, pair<int, int> b) {
    return a.second > b.second;
  }
};

void dijkstra(al& graph, int source, int n) {
  priority_queue<pair<int, int>, vector<pair<int, int> >, cmp> dijq;
  vector<int> dist(n);
  vector<bool> processed(n);
  for (int i=0; i<n; i++) {
    dist[i] = numeric_limits<int>::max();
  }
  dist[source] = 0;
  dijq.push(make_pair(source, 0));

  while (dijq.size() > 0) {
    int val = dijq.top().first;
    dijq.pop();
    if (!processed[val]) {
      for (int i=0; i<graph[val].size(); i++) {
        int child = graph[val][i].first;
        int weight = graph[val][i].second;
        int temp = min(dist[child], dist[val] + weight);
        if (dist[child] > temp) {
          dijq.push(make_pair(child, temp));
          dist[child] = temp;
        }
      }
      processed[val] = true;
    }
  }
  print_dist(dist);
}

void floyd_warshal(al& graph, int n) {
  vector<vector<int> > dist(n);
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      dist[i].push_back(numeric_limits<int>::max());
    }
  }
  for (int i=0; i<n; i++) {
    dist[i][i] = 0;
    for (int j=0; j<graph[i].size(); j++) {
      dist[i][graph[i][j].first] = graph[i][j].second;
    }
  }
  for (int k=0; k<n; k++)
    for (int i=0; i<n; i++)
      for (int j=0; j<n; j++)
        dist[i][j] = min((long)dist[i][j], (long)dist[i][k] + (long)dist[k][j]);
  print_dist(dist[0]);
}

int main() {
  al zgraph;
  al ugraph;
  initialize_graph(zgraph, 6);
  initialize_graph(ugraph, 6);

  add_edge_u(zgraph, 0, 1, 0);
  add_edge_u(zgraph, 1, 2, 1);
  add_edge_u(zgraph, 1, 3, 0);
  add_edge_u(zgraph, 2, 0, 1);
  add_edge_u(zgraph, 1, 4, 1);
  add_edge_u(zgraph, 2, 5, 1);

  add_edge_u(ugraph, 0, 1, 10);
  add_edge_u(ugraph, 1, 2, 1);
  add_edge_u(ugraph, 1, 3, 1);
  add_edge_u(ugraph, 2, 0, 1);
  add_edge_u(ugraph, 1, 4, 1);
  add_edge_u(ugraph, 2, 5, 1);

  zobfs(zgraph, 0, 6);
  bellmanford(zgraph, 0, 6);
  bellmanford(ugraph, 0, 6);
  dijkstra(ugraph, 0, 6);
  floyd_warshal(ugraph, 6);

  return 0;
}

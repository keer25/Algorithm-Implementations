# include <iostream>
# include <vector>
# include <unordered_map>
using namespace std;
typedef vector<vector<int> > am;
typedef unordered_map<int, pair<int, int> > nltype;

void initialize_graph(am& graph, int n) {
  graph.resize(n);
  for (int i=0; i<n; i++) {
    graph[i].resize(n);
  }
}

void add_edge_d(am& graph, int u, int v, int w) {
  graph[u][v] = w;
}

void print_vec(vector<int>& vec) {
  for (int i=0; i<vec.size(); i++) {
    cout<<vec[i]<<' ';
  }
  cout<<'\n';
}

void print_graph(am& graph) {
  for (int i=0; i<graph.size(); i++) {
    for (int j=0; j<graph.size(); j++) {
      cout<<graph[i][j]<<" ";
    }
    cout<<'\n';
  }
  cout<<'\n';
}

void appends(int x, am& graph, int n, vector<int>& starr, nltype& nlmap, vector<int>& l) {
  starr[x] = 1;
  for (int i=0; i<n; i++) {
    if (graph[x][i] && starr[i] != 2) {
      int diff = graph[x][i] - (l[x] + l[i]);
      if (nlmap.find(i) != nlmap.end()) {
        if (diff < nlmap[i].first) {
          nlmap[i].first = diff;
          nlmap[i].second = x;
        }
      } else {
        nlmap[i] = make_pair(diff, x);
      }
    }
  }
}

void appendt(int y, vector<int>& starr, nltype& nlmap) {
  starr[y] = 2;
  nlmap.erase(y);
}

void augmentmatchings(int head, int tail, vector<int>& parentarr, vector<int>& matchesarr) {
  int path = tail;
  while (path != -1) {
    matchesarr[path] = parentarr[path];
    matchesarr[parentarr[path]] = path;
    if (parentarr[path] == head) break;
    path = parentarr[parentarr[path]]; // Skip two
  }
}



// partition 1 is taken as x and other as y
// O(V^3) algorithm for assignment (min cost max matching) problem
// Works with unbalanced assignment but |X| < |Y|
pair<int, int> hungarian(am& graph, int n, vector<int>& partition) {// graph[i][j] = 0 if no edge ow. w of edge i->j
  int maxmatchings = 0;
  int nx = 0;
  int ny = 0;
  int x;
  int nmatchings = 0;
  vector<int> matchesarr(n, -1); // Will be representing edges y->x or x->y which are in M
  vector<int> l(n);
  nltype nlmap;
  vector<int> starr(n); // s ->1, t->2, ow->0
  vector<int> parentarr(n, -1);
  int cost = 0;
  // Given the DS for tracking all this, algorithm will be easy to write

  print_graph(graph);
  // Initialize labellings
  for (int i=0; i<n; i++) {
    if (partition[i]) {
      nx++;
      l[i] = -1;
      for (int j=0; j<n; j++)
        if (graph[i][j])
          if (l[i] == -1) l[i] = graph[i][j];
          else l[i] = min(graph[i][j], l[i]);
    }  else {//ow. l[i] = 0
      ny++;
    }
  }
  maxmatchings = min(nx, ny);
  cout<<"nx: "<<nx<<", ny: "<<ny<<'\n';
  cout<<"Added Labellings";
  print_vec(l);

  while (nmatchings < maxmatchings) {
    //Pick free vertex from X
    for (int i=0; i<n; i++) {
      if (partition[i] && (matchesarr[i] == -1)) {
        appends(i, graph, n, starr, nlmap, l);
        x = i; // Used as head for the alternating tree
        break;
      }
    }
    cout<<"Picked Vertex\n";
    print_vec(starr);

    bool augmented = false;
    while (!augmented) {
      int delta = -1;
      for (int i=0; i<n; i++) {
        if (nlmap.find(i) != nlmap.end()) { // To compute delta is NL_l - T is bull
          if (delta == -1) delta = nlmap[i].first;
          else delta = min(delta, nlmap[i].first);
        }
        if ((nlmap.find(i) != nlmap.end()) && (nlmap[i].first == 0)) {
          parentarr[i] = nlmap[i].second; // Extend AT
          cout<<"Added x->y to AT\n";
          print_vec(parentarr);
          if (matchesarr[i] == -1) {
            augmentmatchings(x, i, parentarr, matchesarr);
            cout<<"augmented matchings\n";
            print_vec(matchesarr);
            nmatchings++;
            augmented = true;
            fill(starr.begin(), starr.end(), 0); // Clear S and T
            nlmap.clear(); // Hence clear NL(S)
            fill(parentarr.begin(), parentarr.end(), -1); // Clear AT
          } else {
            parentarr[matchesarr[i]] = i;
            appends(matchesarr[i], graph, n, starr, nlmap, l);
            appendt(i, starr, nlmap);
            cout<<"Added y->x to AT\n";
            print_vec(parentarr);
          }
          break;
        }
      }
      if (delta != 0) { // Means no y in NL_l - T, so enhance labels
        for (int i=0; i<n; i++) {
          if (starr[i] == 1) l[i] += delta;
          else if (starr[i] == 2) l[i] -= delta;
        }
        for (auto it = nlmap.begin(); it != nlmap.end(); it++) {
        // Update nlmap as for all x belongs to S l += delta, while for y \notin T we have l -= delta
          it->second.first += delta;
        }
      }
    }
  }
  for (int i=0; i<n; i++) { // Calculating cost
    if (partition[i]) {
      cost += graph[i][matchesarr[i]];
    }
  }
  return make_pair(nmatchings, cost);
}

int main() {
  am bpgraph;
  initialize_graph(bpgraph, 6);
  pair<int, int> ans;
  vector<int> partition(6);
  add_edge_d(bpgraph, 0, 3, 15);
  add_edge_d(bpgraph, 0, 4, 10);
  add_edge_d(bpgraph, 0, 5, 9);
  add_edge_d(bpgraph, 1, 3, 9);
  add_edge_d(bpgraph, 1, 4, 15);
  add_edge_d(bpgraph, 1, 5, 10);
  add_edge_d(bpgraph, 2, 3, 10);
  add_edge_d(bpgraph, 2, 4, 12);
  add_edge_d(bpgraph, 2, 5, 8);
  partition[0] = 1;
  partition[1] = 1;
  partition[2] = 1;
  cout<<"Starting\n";
  ans = hungarian(bpgraph, 6, partition);
  cout<<"Matching: "<<ans.first<<", Cost: "<<ans.second<<'\n';

  am ubpgraph;
  initialize_graph(ubpgraph, 5);
  vector<int> partition1(5);
  add_edge_d(ubpgraph, 3, 0, 15);
  add_edge_d(ubpgraph, 4, 0, 10);
  add_edge_d(ubpgraph, 4, 1, 15);
  add_edge_d(ubpgraph, 3, 2, 10);
  add_edge_d(ubpgraph, 4, 2, 12);
  partition1[4] = 1;
  partition1[3] = 1;
  cout<<"Starting\n";
  ans = hungarian(ubpgraph, 5, partition1);
  cout<<"Matching: "<<ans.first<<", Cost: "<<ans.second<<'\n';

  return 0;
}

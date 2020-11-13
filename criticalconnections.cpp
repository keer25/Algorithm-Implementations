class Solution {
public:
    vector<bool> visited;
    vector<bool> path;
    vector<bool> critical;
    vector<bool> be;
    vector<vector<int>> alist;
    vector<int> minbe;
    vector<int> disc;

    int getminbe(int a, int b) {
        if (a == -1) return b;
        else return min(a, b);
    }

    void dfsprocess(int node) {
        int nc = 0;
        path[node] = true;
        visited[node] = true;
        //if (alist[node].size() == 0) critical[node] = false;
        int gbmin = -1;
        for (int i=0; i<alist[node].size(); i++) {
            int proc = alist[node][i];
            if (path[proc]) {
                //critical[node] = false;
                if (disc[proc] != disc[node] - 1)
                         minbe[node] = getminbe(minbe[node], disc[proc]);
                    }
            if (!visited[proc]) {
                nc++;
                disc[proc] = disc[node] + 1;
                dfsprocess(proc);
                if (minbe[proc] != -1) {

                    if (minbe[proc] > disc[node]) {
                        critical[node] = true;
                    }
                    minbe[node] = getminbe(minbe[node], disc[minbe[proc]]);
                } else {
                    critical[node] = true;
                }
            }
        }
        // if (minbe[node] > disc[node]) {
        //     critical[node] = true;
        // }
       // for (int i=0; i<alist[node].size(); i++) {
        // int proc = alist[node][i];
     //   if (path[proc]) {
                //critical[node] = false;
   //             minbe[node] = getminbe(minbe[node], disc[proc]);
    //    }
      //  }
        if (nc < 2 && disc[node] == 0) critical[node] = false;
        path[node] = false;
    }

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> ans;
        for (int i=0; i<n; i++) {
            visited.push_back(false);
            path.push_back(false);
            critical.push_back(false);
            be.push_back(false);
            minbe.push_back(-1);
            disc.push_back(-1);
        }
        alist.resize(n);
        for (int i=0; i<connections.size(); i++) {
            alist[connections[i][0]].push_back(connections[i][1]);
            alist[connections[i][1]].push_back(connections[i][0]);
        }
        for (int i=0; i<n; i++) {
            if (visited[i] == false) {
                disc[i] = 0;
                dfsprocess(i);
                vector<int> anss;
            for (int i=0; i<n; i++) {
                if (critical[i]) {
                    anss.push_back(i);
                }
            }
            if (anss.size() > 0) {
                ans.push_back(anss);
            }
            }
        }
        return ans;
    }
};

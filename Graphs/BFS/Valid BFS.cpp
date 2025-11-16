// In my first approch I was only checking that in each level i should have desired nodes i was not checking the order of the nodes 
// which was wrong assume that in level 0 ---> 1
// and its child are level 1 ---> 2, 3
// than according to valid bfs in level 2 the childrens of 2 should come first than the child of 3 

// IN THIS EVERTHING IS CORRECT BECAUSE I WAS CHECKING EACH NODE NOT ALL LEVEL NODE 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
public: 
     vector<bool> vis;
     int n;

     Solution(int nodes) : n(nodes), vis(nodes + 1, false) {}

     bool bfs(int n, unordered_map<int, vector<int>>& adj, vector<int>& sequence) {
          // start BFS from 1
          if(sequence[0] != 1) return false;
          queue<int> q;
          vis[1] = true;
          q.push(1);
          int idx = 1; // sequence index

          while(!q.empty()) {
               int parent = q.front(); q.pop();
               unordered_set<int> expected;
               for(int nbr : adj[parent]) {
                    if(!vis[nbr]) expected.insert(nbr);
               }
               int cnt = expected.size();
               
               for(int i = idx; i < idx + cnt; ++i) {
                    if(expected.find(sequence[i]) == expected.end()) {
                         return false;
                    }
                    vis[sequence[i]] = true;
                    q.push(sequence[i]);  // KYUKI HAME GIVEN ORDER CHECK KARNA HAI JO HAME SEQ DI HAI 
               }
               idx += cnt;
          }
          return idx == n;
     }
     };

     int main() {
     int n;
     cin >> n;
     unordered_map<int, vector<int>> adj;
     for(int i = 0; i < n - 1; i++) {
          int u, v;
          cin >> u >> v;
          adj[u].push_back(v);
          adj[v].push_back(u);
     }
     vector<int> sequence(n);
     for(int i = 0; i < n; i++) {
          cin >> sequence[i];
     }

     Solution obj(n);
     bool result = obj.bfs(n, adj, sequence);
     cout << (result ? "Yes" : "No") << endl;
     return 0;
}

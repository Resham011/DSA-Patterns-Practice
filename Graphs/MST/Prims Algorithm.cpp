// Goal: Find Minimum Spanning Tree (connect all nodes with minimum total edge weight)
// Approach: Grow MST from one vertex, always adding cheapest edge to unvisited node
// Steps:

// Start at any vertex, mark visited
// Add all its edges to min-heap
// Pop cheapest edge from heap
// If leads to unvisited node → add edge to MST, mark node visited, add its edges to heap
// Repeat until all nodes visited

// Implementation:

// Use min-heap storing: {edge_weight, node, parent}
// Track visited nodes with boolean array
// Build adjacency list from edges

// Key Point: Push only individual edge weight (nbr_wt), NOT cumulative (wt + nbr_wt)
// Time: O(E log V) with binary heap
// Space: O(V + E)
// When to use: Dense graphs (many edges), need MST
// vs Kruskal's: Prim's grows from one point; Kruskal's sorts all edges globally

class Solution {
     public:
     int spanningTree(int V, vector<vector<int>>& edges) {
          int ans = 0;
          priority_queue< vector<int>, vector<vector<int>>, greater<vector<int>> > pq;
          vector<int> parent(V);
          vector<int> vis(V);
          
          unordered_map<int, vector<pair<int, int>>> adj;
          
          for(auto& edge : edges){
               adj[edge[0]].push_back({edge[1], edge[2]});
               adj[edge[1]].push_back({edge[0], edge[2]});
          }
          
          pq.push({0, 0, -1});
          while(!pq.empty()){
               auto edge = pq.top();
               pq.pop();
               
               int wt = edge[0];
               int node = edge[1];
               int p = edge[2];
               
               
               if(vis[node] == false){
                    vis[node] = true;
                    parent[node] = p;
                    ans += wt;
               }
               
               for(auto& vec : adj[node]){
                    int nbr = vec.first;
                    int nbr_wt = vec.second;
                    
                    if(vis[nbr] == false){
                         pq.push({nbr_wt, nbr, node});
                    }
               }
          }
          return ans;
     }
};
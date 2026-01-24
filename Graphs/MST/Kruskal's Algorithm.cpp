// whta is MST?
// connect the V vertex in the graph with no cycle such that it have minimum sum of all the edges 
// no cycle, connected, V - 1 edges in MST 
// Algorithms for finding MST = kruskal's, Prim's 

// whta is kruskal's algo?
// sort all the edges in ascending order 
// assume all the vertex are disconnected / diferent components at first (SING DSU WE WILL FIND VERTEX ARE IN SAME OR DIFFERRNT COMPONENT)
// using edges try to connect the vertex if they are in different component and do not create cycle
// when all the vertex are in one component and have V - 1 edges MST is obtained.

// How to identify MST problems:

// Keywords: "minimum cost to connect", "least expense to link all", "cheapest network"
// Structure: Graph/network with weighted edges where you need to connect all nodes
// Goal: Connect everything with minimum total weight/cost
// No cycles needed: You don't need multiple paths between nodes

// Common scenarios:
// Connecting cities with roads/cables at minimum cost
// Network design problems
// Clustering with minimum distance

// Red flag it's NOT MST: If you need shortest path between two specific points (that's Dijkstra/BFS) or need to visit all nodes and return (that's TSP)

// Kruskal's Algorithm Time Complexity:
// O(E log E) or equivalently O(E log V)
// Breakdown:

// Sorting edges: O(E log E) — dominates the complexity
// Union-Find operations: O(E α(V)) — nearly constant with path compression
// Overall: O(E log E)

class Solution
{
          public:
     //DSU Code
     vector<int> parent;
     vector<int> rank;
     
     int find (int x) {
          if (x == parent[x]) 
               return x;
     
          return parent[x] = find(parent[x]);
     }
     
     void Union (int x, int y) {
          int x_parent = find(x);
          int y_parent = find(y);
     
          if (x_parent == y_parent) 
               return;
     
          if(rank[x_parent] > rank[y_parent]) {
               parent[y_parent] = x_parent;
          } else if(rank[x_parent] < rank[y_parent]) {
               parent[x_parent] = y_parent;
          } else {
               parent[x_parent] = y_parent;
               rank[y_parent]++;
          }
     }
     
     int Kruskal(vector<vector<int>> &vec) {

          int sum = 0;
          for(auto &temp : vec) {
               
               int u = temp[0];
               int v = temp[1];
               int wt = temp[2];
               
               int parent_u = find(u);
               int parent_v = find(v);
               
               if(parent_u != parent_v) {
                    Union(u, v);
                    sum += wt;
               }
               
          }

          //if(edgesConnexted != V-1) 
          //"It's not a MST" - REMEMBER THIS ALWAYS if anyone asks you how to check if we formed an MST or not

          
          return sum;
     }
     
     int spanningTree(int V, vector<vector<int>> adj[]) {
          
          parent.resize(V);
          rank.resize(V, 0);
               
          for(int i = 0; i<V; i++)
               parent[i] = i;

          vector<vector<int>> vec;
          
          
          for(int i = 0; i<V; i++) {
               
               for(auto &temp : adj[i]) {
                    
                    int u = i;
                    int v = temp[0];
                    int d = temp[1];

                    vec.push_back({u, v, d});
                    
               }
               
          }
          
          
          auto lambda = [&](auto &v1, auto &v2) {
               return v1[2] < v2[2];
          };
          
          sort(begin(vec), end(vec), lambda);
          
          return Kruskal(vec);
          
     }
};
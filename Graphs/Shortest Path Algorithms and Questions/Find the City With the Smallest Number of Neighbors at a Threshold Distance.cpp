//Approach (Using Dijkstra's)
//T.C : O(V * ElogV) where E is the number of edges and V = number of vertices. We call Dijkstra's for each vertex.
        //In worst case , max edges = V*(V-1)/2
        //O(V * V*(V-1)/2 * log V)
        //Which is approximately equal to O(V^3 * log V)
//S.C : O(V^2)
class Solution {
public:
     #define P pair<int, int>
     void dijkastra(int node, vector<vector<int>>& ans, unordered_map<int, vector<pair<int,int>>>& adj){
          priority_queue<P, vector<P>, greater<P>> pq;
          pq.push({0, node});
          ans[node][node] = 0;

          while(!pq.empty()){
               int dist = pq.top().first;
               int topNode = pq.top().second;
               pq.pop();

               for(auto& p : adj[topNode]){
                    int nbr = p.first;
                    int nbr_dist = p.second;

                    if(ans[node][nbr] > dist + nbr_dist){ // Use ans[node][nbr] not ans[topNode][nbr] because we are calculation shortest distane fron node to nbr not topNode 
                         ans[node][nbr] = dist + nbr_dist;
                         pq.push({ans[node][nbr], nbr});
                    }
               }
          }
     }

     int cityWithSmallestNumberOfNbr(vector<vector<int>>& ans, int& distanceThreshold, int& n){
          int minNbrNumber = INT_MAX;
          int maxNode = -1;
          int node;
          for(node = 0; node < n; node++){
               int currValidNbr =0;
               for(int nbr = 0; nbr < n; nbr++){
                    if(node != nbr && ans[node][nbr] <= distanceThreshold) currValidNbr++;
               }
               if(currValidNbr <= minNbrNumber){
                    minNbrNumber = currValidNbr;
                    maxNode = node;
               }
          }
          return maxNode;
     }
     int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
          unordered_map<int, vector<pair<int,int>>> adj;

          for(auto& edge : edges){
               int u = edge[0];
               int v = edge[1];
               int wt = edge[2];

               adj[u].push_back({v, wt});
               adj[v].push_back({u, wt});
          }

          vector<vector<int>> ans(n, vector<int>(n, INT_MAX));
          for (int i = 0; i < n; i++) {
               ans[i][i] = 0;  // Distance to itself is zero
          }
          for(int i = 0; i < n; i++){
               dijkastra(i, ans, adj);
          }
          return cityWithSmallestNumberOfNbr(ans, distanceThreshold, n);
     }
};


//Approach (Using Bellman-Ford)
//T.C : O(V * (V * E)) where E is the number of edges and V = number of vertices. We call Bellman(V*E) for each vertex.
        //In worst case , max edges = V*(V-1)/2
        //O(V * V*(V-1)/2 * log V)
        //Which is approximately equal to O(V^4)
//S.C : O(V^2)
class Solution {
public:
     #define P pair<int, int>

     void bellmanFord(int n, vector<vector<int>>& edges, vector<int>& shortestPathDistances, int source) {
          fill(shortestPathDistances.begin(), shortestPathDistances.end(), INT_MAX);
          shortestPathDistances[source] = 0;

          for (int i = 1; i < n; i++) {
               for (const auto& edge : edges) {
                    int u  = edge[0];
                    int v  = edge[1];
                    int wt = edge[2];
                    if (shortestPathDistances[u] != INT_MAX &&
                         shortestPathDistances[u] + wt < shortestPathDistances[v]) {
                         shortestPathDistances[v] = shortestPathDistances[u] + wt;
                    }
                    //bi-directional edge
                    if (shortestPathDistances[v] != INT_MAX &&
                         shortestPathDistances[v] + wt < shortestPathDistances[u]) {
                         shortestPathDistances[u] = shortestPathDistances[v] + wt;
                    }
               }
          }
     }

     int getCityWithFewestReachable(int n, const vector<vector<int>>& shortestPathMatrix, int distanceThreshold) {
          int cityWithFewestReachable = -1;
          int fewestReachableCount = INT_MAX;

          for (int i = 0; i < n; i++) {
               int reachableCount = 0;
               for (int j = 0; j < n; j++) {
                    if (i != j && shortestPathMatrix[i][j] <= distanceThreshold) {
                         reachableCount++;
                    }
               }

               if (reachableCount <= fewestReachableCount) {
                    fewestReachableCount = reachableCount;
                    cityWithFewestReachable = i;
               }
          }
          return cityWithFewestReachable;
     }

     int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
          vector<vector<int>> shortestPathMatrix(n, vector<int>(n, INT_MAX));

          for (int i = 0; i < n; i++) {
               shortestPathMatrix[i][i] = 0;  // Distance to itself is zero
          }

          for (const auto& edge : edges) {
               int u = edge[0];
               int v = edge[1];
               int wt = edge[2];
               shortestPathMatrix[u][v] = wt;
               shortestPathMatrix[v][u] = wt;
          }

          // Compute shortest paths from each city using Dijkstra's algorithm
          for (int i = 0; i < n; i++) {
               bellmanFord(n, edges, shortestPathMatrix[i], i);
          }

          return getCityWithFewestReachable(n, shortestPathMatrix, distanceThreshold);
     }
};


//Approach (Using Dijkstra's)
//T.C : O(V^3)
//S.C : O(V^2)
class Solution {
public:
     #define P pair<int, int>
     void floydWarshall(int n, vector<vector<int>>& shortestPathMatrix) {
          
          for(int via = 0; via < n; via++) {
               
               for(int i = 0; i<n; i++) {
                    for(int j = 0; j<n; j++) {
                         
                    shortestPathMatrix[i][j] = min(shortestPathMatrix[i][j],
                                                       shortestPathMatrix[i][via] + shortestPathMatrix[via][j]);
                         
                    }
               }
          }
     }

     int getCityWithFewestReachable(int n, const vector<vector<int>>& shortestPathMatrix, int distanceThreshold) {
          int cityWithFewestReachable = -1;
          int fewestReachableCount = INT_MAX;

          for (int i = 0; i < n; i++) {
               int reachableCount = 0;
               for (int j = 0; j < n; j++) {
                    if (i != j && shortestPathMatrix[i][j] <= distanceThreshold) {
                         reachableCount++;
                    }
               }

               if (reachableCount <= fewestReachableCount) {
                    fewestReachableCount = reachableCount;
                    cityWithFewestReachable = i;
               }
          }
          return cityWithFewestReachable;
     }

     int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
          vector<vector<int>> shortestPathMatrix(n, vector<int>(n, 1e9+7));

          for (int i = 0; i < n; i++) {
               shortestPathMatrix[i][i] = 0;  // Distance to itself is zero
          }

          for (const auto& edge : edges) {
               int u = edge[0];
               int v = edge[1];
               int wt = edge[2];
               shortestPathMatrix[u][v] = wt;
               shortestPathMatrix[v][u] = wt;
          }

          floydWarshall(n, shortestPathMatrix);

          return getCityWithFewestReachable(n, shortestPathMatrix, distanceThreshold);
     }
};

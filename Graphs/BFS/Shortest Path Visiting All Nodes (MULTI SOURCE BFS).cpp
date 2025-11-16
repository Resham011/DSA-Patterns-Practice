class Solution {
public:
    
     int setMask(int mask, int bit){
          int newMask = (mask | (1 << bit));
          return  newMask; 
     }
     int shortestPathLength(vector<vector<int>>& graph) {
          int n = graph.size();
          
          unordered_map<int, vector<int>> adj;
          set<pair<int, int>> st;
          queue<pair<int, int>> q;

          for(int u = 0; u < n; u++){
               for(auto v : graph[u]){
                    adj[u].push_back(v);
               }
          }

          for(int i = 0; i < n - 1; i++){
               int mask = setMask(0, i);
               q.push({i, mask});
               st.insert({i, mask});
          }
          
          int len = 0;    
          while(!q.empty()){
               int size = q.size();
               while(size--){
                    auto front = q.front();
                    q.pop();
                    int node = front.first;
                    int mask = front.second;

                    // if(mask == (pow(2, n) - 1)) return len;
                    if(mask == (1 << n) - 1) return len;
                    for(auto& nbr : adj[node]){
                         int newMask = setMask(mask, nbr);
                         if(st.find({nbr, newMask}) == st.end()){
                         q.push({nbr, newMask});
                         st.insert({nbr, newMask});
                         }
                    }
               }
               len++;
          }
          return len;
     }
};




// 1. **Current Node:** The node where you are standing.
// 2. **Visited Mask:** A bitmask showing which nodes have been visited.



// ### Example with  n = 3:

// Nodes: 0, 1, 2

// - Possible bitmask values (3 bits):  
//   000 (none visited)  
//   001 (only node 0 visited)  
//   010 (only node 1 visited)  
//   011 (nodes 0 and 1 visited)  
//   100 (only node 2 visited)  
//   101 (nodes 0 and 2 visited)  
//   110 (nodes 1 and 2 visited)  
//   111 (all nodes visited)  
// - Total bitmask values: \( 2^3 = 8 \).

// For each of the 3 nodes, you can have any of these 8 visited masks:

// So for n nodes we will be having (n * 2 ^ n ) possible combinations 
// ---

// ### Summary Table

// | Current Node | Visited Mask (3 bits) |
// |--------------|----------------------|
// | 0            | 000, 001, ..., 111   | 2 ^ n
// | 1            | 000, 001, ..., 111   | 2 ^ n
// | 2            | 000, 001, ..., 111   | 2 ^ n 

// So the total nomber of times in worst case the outer while loop of queue can have this (3 * 2 ^ 3) number of states.
// and the inner for loop of nbr can also run for n times in worst case.

//T.C will be = O(n^2 * 2^n) 
// Space complexity is O(n×2^n)


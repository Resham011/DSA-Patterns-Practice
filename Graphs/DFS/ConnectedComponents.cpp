// 💡 Core insights (intuition flow)
// 1️⃣ Treat each couple as a single entity

// People (2k, 2k+1) always belong to couple k.

// So, rather than tracking individuals, think of couples being split across seat pairs.

// 2️⃣ Think in seat pairs

// Seats naturally come in pairs: (0,1), (2,3), (4,5), …

// Each seat pair may contain:

// Two people from the same couple ✅

// Two people from different couples ❌

// 3️⃣ “Different couples in one seat pair” creates a connection

// If a seat pair has one person from couple A and one from couple B,
// it means these two couples are intertwined (mixed up) — they depend on each other to get fixed.

// 👉 So, we draw an edge between A and B.

// 4️⃣ This forms a graph

// Nodes → couples

// Edges → seat pairs that mix two different couples

// Each connected component of this graph represents a set of couples that are tangled together.

// 5️⃣ Each component of size k needs k - 1 swaps

// Inside a connected component, couples are mixed.

// To fully separate and seat them correctly:

// You can fix one couple with each swap.

// After fixing k - 1 couples, the last one automatically becomes correct.

// Hence:

// Minimum swaps = total couples − number of connected components

// 6️⃣ Greedy algorithm matches this perfectly

// The greedy method (swap partner next to their pair)
// implicitly fixes one couple per step → exactly k - 1 swaps per connected component.

// So:

// Greedy = optimal

// Graph = proof of correctness


class Solution {
public:
    int dfs(int node, vector<bool>& vis, unordered_map<int, vector<int>>& adj){
        vis[node] = true;

        int size = 1;

        for(auto& nbr : adj[node]){
            if(vis[nbr] == false){
                size += dfs(nbr, vis, adj);
            }
        }
        return size;
    }
    int minSwapsCouples(vector<int>& row) {
        int n = row.size() / 2; // NUMBER OF COUPLE PAIRS

        unordered_map<int, vector<int>> adj;

        for(int i = 0; i < n * 2 - 1; i += 2){
            int one = row[i] / 2; // BY DIVIDING IT BY 2 WE ARE EXTRACTING THAT UNDER WHICH COUPLE GROUP THEY FALL LIKE [0, 1] FALLS UNDER [GROUP 0] [1, 2] --> GROUP 1 [3, 4] --> GROUP 2 AND SO ON 
            int two = row[i + 1] / 2; 

            if(one != two){
                // THESE TWO GROUPS ARE CONNECTED THERE IS EDGE BETWEEN THESE 
                adj[one].push_back(two);
                adj[two].push_back(one);
            }
        }
        int swaps = 0;
        vector<bool> vis(n, false);
        for(int i = 0; i < n; i++){
            if(vis[i] == false){
                int size = dfs(i, vis, adj); // SIZE IS THE COMPONENT SIZE 
                if(size > 1)  swaps += size - 1;
            }
        }
        return swaps;
    }
};
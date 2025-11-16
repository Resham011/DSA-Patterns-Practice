class Solution {
public:
    int maxi;
    int MaxTime;

    void solve(int node, int time, int quality, vector<int>& vis, unordered_map<int, vector<vector<int>>>& adj, vector<int>& values){
        if(time > MaxTime) return;
        if(node == 0) maxi = max(maxi, quality);

        vis[node]++; 
        if(vis[node] == 1) quality += values[node];

        for(auto vec : adj[node]){
            int nbr = vec[0];
            int wt = vec[1];

            solve(nbr, time + wt, quality, vis, adj, values);
        }
        vis[node]--; //backtrack
    }
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        MaxTime = maxTime;
        maxi = values[0];
        unordered_map<int, vector<vector<int>>> adj;

        for(auto edge : edges){
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt});
        }

        vector<int> vis(values.size(), 0);
        solve(0, 0, 0, vis, adj, values);
        return maxi;
    }
}; 
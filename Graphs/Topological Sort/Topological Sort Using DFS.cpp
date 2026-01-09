class Solution {
public:
     bool dfs(int node, stack<int>& st, vector<int>& inrec, vector<int>& vis, unordered_map<int, vector<int>>& adj){
          inrec[node] = true;
          vis[node] = true;

          for(auto& nbr : adj[node]){
               if(vis[nbr] && inrec[nbr]) return true; //cycle present
               if(vis[nbr] == false){
                    if(dfs(nbr, st, inrec, vis, adj)) return true;
               }            
          }
          st.push(node);
          inrec[node] = false;
          return false;
     }
     vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
          unordered_map<int, vector<int>> adj;

          for(auto& edge : prerequisites){
               int a = edge[0];
               int b = edge[1];

               adj[b].push_back(a);
          }
          vector<int> inrec(numCourses, false);
          vector<int> vis(numCourses, false);
          stack<int> st;
          for(int i = 0; i < numCourses; i++){
               if(vis[i] == false){
                    if(dfs(i, st, inrec, vis, adj)) return {}; 
               }
          }
          vector<int> ans;
          while(!st.empty()){
               ans.push_back(st.top());
               st.pop();
          }
          return ans;
     }
}; 



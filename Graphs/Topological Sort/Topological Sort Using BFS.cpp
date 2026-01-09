class Solution {
public:
     vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
          unordered_map<int, vector<int>> adj;
          vector<int> indegree(numCourses, 0);
          queue<int> q;
          vector<int> ans;
          for(auto it : prerequisites){
               int u = it[0];
               int v = it[1];
               adj[v].push_back(u);
               indegree[u]++;
          }

          for(int i = 0; i < numCourses; i++){
               if(indegree[i] == 0) q.push(i);
          }

          while(!q.empty()){
               int n = q.size();
               int course = q.front();
               q.pop();
               ans.push_back(course);
               for(auto nbr : adj[course]){
                    indegree[nbr]--;
                    if(indegree[nbr] == 0) q.push(nbr);
               }
          }
          return (ans.size() == numCourses) ? ans : vector<int>{};
     }
};



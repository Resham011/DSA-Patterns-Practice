class Solution {
     public:
     string findOrder(vector<string> &words) {
          int n = words.size();
          unordered_set<char> st;
          unordered_map<char, vector<char>> adj;
          vector<int> indegree(26, 0);
          
          for (auto &w : words){
               for (char c : w){
                    st.insert(c);
               }
          }
          
          for(int i = 0; i < n - 1; i++){
               string a = words[i];
               string b = words[i + 1];
               bool found = false;
               
               int minLen = min(words[i].size(), words[i + 1].size());
               
               for(int j = 0; j < minLen; j++){
                    if(a[j] != b[j]){
                         adj[a[j]].push_back(b[j]);
                         indegree[b[j] - 'a']++;
                         found = true;
                         break;
                    }
               }
               
               if(found == false && words[i].size() > words[i + 1].size()) return "";
          }
          
          string ans = "";
          queue<char> q;
          
          for(int i = 0; i < 26; i++){
               if(indegree[i] == 0 && st.find('a' + i) != st.end()){
                    q.push('a' + i);
               }
          }
          
          while(!q.empty()){
               char front = q.front();
               ans += front;
               q.pop();
               
               for(auto& nbr : adj[front]){
                    indegree[nbr - 'a']--;
                    if(indegree[nbr - 'a'] == 0) q.push(nbr);
               }
          }
          
          return ans.size() == st.size() ? ans : "";
     }
};


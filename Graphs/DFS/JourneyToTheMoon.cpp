// USING DFS
void dfs(int i,map<int,vector<int>>&m,vector<int>&visited,long long &temp) {
    visited[i]=1;
    temp++;
    for(auto a:m[i]) {
        if(visited[a]==0) {
            dfs(a,m,visited,temp);
        }
    }
}
int journeyToMoon(int n, vector<vector<int>> astronaut) {
    map<int,vector<int>> m;
    for(auto a:astronaut) {
        m[a[0]].push_back(a[1]);
        m[a[1]].push_back(a[0]);
    }
    //for(int i=0;i<n;i++)m[i]={};
    vector<int> visited(n);
    long long ans=0;
    for(int i=0;i<n;i++) {
        if(visited[i]==0) {
            long long temp=0;
            dfs(i,m,visited,temp);
            ans=ans+temp*(n-temp);
        }
    }
    cout<<ans/2;
    return ans/2;
}

// USING DSU

int find_root(vector<int>& parent, int x){
    if(parent[x] == x) return x;
    return parent[x] = find_root(parent, parent[x]);
}
void Union(vector<int>& parent, int x, int y){
    int x_parent = find_root(parent, x);
    int y_parent = find_root(parent, y);

    if(x_parent == y_parent) return;

    parent[x_parent] = y_parent;
}

// RETURN type changed to long long
long long journeyToMoon(int n, vector<vector<int>> astronaut) {
     vector<int> parent(n);
     for(int i = 0; i < n; i++){
          parent[i] = i;
     }

     // union all pairs
     for(const auto& vec : astronaut){
          Union(parent, vec[0], vec[1]);
     }

     // path compression so that each astraunot points to its root parent
     for(int i = 0; i < n; i++){
          find_root(parent, i);
     }

     // Count astronauts in each country (root)
     vector<int> country_size(n, 0);
     for(int i = 0; i < n; i++){
          country_size[parent[i]]++;
     }

     long long sum = 0;
     long long ans = 0;
     for(int i = 0; i < n; i++){
          if (country_size[i] > 0) {
               ans += (long long)country_size[i] * sum;
               sum += country_size[i];
          }
     }
     return ans;
}


class Solution {
public:
     // -------------------------------
     // Backtracking function to build all shortest paths
     // -------------------------------
     void backtrack(string& word,                    // current word
                    string& beginWord,               // starting word
                    unordered_map<string, vector<string>>& parent, // map of {child -> parents}
                    vector<string>& path,            // current path being built
                    vector<vector<string>>& ans) {   // final result
          // If we reached the beginWord, we found a complete path
          if (word == beginWord) {
               vector<string> temp = path;
               reverse(temp.begin(), temp.end());      // reverse since we built path backwards
               ans.push_back(temp);
               return;
          }

          // Explore all parent words of the current word
          for (auto& p : parent[word]) {
               path.push_back(p);                      // add parent to path
               backtrack(p, beginWord, parent, path, ans); // recurse
               path.pop_back();                        // backtrack (remove parent)
          }
     }

     // -------------------------------
     // Find all valid neighbors (words differing by 1 letter and existing in dictionary)
     // -------------------------------
     vector<string> findValidNbr(string& str, unordered_set<string>& st){
          vector<string> valid;
          
          // Try changing every character of the word
          for(int i = 0; i < str.size(); i++){
               for(char ch = 'a'; ch <= 'z'; ch++){
                    string curr = str;
                    curr[i] = ch;                       // replace one char
                    
                    // If new word exists in dictionary, it's valid
                    if(st.find(curr) != st.end()) 
                         valid.push_back(curr);
               }
          }
          return valid;
     }

     // -------------------------------
     // Main function: find all shortest transformation sequences
     // -------------------------------
     vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
          // Put all dictionary words into a set for O(1) lookup
          unordered_set<string> st(wordList.begin(), wordList.end());

          // Queue for BFS
          queue<string> q;
          // Parent map: stores "who led to this word"
          unordered_map<string, vector<string>> parent;
          // Global visited words (to avoid revisiting old layers)
          unordered_set<string> visited;
          bool found = false; // flag when we reach endWord

          // Start BFS with beginWord
          q.push(beginWord);

          // BFS loop
          while(!q.empty()){
               int size = q.size();                    // number of nodes in current level
               unordered_set<string> visitedInLevel;   // track words visited in this BFS level

               while(size--){
                    string node = q.front();
                    q.pop();
                    
                    // If we reached the endWord, stop BFS (shortest paths found)
                    if(node == endWord){
                         found = true;
                         break;
                    } 

                    // Get all valid neighbors
                    vector<string> adj = findValidNbr(node, st);
                    for(auto& nbr : adj){
                         // Only consider neighbors that are not globally visited before
                         if(visited.find(nbr) == visited.end()){
                         parent[nbr].push_back(node);  // store parent relationship

                         // Add to queue only once in this level REMENBER THIS ELSE DUPLICATE PATHS WILL BE SHOWN 
                         if(visitedInLevel.find(nbr) == visitedInLevel.end()){
                              q.push(nbr);                        
                              visitedInLevel.insert(nbr);
                         }
                         }
                    }
               }

               // If we found endWord at this level → stop BFS
               if(found) break;

               // Mark all words in this level as globally visited after complete the previous entire level in queue
               visited.insert(visitedInLevel.begin(), visitedInLevel.end());
          }

          // -------------------------------
          // Backtracking stage: reconstruct paths from endWord to beginWord
          // -------------------------------
          vector<vector<string>> ans;
          if(found){
               vector<string> path = {endWord};         // start path from endWord
               backtrack(endWord, beginWord, parent, path, ans);
          }

          return ans;
     }
};


                    // for(auto& nbr : adj){
                    //      // Only consider neighbors that are not globally visited before
                    //      if(visited.find(nbr) == visited.end()){
                    //      parent[nbr].push_back(node);  // store parent relationship

                    //      // Add to queue only once in this level REMENBER THIS ELSE DUPLICATE PATHS WILL BE SHOWN 
                    //      if(visitedInLevel.find(nbr) == visitedInLevel.end()){
                    //           q.push(nbr);                        
                    //           visitedInLevel.insert(nbr);
                    //      }
                    //      }
                    // }
                    // ALL PROBLEM EDGE CASE ARE HERE 

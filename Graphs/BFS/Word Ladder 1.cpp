// 🚀 Word Ladder – Revision Guide
// 1️⃣ Problem in Simple Words

// Start with beginWord.

// End with endWord.

// At each step, you can change one letter to form a new word.

// New word must exist in the wordList.

// Find the shortest sequence length from beginWord to endWord.

// 2️⃣ Where I Started (My First Attempt)

// Wrote a recursive DFS (solve).

// Used ValidWords to find neighbors.

// Tried to compute minimum steps by exploring all paths.

// 3️⃣ Mistakes I Made

// Wrong adjacency condition

// I first checked if letters were from the same set.

// Correct rule: two words are neighbors if they differ by exactly one character at the same index.

// No visited tracking

// My DFS went in cycles (hit → hot → hit → hot …).

// Result: stack overflow error.

// Chose DFS for shortest path

// DFS explores deep paths first.

// To guarantee shortest, DFS must explore all paths.

// This leads to exponential complexity.

// 4️⃣ Key Realization

// The problem isn’t just “find a path”.

// It’s “find the shortest path”.

// DFS is bad for shortest paths.

// BFS is perfect:

// Expands outward level by level.

// The first time you hit endWord, you are guaranteed it’s the shortest.

// No need to explore useless long paths.

// 5️⃣ Why BFS Works (Visual Intuition)

// Example: hit → cog, wordList = [hot, dot, lot, dog, log, cog]

// BFS Exploration (by levels)

// Level 0: hit
// Level 1: hot
// Level 2: dot, lot
// Level 3: dog, log
// Level 4: cog ✅


// The moment we see cog at level 4 → done. This is the shortest path.

// DFS Exploration (possible path)

// hit → hot → lot → log → (maybe goes deeper or circles around)


// DFS may waste time before finding cog.

class Solution {
public:
    vector<string> ValidWords(string& str, vector<string>& wordList, unordered_set<string>& visited){
        vector<string> valid;
        for(auto& word : wordList){
            if(visited.count(word)) continue; // skip visited
            if(word.size() != str.size()) continue;
            int diff = 0;
            for(int i = 0; i < str.size(); i++){
                if(str[i] != word[i]) diff++;
            }
            if(diff == 1) valid.push_back(word);
        }
        return valid;
    }

    int solve(string begin, string& end, vector<string>& wordList, unordered_set<string>& visited){
        if(begin == end) return 0;

        visited.insert(begin); // mark current word visited
        int ans = INT_MAX;

        vector<string> isValid = ValidWords(begin, wordList, visited);
        for(auto& word : isValid){
            int curr = solve(word, end, wordList, visited);
            if(curr != INT_MAX){
                ans = min(ans, 1 + curr);
            }
        }

        visited.erase(begin); // backtrack (if you want all paths, not shortest)
        return ans;
    }

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> st(wordList.begin(), wordList.end());
        if(st.find(endWord) == st.end()) return 0;

        unordered_set<string> visited;
        int ans = solve(beginWord, endWord, wordList, visited);

        return (ans == INT_MAX ? 0 : ans + 1); 
        // +1 because ladderLength counts number of words including beginWord
    }
};

// 🔑 The Problem Goal

// We need the shortest transformation sequence length.

// That means: from beginWord to endWord, changing one letter at a time, find the minimum number of steps.

// 🟥 Why DFS is inefficient

// DFS explores deep paths first

// DFS will try one sequence of transformations all the way until it hits endWord (or dead end).

// That path might be very long compared to the shortest path.

// Example: shortest path is hit → hot → dot → dog → cog (length 5).
// But DFS could first explore a 15-step chain before ever reaching cog.

// You must check all paths to guarantee shortest

// DFS doesn’t stop when it finds the target, because maybe there’s a shorter path elsewhere.

// So, you need to explore every possible route → exponential complexity.

// Exponential branching

// Each word can branch to many valid neighbors.

// Without pruning, DFS will explore nearly all possibilities → complexity blows up.

// Stack depth risk

// With long paths, recursive DFS risks stack overflow (like you just saw).

// BFS uses an explicit queue, no recursion depth issues.

// 🟩 Why BFS is efficient

// BFS explores by levels

// It checks all words reachable in 1 step, then all in 2 steps, then 3 steps, etc.

// The moment BFS hits endWord, you know it’s the shortest path. ✅

// Early exit

// BFS stops as soon as the target is found → no need to explore longer paths.

// Polynomial time

// BFS visits each word at most once → O(N * L) complexity (N = number of words, L = word length).

// Much better than exponential DFS.


class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        queue<string> q;
        unordered_map<string, vector<string>> adj;
        for(auto word : wordList){
            if(word.size() != beginWord.size()) continue;
            int diff = 0;
            for(int i = 0; i < beginWord.size(); i++){
                if(beginWord[i] != word[i]) diff++; 
            }
            if(diff == 1){
                adj[beginWord].push_back(word);
                adj[word].push_back(beginWord);
            }
        }
        for(auto word : wordList){
            for(auto curr : wordList){
                if(word.size() != curr.size()) continue;
                int diff = 0;
                for(int i = 0; i < curr.size(); i++){
                    if(curr[i] != word[i]) diff++;
                }
                if(diff == 1){
                    adj[word].push_back(curr);
                    adj[curr].push_back(word);
                } 
            }
        }
        
        int ans = 0;
        unordered_set<string> visited;
        q.push(beginWord);

        while(!q.empty()){
            int size = q.size();

            while(size--){
                auto str = q.front();
                q.pop();

                if(str == endWord) return ans + 1;

                for(auto& nbr : adj[str]){
                    if(visited.find(nbr) == visited.end()){
                        visited.insert(nbr);
                        q.push(nbr);
                    }
                }
            }
            ans++;
        }
        return 0;
    }       
};
// T.C : O(m * n)
class Solution {
public:
     int m;
     int n;
     void dfs(int i, int j, vector<vector<char>>& board){
          if(i < 0 || j < 0 || i >= m || j >= n || board[i][j] != 'O') return;
               
          board[i][j] = 'S';
          dfs(i + 1, j, board); // boundary vale "O" ke left right up down jitne bhi directly connected "O" hai vo bhi save hai vo "X" meh convert nhi ho sakte kyuki vo "X" se surrounded nhi ha 4o side se 
          dfs(i - 1, j, board);
          dfs(i, j + 1, board);
          dfs(i, j - 1, board);
          return;
     }
     void solve(vector<vector<char>>& board) {
          m = board.size();
          n = board[0].size();

          // first row
          for(int col = 0; col < n; col++){
               if(board[0][col] == 'X' || board[0][col] == 'S') continue;
               dfs(0, col, board);
          }
          // last row
          for(int col = 0; col < n; col++){
               if(board[m - 1][col] == 'X' || board[m - 1][col] == 'S') continue;
               dfs(m - 1, col, board);
          }
          // first column
          for(int row = 0; row < m; row++){
               if(board[row][0] == 'X' || board[row][0] == 'S') continue;
               dfs(row, 0, board);
          }        
          // last col
          for(int row = 0; row < m; row++){
               if(board[row][n - 1] == 'X' || board[row][n - 1] == 'S') continue;
               dfs(row, n - 1, board);
          }  

          for(int i = 0; i < m; i++){
               for(int j = 0; j < n; j++){
                    if(board[i][j] == 'S') board[i][j] = 'O';
                    else if(board[i][j] == 'O') board[i][j] = 'X'; 
               }
          }
     }
};
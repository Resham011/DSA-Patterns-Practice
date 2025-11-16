/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
     Node* cloneGraph(Node* node) {
          if(node == NULL) return NULL;
          unordered_map<Node*, Node*> clone;
          queue<Node*> q;
          unordered_set<Node*> visited;

          int val = node->val;
          Node* cloneNode = new Node(val);
          clone[node] = cloneNode;
          q.push(node);
          visited.insert(node);

          while(!q.empty()){
               Node* node = q.front();
               q.pop();

               Node* cloneNode = clone[node];

               for(Node* nbr : node->neighbors){
                    if(clone.find(nbr) == clone.end()){
                         // create the clone 
                         int val = nbr->val;
                         Node* cloneOfNbr = new Node(val);
                         clone[nbr] = cloneOfNbr;
                    }
                    cloneNode->neighbors.push_back(clone[nbr]);

                    if(visited.find(nbr) == visited.end()){
                         q.push(nbr);
                         visited.insert(nbr);
                    }
               }
          }
          return cloneNode;
     }
};
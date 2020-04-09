#include "node.h"

Node * Tree_helper(priority_queue_t pq){
  if (pq.size() == 1){
    return pq.top();
  }
  Node *a = pq.top();
  pq.pop();
  Node *b = pq.top();
  pq.pop();
  Node *curr_tree = new Node(a,b);
  pq.push(curr_tree);
  return Tree_helper(pq);
}



Node *  buildTree(uint64_t * counts) {
  priority_queue_t pq;
  //Node * tree;
  for (int i = 0; i < 257; i++){
    //Node curr(i, counts[i]);
    if (counts[i] > 0){
      pq.push(new Node(i, counts[i]));
    }
  }
  if (pq.size() == 0){
    return NULL; 
  }
  Node *ans = Tree_helper(pq);
  return ans;
}



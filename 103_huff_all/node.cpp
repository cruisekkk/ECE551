#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned,BitString> & theMap) {
  if (sym != NO_SYM){
    assert(left == NULL && right == NULL);
    theMap[sym] = b;
  }
  else {
    //Node *curr = this;
    //left
    this->left->buildMap(b.plusZero(), theMap);
    //right
    this->right->buildMap(b.plusOne(), theMap);
      //buildMap(b, theMap);
  }
}


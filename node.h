#ifndef NODE_H
#define NODE_H
#include <iostream>

class Node
{
 public:
  // constructors and destructors
  Node();
  Node(int);
  ~Node();

  // functions (getters)
  Node* getLeft(); // returns left child
  Node* getRight(); // returns right child
  int getValue(); // returns data value

  // functions (setters)
  void setLeft(Node*); // establish left child
  void setRight(Node*); // establish right child
  void setValue(int); // establish data value
  
 private:
  // variables
  int data;
  Node* left;
  Node* right;
  
};
#endif

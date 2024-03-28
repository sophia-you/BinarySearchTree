#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

// default constructor
Node::Node()
{
  // initialize all variables as null
  data = 0;
  left = NULL;
  right = NULL;
}

// regular constructor
Node::Node(int newdata)
{
  data = newdata;
  left = NULL;
  right = NULL;
}

// destructor, which destroys anything left on the heap
Node::~Node()
{
  left = NULL;
  right = NULL;
}

		
// returns left child
Node* Node::getLeft()
{
  return left;
}

// returns right child
Node* Node::getRight()
{
  return right;
}

// returns data value
int Node::getValue()
{
  return data;
}

// set left child
void Node::setLeft(Node* newleft)
{
  left = newleft;
}

// set right child
void Node::setRight(Node* newright)
{
  right = newright;
}

// set new data
void Node::setValue(int newdata)
{
  data = newdata;
}

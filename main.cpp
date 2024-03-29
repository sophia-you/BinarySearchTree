#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"

using namespace std;

/*
 * Author | Sophia You
 * Date | March 27 2024
 * Description | This is a binary search tree. Data values are entered from either the
 * console or via a file. The first data value is the root of the tree. As each data
 * value is entered, if it is less than the root, it becomes a left descendant, and if 
 * it is greater than the root, it becomes a right descendant. A user should be able to
 * add, search for, and remove parts of the tree.
 */

// FUNCTION PROTOTYPES
void insert(Node* &root, Node* current,  Node* newnode);
void print(Node* current, int numTabs);
bool traverse(Node* current, int searchkey);
void remove(Node* &root, Node* current, Node* parent, int searchkey);

int main()
{
  // user input and running
  int max = 50;
  char input[max];
  bool running = true;

  // binary tree
  Node* root = NULL;

  // the program will loop until the user wants to quit
  while (running)
    {
      // instructions
      cout << endl;
      cout << "Please only use lowercase letters." << endl;
      cout << "This is a binary search tree." << endl;
      cout << endl;
      cout << "To quit the program, type 'quit.'" << endl;
      cout << "To insert nodes, type 'insert.'" << endl;
      cout << "To remove nodes, type 'remove.'" << endl;
      cout << "To visualize your tree, type 'print'" << endl;
      cout << "To find a value in the tree, type 'search.'" << endl;

      cin.getline(input, max);

      // stop running
      if (strcmp(input, "quit") == 0)
	{
	  running = false;
	}

      // insert nodes into the tree via console or file
      else if (strcmp(input, "insert") == 0)
	{
	  cout << "to insert via console, type 'console.'" << endl;
	  cout << "to insert via file, type 'file.'" << endl;
	  cin.getline(input, max);
	  if (strcmp(input, "console") == 0)
	    {
	      int numValues = 0;
	      int newnum = 0;
	      cout << "How many data values are you entering?" << endl;
	      cin >> numValues;
	      cin.ignore(max, '\n');
	      cout << "Enter your values separated by a space." << endl;
	      for (int i = 0; i < numValues; i++)
		{
		  cin >> newnum;
		  Node* newnode = new Node(newnum);
		  insert(root, root, newnode);
		  print(root, 0);
		}
	      
	      cin.ignore(max, '\n');
	      
	    }
	  else if (strcmp(input, "file") == 0)
	    {
	      // read in the file
	      cout << "What is the name of the file you want to read in?" << endl;
	      cin.getline(input, max);
	      ifstream inFile;
	      inFile.open(input);

	      int newnum = 0; // temporarily keeps track of values
	      while (inFile >> newnum)
		{
		  Node* newnode	= new Node(newnum);
                  insert(root, root, newnode);
		}

	      // print out the tree
	      print(root, 0);
	      
	      inFile.close();
	    }
	}

      // prompt the user for a node to remove
      else if (strcmp(input, "remove") == 0)
        {
	  cout << "What number are you trying to remove?" << endl;
	  int searchkey = 0; // this is the number we're trying to remove
	  cin >> searchkey;
	  cin.ignore(max, '\n');

	  // we must make sure the value we want to remove is in the tree.
	  if (!traverse(root, searchkey))
	    {
	      cout << "This value is not in the binary tree." << endl;
	    }
	  else
	    {
	      remove(root, root, root, searchkey);
	      print(root, 0);
	    }
        }

      // displays the tree in a visual manner
      else if (strcmp(input, "print") == 0)
        {
	  print(root, 0);
        }

      // determines whether a node exists or not within a tree
      else if (strcmp(input, "search") == 0)
        {
	  cout << endl;
	  cout << "Which number are you trying to find?" << endl;
	  int searchkey = 0; // this is the number we are trying to find
	  cin >> searchkey;
	  cin.ignore(max, '\n');
	  bool found = traverse(root, searchkey);
	  if (found)
	    {
	      cout << "This value exists in the binary tree." << endl;
	    }
	  else
	    {
	      cout << "This value does not exist in the binary tree." << endl;
	    }
        }
    }

  return 0;
}

/**
 * This function takes in a new node (created above in main) which contains
 * a new value. It compares the new node's value to the root of the binary
 * search tree. If the new value is greater, it goes down to the right child,
 * and if it is lesser, it goes down the left. This process is repeated
 * with each node until the new value reaches a left and establishes
 * its position there.
 *
 * @param root | the root of the btree in question
 * &param current | the current node in the btree we're evaluating
 * @param newnode | the node we want to put in
 */
void insert(Node* &root, Node* current, Node* newnode)
{

  if (root == NULL) // empty tree
    {
      root = newnode;
      return;
    }

  // the new node is smaller than the parent; add to left branch
  else if (newnode->getValue() < current->getValue())
    {
      if (current->getLeft() == NULL) // reached a leaf
	{
	  current->setLeft(newnode);
	}
      else // keep moving down the tree
	{
	  insert(root, current->getLeft(), newnode);
	}
    }

  // the new node is larger than the parent; add to right branch
  else if (newnode->getValue() > current->getValue())
    {
      if (current->getRight() == NULL) // reached a leaf
	{
	  current->setRight(newnode);
	}
      else // keep moving down the tree
	{
	  insert(root, current->getRight(), newnode);
	}
    }

  // we cannot have two nodes of the same value
  else if (newnode->getValue() == current->getValue())
    {
      cout << "Two nodes of the same value cannot be added." << endl;
      cout << "Therefore the node " << newnode->getValue() << " cannot be addedmore than once." << endl;
    }
}

/**
 * This function, given a searchkey, removes the requested node from the 
 * binary tree.
 * If the node is question has no children, the node is simply deleted.
 * If the node has one child, the child is adopted by the grandparent.
 * If the node has two children, we must find the next largest node.
 * This means we go to the right child, then as left as possible. The
 * left descendant replaces the original node. The left descendant's child,
 * who should be a right child, is then adopted by its grandparent. 
 */

void remove(Node* &root, Node* current, Node* parent, int searchkey)
{
  // This returns if the searchkey isn't found
  // This shouldn't happen because we have built in a searchkey check
  // up in main
  if (current == NULL)
    {
      return;
    }
  
  // we have found the node to remove
  if (searchkey == current->getValue())
    {

      // this node has no children; we can just delete it
      if (current->getLeft() == NULL &&
	  current->getRight() == NULL)
      {

	// the root is the only thing in the tree
	if (current == root)
	  {
	    root = NULL; // the tree is now empty
	  }
	// current node itself is a left child
	if (parent->getLeft() == current)
	  {
	    parent->setLeft(NULL);
	  }
	// current node itself is a right child;
	else if (parent->getRight() == current)
	  {
	    parent->setRight(NULL);
	  }
	Node* temp = current;
	delete temp;
      }

      // if the node has one child
      else if (current->getLeft() == NULL || current->getRight() == NULL)
	{
	  // this is the current node's non-null child
	  // this child will be adopted by current node's parent
	  Node* child = NULL;

	  // determine which child is not null
	  if (current->getLeft() != NULL)
	    {
	      child = current->getLeft();
	    }
	  else if (current->getRight() != NULL)
	    {
	      child = current->getRight();
	    }

	  // if the node to be removed is the root
	  if (current == root)
	    {
	      // we cannot just delete the root since it's by reference
	      Node* temp = current;
	      root = child;
	      delete temp;
	    }
	  else // the node to be removed isn't the root
	    {
	      // adopt the child (if the current node is not the root)
	      if (parent->getLeft() == current)
		{
		  parent->setLeft(child);
		}
	      else if (parent->getRight() == current)
		{
		  parent->setRight(child);
		}

	      Node* temp = current;
	      delete temp;
	    }
	}

      // the node has two children
      else if (current->getLeft() != NULL && current->getRight() != NULL)
	{
	  
	  // we need to find the next largest node AND the next largest node's
	  // parent
	  // go to the right child, then go left as far as possible
	  Node* nextLargest = current->getRight();
	  Node* nextLargestParent = current;
	  while (nextLargest->getLeft() != NULL)
	    {
	      nextLargestParent = nextLargest;
	      nextLargest = nextLargest->getLeft();
	    }

	  /*
	   * IMPORTANT NOTE:
	   * If this while statement works, the node nextLargest should NOT
	   * have another left child. It either has a right child or no
	   * children.
	   */

	  // we must save the child's subtree
	  // this is the child of the next largest node
	  Node* nextChild = nextLargest->getRight();

	  // next, we must disconnect the next largest from its subtree
	  // this is because we are moving the next largest to replace
	  // the current node and we don't want it to have baggage
	  nextLargest->setRight(NULL);

	  // nextLargest will replace where the parent node used to be
	  if (current == root) // if the node to be removed is the root
	    {
	      Node* temp = current;

	      // root is replaced by the next largest node
	      root = nextLargest;

	      // connect nextLargest to the root's original subtree
	      if (current->getLeft() != nextLargest)
                {
                  nextLargest->setLeft(current->getLeft());
                }
              if (current->getRight() != nextLargest)
                {
                  nextLargest->setRight(current->getRight());
                }

	      // nextLargest's original parent will adopt nextLargest's child
              if (nextLargestParent != current)
                {
                  nextLargestParent->setLeft(nextChild);
                }

	      delete temp;
	    }
	  else // the node to be removed isn't the root
            {
	      
              // if the current node in question is a left child
              if (parent->getLeft() == current)
                {
                  parent->setLeft(nextLargest);
                }

	      // the current node is a right child
              else if (parent->getRight() == current)
                {
		  parent->setRight(nextLargest);
                }

	      // the next largest has replaced the current node's position
	      // we much attach the nextLargest to current node's subtree
	      if (current->getLeft() != nextLargest)
		{
		  nextLargest->setLeft(current->getLeft());
		}
	      if (current->getRight() != nextLargest)
		{
		  nextLargest->setRight(current->getRight());
		}
	      
	      // there is still an empty space between nextLargest's parent
	      // and nextLargest's child; we must bridge that gap
	      if (nextLargestParent != current)
		{
		  nextLargestParent->setLeft(nextChild);
		}
	      
              Node* temp = current;
              delete temp;
            }
	  
	}
    }
  else if (searchkey < current->getValue())
    {
      remove(root, current->getLeft(), current, searchkey);
    }
  else if (searchkey > current->getValue())
    {
      remove(root, current->getRight(), current, searchkey);
    }
  
}

/**
 * This function displays the binary search tree in a visual manner,
 * sideways.
 * 
 * @param current | the current node we are print out
 * @param numTabs | the number of indentations required for this node
 */
void print(Node* current, int numTabs)
{

  // if we get to a leaf, we want to jump out of print
  if (current == NULL)
    {
      return; // nothing to print
    }

  // otherwise, we have not reached a leaf
  numTabs += 1; // indent one more in
  print(current->getRight(), numTabs); // recursively print right child
  cout << endl; // line break
  for (int i = 1; i < numTabs; i++)
    {
      // indent the number of times as stated by numTabs
      cout << "\t";
    }
  cout << current->getValue() << "\n"; // print the current value
  print(current->getLeft(), numTabs); // recursively print left child
}

/**
 * This function, when given a "searchkey," walks through the
 * binary tree and determines whether the searchkey is found in the tree.
 *
 * @param current | the current node we're dealing with
 * @param searchkey | the value of the node we're trying to find
 * @return bool | returns whether or not the searchkey was found.
 */
bool traverse(Node* current, int searchkey)
{
  // base case; we have not found the key
  if (current == NULL)
    {
      // we have walked through the tree without finding it
      return false;
    }
  
  // the searchkey has been found
  else if (current->getValue() == searchkey)
    {
      return true;
    }
  
  // RECURSIVE CASES
  // search key is less than current node; go left
  else if (searchkey < current->getValue())
    {
      return traverse(current->getLeft(), searchkey);
    }
  // search key is greater than current node; go right
  else if (searchkey > current->getValue())
    {
      return traverse(current->getRight(), searchkey);
    }

  return false;
}

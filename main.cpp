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
void traverse(Node* current, int searchkey);

int main()
{
  // user input and running
  int max = 50;
  char input[max];
  bool running = true;

  // binary tree
  Node* root = NULL;

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
      if (strcmp(input, "quit") == 0)
	{
	  running = false;
	}
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
		  cout << newnum << endl;
		  Node* newnode = new Node(newnum);
		  insert(root, root, newnode);
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
		  cout << "current number: " <<  newnum << endl;
		  Node* newnode	= new Node(newnum);
                  insert(root, root, newnode);
		  print(root, 0);
		  
		}

	      inFile.close();
	    }
	}
      else if (strcmp(input, "remove") == 0)
        {
	  cout << "What number are you trying to remove?" << endl;
	  
        }
      else if (strcmp(input, "print") == 0)
        {
	  print(root, 0);
        }
      else if (strcmp(input, "search") == 0)
        {
	  cout << "Which number are you trying to find?" << endl;
	  int searchkey = 0; // this is the number we are trying to find
	  cin >> searchkey;
	  cin.ignore(max, '\n');
	  traverse(root, searchkey);
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
  cout << "in insert" << endl;

  if (root == NULL) // empty tree
    {
      cout << "adding new node" << endl;
      root = newnode;
      return;
    }

  // the new node is smaller than the parent; add to left branch
  else if (newnode->getValue() < current->getValue())
    {
      cout << "to left branch" << endl;
      if (current->getLeft() == NULL) // reached a leaf
	{
	  cout << "adding new node in left branch" << endl;
	  current->setLeft(newnode);
	  cout << current->getLeft()->getValue() << endl;
	}
      else // keep moving down the tree
	{
	  cout << "we have to continue (L)" << endl;
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
	  cout << "we have to continue (R)" << endl;
	  insert(root, current->getRight(), newnode);
	}
    }

  // we cannot have two nodes of the same value
  else if (newnode->getValue() == current->getValue())
    {
      cout << "Two nodes of the same value cannot be added." << endl;
      cout << "Therefore the node " << newnode->getValue() << " cannot be added" << endl;
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
 */
void traverse(Node* current, int searchkey)
{
  // base case; we have not found the key
  if (current == NULL)
    {
      cout << "This value does not exist in the tree." << endl;
      return;
    }
  
  // the searchkey has been found
  else if (current->getValue() == searchkey)
    {
      cout << "This value exists in the tree." << endl;
    }
  
  // RECURSIVE CASES
  // search key is less than current node; go left
  else if (searchkey < current->getValue())
    {
      traverse(current->getLeft(), searchkey);
    }
  // search key is greater than current node; go right
  else if (searchkey > current->getValue())
    {
      traverse(current->getRight(), searchkey);
    }
}

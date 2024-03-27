#include <iostream>
#include <cstring>
#include <fstream>
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

int main()
{
  int max = 50;
  char input[max];
  bool running = true;

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
      cout << "To find a value in the tree, type 'find.'" << endl;

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
	      cout << "Enter your data separated by a single space. Enter '-1' at the end of your data set when you are done." << endl;
	      cin.getline(input, max);
	      int length = strlen(input);
	      int newnum = 0;
	      for (int i = 0; i < 10; i++)
		{
		  cin >> newnum;
		  cout << newnum;
		}
	      
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
		  cout << newnum << endl;
		}

	      inFile.close();
	    }
	}
      else if (strcmp(input, "remove") == 0)
        {
        }
      else if (strcmp(input, "print") == 0)
        {
        }
      else if (strcmp(input, "find") == 0)
        {
        }
    }

  return 0;
}


//*this is a testing main checking for proper file read in
// and check to make sure the arrays are initialized
// correctly

#include <iostream>
#include <fstream>
#include "graphm.h"

using namespace std;

int main()
{
	//reading in files
   ifstream infile1("data31.txt");
   if (!infile1)
   {
      cerr << "File could not be opened." << endl;
      return 1;
   }

   GraphM G;
   G.buildGraph(infile1);

   //adjacency matrix and 2d "T" matrix should be populated

	return 0;
}
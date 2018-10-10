//---------------------------------------------------------------------------
// lab3.cpp
//---------------------------------------------------------------------------
// This code tests all of the basic functionality of the classes to
// perform Dijkstra's algorihms and depth-first search for CSS 343 Lab 3.
// It is not meant to exhaustively test the class.
//
// Assumptions:
//   -- students can follow the directions to interface with this file
//   -- text files "data31.txt" and "data32.txt" are formatted as described 
//---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include "graphl.h"
#include "graphm.h"
using namespace std;

//-------------------------- main -------------------------------------------
int main() {
   // part 1
   ifstream infile1("data3uwb.txt");
   if (!infile1) {
      cerr << "File could not be opened." << endl;
      return 1;
   }

   //for each graph, find the shortest path from every node to all other nodes
   for(;;){
      GraphM G;
      G.buildGraph(infile1);
      if (infile1.eof()) 
         break;
      G.findShortestPath();        
      G.displayAll();              // display shortest distance, path to cout
      G.display(3,1);              // display path from node 3 to 1 to cout
      // may be other calls to display
   }

   /*// part 2 
   ifstream infile2("data3uwb.txt");
   if (!infile2) {
      cerr << "File could not be opened." << endl;
      return 1;
   }

   //for each graph, find the depth-first search ordering
   for (;;) {
      GraphL G;
      G.buildGraph(infile2);
      if (infile2.eof()) 
         break;
      G.displayGraph();
      G.depthFirstSearch();    // find and display depth-first ordering to cout
   }*/

   cout << endl;
   return 0;
}


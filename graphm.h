
/* Aaron Parks
 * Prof. Carol Zander
 * CSS 343 : Winter 2010
 * Lab 3 - Part 1: Dijkstra's Shortest Path Algorithm */
 
/*--- GraphM Class -------------------------------------------------------------
 * GraphM is built around the 'findShortestPath' function for a graph. Using
 * values stored in a 2D-array "adjacency matrix" of path values and information
 * stored in TableType -- another 2D array of TableType structs - 
 * 'findShortestPath' calculates the optimal minimal distance between two 
 * connected nodes on a graph. Additionally, any path contain more than an
 * "origin" node and a "destination" node have the path information stored.
 *------------------------------------------------------------------------------
 * Assumptions
 * - NodeData
 *   -> nodedata member functions are implement correctly
 *   -> strings longer than 50 characters will not be inserted
 * - buildGraph
 *   -> data in data text files are formatted corrected
 *   -> external file for parameter was already checked for existance
 * - insertEdge
 *   -> negative nodes or edge values will be inserted.
 *   -> negative values inserted will auto-magically be converted to their
 *      absolute value
 *   -> 'findShortestPath' only needs to be called again from this function
 *      if  the adjacency matrix is being built with 'buildGraph'
 * - removeEdge
 *   -> the edge specified to be remove is in the adjacency matrix
 * - General
 *   -> number of nodes will not exceed MAX_NODES
 *   -> "row zero" and "column zero" will never be used
 *----------------------------------------------------------------------------*/
 
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <limits>
#include "nodedata.h"
using namespace std;

const int MAX_NODES = 100;                  //maximum size of arrays
const int MAX = numeric_limits<int>::max(); //very large int, used for comparing

class GraphM
{
public:
   //constructor
   GraphM();
   //destructor
   ~GraphM();
   
   //uses external file to populate adjacency matrix and TableType 2D array
   bool buildGraph(ifstream&);
   //populates 'dist' and 'path' in TableType 2D array
   void findShortestPath();
   //inserts edge values into adjacency matrix
   bool insertEdge(int, int, int, bool building = false);
   //removes edge from adjacency matrix
   bool removeEdge(int, int);

   //display functions
   //displays all information about the graph
   void displayAll() const;
   //displays the path between two nodes
   void displayPath(int, int) const;
   //displays the distance and potential path between two nodes
   void display(int, int) const;
private:
   struct TableType
   {
      bool visited;         //whether node has been visited or not
      int dist;             //shortest distance from source known so far
      int path;             //previous node in path of min dist      
   };
   
   NodeData data[MAX_NODES];          //string description for graph nodes
   int C[MAX_NODES][MAX_NODES];       //Cost array, aka adjacency matrix
   int size;                          //number of nodes in the graph
   TableType T[MAX_NODES][MAX_NODES]; //stores visited, distance, and path
   
   //find smallest path from node in parameter
   int getMinNode(int);
   //recursive function for 'displayPath'
   void displayPathHelper(int, int) const;
   //utility function for 'display' to display node names
   void displayNames(int, int) const;
   //recursive function for 'displayNames'
   void displayNamesHelper(int, int) const;
   //initializes adjacency matrix and TableType matrix
   void initialize();
   //utility function for 'removeNode' //clears values from TableType
   void clearTableType();
};
#endif
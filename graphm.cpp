
/* Aaron Parks
 * Prof. Carol Zander
 * CSS 343 : Winter 2010
 * Lab 3 - Part 1 : Dijkstra's Shortest Path Algorithm */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "graphm.h"

//------------------------------------------------------------------------------
//constructor
// - Instantiates Adjacency matrix (100x100) and instantiates 2D
//   TableType (100x100) by calling 'initialize' utility function.
//------------------------------------------------------------------------------
GraphM::GraphM() { initialize(); }

//------------------------------------------------------------------------------
//destructor
// - Necessary in order to delete strings.
//------------------------------------------------------------------------------
GraphM::~GraphM() { }

//------------------------------------------------------------------------------
//buildGraph
// - Adjacency Matrix
//   Will not allow zero or negatively numbered nodes or costs.  If negative
//   values are entered for nodes values, absolute value will be used.
//   If duplicate 'source' and 'destination' values are entered, cost will be
//   changed to newest value.
//   Will not allow for 'cost' of zero or less
//------------------------------------------------------------------------------
bool GraphM::buildGraph(ifstream& infile)
{
   int source = 0;                    //node where path starts
   int destination = 0;               //node where path ends
   int cost = 0;                      //cost of path from source to destination
   this->size = 0;                    //number of nodes in the graph
   
   //initialize adjacency matrix and TableType
   initialize();
   
   infile >> size;
   
   //check if size is too small or if at end of file
   if (size > 0 || !infile.eof())
   {
      //reads in node descriptions starting at 1
      for (int i = 0; i <= size; i++)
         data[i].setData(infile);
   }
   else
      return false;
  
   while (true)
   {
      //read in nodes and edges into adjacency matrix
      infile >> source >> destination >> cost;

      //terminate reading file //as per assignment instructions
      //will also catch on all zeros
      if (source != 0)
      {
         if (destination != 0 && cost != 0)
         {
            if (!insertEdge(source, destination, cost, true))
            {
               //error occurred! //edge insertion skipped!
               //normally, an exception would be thrown here
               continue;
            }
         }
      }
      else
         break;
   }
   return true;
}

//------------------------------------------------------------------------------
//findShortestPath
// - TableType 2D array
//   Will give values to the 'dist' data member of each struct based upon the
//   path information sorted in the adjacency matrix. Will continually check
//   for shorter paths via previously checked nodes. If a shorter path is found
//   will update the .dist of the current node, and change the path to represent
//   the node present in the new route.
//------------------------------------------------------------------------------
void GraphM::findShortestPath()
{
   //holder for node adjacent to source with smallest distance
   int v = 0;

   //row
   for (int source = 1; source <= size; source++)
   {
      for (int i = 1; i <= size-1; i++)
      {
         //determine T[source][x] with smallest .dist
         v = getMinNode(source);

         //v will be less than zero if only remaining values are MAX
         if (v > 0)
         {
            T[source][v].visited = true;

            //for all adjacent nodes //determine shortest distance
            for (int w = 1; w < size; w++)
            {
               if (C[v][w] != MAX)
               {
                  //adjust the shortest distance from source to w
                  //if going through v is shorter, set .path to v
                  if (T[source][w].visited == false)
                  {
                     if ((T[source][v].dist + C[v][w]) <= T[source][w].dist)
                     {
                        T[source][w].dist = (T[source][v].dist + C[v][w]);
                        T[source][w].path = v;
                     }
                  }
               }
            }
         }
      }
   }
}

//------------------------------------------------------------------------------
//insertEdge
// - Writes 'row', 'column' and 'cost' information into adjacency matrix.
//   Will account for the following cases:
//   -> row || col == 0
//   -> row || col < 0 (negative numbers)
//   -> val < 0 (negative number)
//   In the case that row and/or column equal zero, nothing inserted and false
//   returned.
//   In the case that row and/or column are negative, absolute values will be
//   used, val inserted, and true returned.
//   In the case of negative val, absolute value will be used
// - Assigns 'dist' value to appropriate location (row X col ) in TableType 2D
//   array.
// - Bool value in parameter acts a sentinal value for 'findShortestPath'.  If
//   the adjacency matrix and TableType.dist are being intialized from the data
//   file, 'findShortestPath' will not be called.  Otherwise, it will be.
//------------------------------------------------------------------------------
bool GraphM::insertEdge(int row, int col, int val, bool building)
{
   //initialize path from node to itself
   if (C[abs(row)][abs(row)] != 0)
   {
      C[abs(row)][abs(row)] = 0;
      T[abs(row)][abs(row)].dist = 0;
   }

   //only okay to insert val of zero if path is to same node
   if (abs(row) == abs(col) && val == 0)
   {
      C[abs(row)][abs(col)] = val;
      T[abs(row)][abs(col)].dist = val;
      return true;
   }
   //only okay to insert only if val does not equal zero
   else if (val != 0)
   {
      C[abs(row)][abs(col)] = abs(val);
      T[abs(row)][abs(col)].dist = abs(val);
      return true;
   }
   else
      return false;

   //will not call 'findShorestPath' if building matricies from data file
   if (!building)
      findShortestPath();
}

//------------------------------------------------------------------------------
//removeEdge
// - Checks if "row" and "col" are within the bounds of the adjacency matrix. If
//   they are not, nothing will be remove and false will be returned.
//   Checks specified node and node (row and column) in the adjacency matrix
//   and sets the value at that location to 'max'.  If value is already
//   'max', will do nothing and return.
//   Calls 'findShortestPath' function to re-calculate paths among the nodes
//------------------------------------------------------------------------------
bool GraphM::removeEdge(int row, int column)
{
   if (row > 0 && row < MAX_NODES && column > 0 && column < MAX_NODES)
   {
      if (C[row][column] != MAX)
      {
         //update value on adjacency matrix
         C[row][column] = MAX;
         //clear all values from TableType 2D array
         clearTableType();
         //re-fill TableType with updated adjacency matrix
         findShortestPath();
         return true;
      }
   }
   else
      return false;
}

//------------------------------------------------------------------------------
//displayAll
// - Displays the names of each node (location), the distance from each node. If
//   no distance exists between nodes, will output '---' and no path
//   information.  If path exists between two nodes, will output the combined
//   total of that path in the 'Dijkstra's' column and display the nodes along
//   the path.
//------------------------------------------------------------------------------
void GraphM::displayAll() const
{
   //set up column headings
   cout << "Description" << setw(23) << "FromNode";
   cout << setw(8) << "ToNode" << setw(13) << "Dijkstra's";
   cout << setw(8) << "Path" << endl;

   //loop to print data from TableType
   for (int row = 1; row <= size; row++)
   {
      cout << data[row] << endl;
      for (int column = 1; column <= size; column++)
      {
         if (row != column)
         {
            cout << setw(30) << row << setw(10) << column;

            if (T[row][column].dist < MAX)
            {
               cout << setw(10) << T[row][column].dist;
               cout << "         ";
               displayPath(row, column);
            }
            else
               cout << setw(11) << "---";

            cout << endl;
         }
      }
   }
   cout << "\n" << endl;
}

//------------------------------------------------------------------------------
//display
// - Displays information specific to the nodes (and the edge connecting them)
// - If edge between two nodes does not exist, cost and path will not be
//   printed.  If nodes are the same node, will display zero for the dist if an
//   edge exists between them, nothing otherwise.  No path information will be
//   displayed in this case.
//------------------------------------------------------------------------------
void GraphM::display(int row, int column) const
{
   //display inserted information
   cout << setw(5) << row << setw(8) << column;

   //check if path from 'start' to 'end' exists
   if (C[row][column] < MAX)
   {
      cout << setw(8) << T[row][column].dist << setw(10);
      displayPath(row, column);
      cout << endl;
      displayNames(row, column);
   }
   else
      cout << setw(9) << "---";

   cout << "\n" << endl;
}

//------------------------------------------------------------------------------
//displayPath & displayPathHelper
// - Used with 'displayAll()' and 'display(int,int)'
// - Recursively calls displayPathHelper to display the path betwene two nodes.
//   Because of the path information stored is for the node that points to the 
//   node with the path equal to the node it references, nodes will be traversed
//   then the paths will be printed.
//------------------------------------------------------------------------------
void GraphM::displayPath(int row, int column) const
{
   int nextCol = T[row][column].path;

   displayPathHelper(row, nextCol);

   cout << column;
}
//------------------------------------------------------------------------------
void GraphM::displayPathHelper(int row, int column) const
{
   int nextCol = T[row][column].path;

   if (nextCol == 0) //end of path
      cout << row << " ";
   else
   {
      displayPathHelper(row, nextCol);
      cout << column << " ";
   }
}

//------------------------------------------------------------------------------
//displayNames & displayNamesHelper
// - Displays the name of the calling row.
//------------------------------------------------------------------------------
void GraphM::displayNames(int row, int column) const
{
   if (row != column)
      displayNamesHelper(row, column);
}
//------------------------------------------------------------------------------
void GraphM::displayNamesHelper(int row, int column) const
{
   if (T[row][column].path != 0)
      displayNamesHelper(column, T[row][column].path);

   cout << data[T[row][column].path] << endl;
}

//------------------------------------------------------------------------------
//getMinNode
// - Checks all nodes in the parameter row in the adjacency matrix for smallest
//   value.  That values represents the shortest 'path' from the graph.  Then
//   will check if that node has been visited.  If visited == true, will
//   continue searching. Until next smallest is found.  If false, will apply the
//   value to 'smallest' and continue searching for a smaller value until the
//   end of the for loop.
//------------------------------------------------------------------------------
int GraphM::getMinNode(int row)
{
   //local variable that holds 'column' with the smallest path
   int smallCol = -1;
   //local variable that represents the shortest path among the nodes
   int shrtPath = MAX;

   for (int i = 1; i <= size; i++)
   {
      if (T[row][i].dist < shrtPath && T[row][i].visited == false)
      {
         shrtPath = T[row][i].dist;
         smallCol = i;
      }
   }
   return smallCol;
}

//------------------------------------------------------------------------------
//initialize
// - Checks if 'Cost' contains max values.  Will only initialize adjacency
//   matrix and 2D array if C[1][1] (first location used in adjacency matrix)
//   is not max.  A non-max value includes garbage memory and
//   legitimate values inserted previously. 
//------------------------------------------------------------------------------
void GraphM::initialize()
{
   //check if already clear
   if (C[1][1] != MAX)
   {
      for (int row = 0; row < MAX_NODES; row++)
      {
         for (int column = 0; column < MAX_NODES; column++)
         {
            C[row][column] = MAX;
            T[row][column].visited = false;
            T[row][column].dist = MAX;
            T[row][column].path = 0;
         }
      }
   }
}
//------------------------------------------------------------------------------
//clearTableType
// - Utility function for 'removeNode'.  Will reset all the values of TableType
//   so that there are no conflicts when values are reassigned in
//   'findShortestPath' function.
//------------------------------------------------------------------------------
void GraphM::clearTableType()
{
   for (int row = 0; row < MAX_NODES; row++)
   {
      for (int column = 0; column < MAX_NODES; column++)
      {
         T[row][column].visited = false;
         T[row][column].dist = MAX;
         T[row][column].path = 0;
      }
   }
}
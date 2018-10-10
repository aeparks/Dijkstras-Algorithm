
/* Aaron Parks
 * Prof. Carol Zander
 * CSS 343 : Winter 2010
 * Lab 3 - Part 2 : Dijkstra's Algorithm-depthFirstSearch */
 
#include <iostream>
#include <fstream>
#include <iomanip>
#include "graphl.h"

//------------------------------------------------------------------------------
//constructor
// - Initializes 'graphArray' by setting all 'edgeHeads' to NULL and all
//   visited values to 'false'.
//------------------------------------------------------------------------------
GraphL::GraphL()
{
   //initialize graphArray
   for (int i = 0; i < MAX_NODES; i++)
   {
      graphArray[i].edgeHead = NULL;
      graphArray[i].visited = false;
   }
}

//------------------------------------------------------------------------------
//destructor
// - Deletes the dynamically allocated memory that was allocated in during
//   'insertEdge' function.  Deletion performed by using utility function
//   'makeEmpty'.
//------------------------------------------------------------------------------
GraphL::~GraphL()
{
   this->makeEmpty();
}

//------------------------------------------------------------------------------
//buildList
// - Array of GraphNodes
//   GraphNodes have pointers to 'EdgeNode' objects.  As the file is read, the
//   GraphNode at the index of the first value will be set to point to a new
//   EdgeNode created with the second value on the line.
//   When '0 0' or any negative value, buildList will exit.
//------------------------------------------------------------------------------
bool GraphL::buildGraph(ifstream& infile)
{
   int source = 0;                    //node where path starts
   int destination = 0;               //node where path ends
   this->size = 0;                    //number of nodes in the graph
   
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
      //read in edges
      infile >> source >> destination;

      //terminate reading if attempt is made to read zero or negative node
      if (source <= 0 || destination <= 0)
         break;
      else
      {
         if (!insertEdge(source, destination))
         {
            //error occurred! //EdgeNode not inserted
            //normally, an exception would be thrown here
            continue;
         }
      }
   }
   return true;
}

//------------------------------------------------------------------------------
//insertEdge
// - Finds location in array at index 'index', creates a new EdgeNode with the
//   int value set to 'edgeTo'.  Inserts at the front of linked list.
//   Note: will not check for duplicate values (that is, multiple instances of
//   an edge from a single node to the same node.
//------------------------------------------------------------------------------
bool GraphL::insertEdge(int index, int edgeTo)
{
   //create new EdgeNode and initialize it
   EdgeNode* newNode = new EdgeNode;

   newNode->adjGraphNode = edgeTo;
   //newNode->visited = false;
   newNode->nextEdge = NULL;

   //insert into array
   //list is empty
   if (graphArray[index].edgeHead == NULL)
      graphArray[index].edgeHead = newNode;
   //list has at least one EdgeNode //insert in front
   else if (graphArray[index].edgeHead != NULL)
   {
      newNode->nextEdge = graphArray[index].edgeHead;
      graphArray[index].edgeHead = newNode;
   }
   else  //something went horribly wrong
   {
      delete newNode;
      return false;
   }
   return true; 
}

//------------------------------------------------------------------------------
//displayGraph
// - Displays all information about the graph including node numbers and their
//   names (node number is determined by which order it was read from the
//   external file), and all edges from that node.
//------------------------------------------------------------------------------
void GraphL::displayGraph() const
{
   //temporary holder for current EdgeNode being operated on
   EdgeNode* current;

   cout << "Graph: \n";
   for (int i = 1; i <= size; i++)
   {
      if (graphArray[i].edgeHead != NULL)
      {
         cout << "Node " << i;
         cout << "        " << data[i] << "\n";

         current = graphArray[i].edgeHead;

         while (current != NULL)
         {
            cout << setw(8) << "edge " << i << " ";
            cout << current->adjGraphNode << "\n";
            current = current->nextEdge;
         }  
      }
   }
   cout << endl;
}

//------------------------------------------------------------------------------
//depthFirstSearch
// - Traveses the 'graphArray' array by walking linked lists at a given index
//   or by indexing into another linked list via an adjacent-representing node.
//------------------------------------------------------------------------------
void GraphL::depthFirstSearch()
{
   cout << "Depth-first ordering: ";
   for (int i = 1 ; i <= size; i++)
   {
      if (graphArray[i].edgeHead != NULL && graphArray[i].visited == false)
         depthFirstSearch(i);
   }
   cout << "\n" << endl;
}
//------------------------------------------------------------------------------
void GraphL::depthFirstSearch(int v)
{
   //pointer used to walk linked list
   EdgeNode* current = NULL;

   graphArray[v].visited = true;
   cout << v << " ";

   current = graphArray[v].edgeHead;
   while (current != NULL)
   {
      if (graphArray[current->adjGraphNode].visited == false)
         depthFirstSearch(current->adjGraphNode);
      else
         current = current->nextEdge;
   }
}

//------------------------------------------------------------------------------
//makeEmpty & makeEmpty (overloaded)
// - Deletes all dynamically allocated memory being pointed at from
//   'graphArray'.  Deletion occurs using recursive calls to overloaded
//   'makeEmpty' function.
//------------------------------------------------------------------------------
void GraphL::makeEmpty()
{
   for (int i = 1; i <= size; i++)
   {
      if (graphArray[i].edgeHead != NULL)
         makeEmpty(graphArray[i].edgeHead);

      //all nodes cleared from linked list //set pointer to NULL
      graphArray[i].edgeHead = NULL;
   }
}
//------------------------------------------------------------------------------
void GraphL::makeEmpty(EdgeNode* current)
{
   if (current->nextEdge != NULL)
      makeEmpty(current->nextEdge);

   delete current;
   current = NULL;
}

/* Aaron Parks
 * Prof. Carol Zander
 * CSS 343 : Winter 2010
 * Lab 3 - Part 2 : Dijkstra's Algorithm-depthFirstSearch */
 
/*--- GraphL Class -------------------------------------------------------------
 * GraphL is built around the 'depthFirstSearch' function for a graph. GraphL
 * contains the necessary functions required to build a graph from an external
 * data file, create an array of linked lists of the edges read in from that
 * data file, and to perform a depthFirstSearch using those linked lists to
 * perform the search.
 *
 *--- Assumptions --------------------------------------------------------------
 * - NodeData
 *   -> nodeData member functions are implemented correctly
 *   -> strings no longer than 50 characters will be inserted
 * - buildGraph
 *   -> the external text file is formatted correctly
 *   -> will exit if size read in is less than zero
 *   -> will exit upon reading '0 X', '0 X', or '0 0'
 * - insertEdge
 *   -> will not insert an EdgeNode that has either negative index reference or
 *      negative graph node reference
 *   -> the order in which the nodes are appended to the linked list does not
 *      matter
 * - General
 *   -> number of nodes will not exceed MAX_NODES
 *   -> index 0 of 'graphArray' will never be used
 *----------------------------------------------------------------------------*/

#ifndef GRAPHL_H
#define GRAPHL_H
#include <iostream>
#include "nodedata.h"
#include "graphm.h"
using namespace std;

struct EdgeNode;           //forward reference for the compiler
struct GraphNode
{
   EdgeNode* edgeHead;     //head of the list of edges
   bool visited;           //has list been visited previously
};

struct EdgeNode
{
   int adjGraphNode;       //subscript of the adjacent graph node
   EdgeNode* nextEdge;     //pointer to next node in list
};

class GraphL
{
public:
   //constructor
   GraphL();
   //destructor
   ~GraphL();

   //uses an external file to populate an array of pointers to linked lists
   bool buildGraph(ifstream&);
   //displays all the nodes stored in the 'graphArray'
   void displayGraph() const;
   //performs a 'depthFirstSearch' on the data stored in the 'graphArray'
   void depthFirstSearch();

private:
   NodeData data[MAX_NODES];         //string description for graph nodes
   GraphNode graphArray[MAX_NODES];  //array of GraphNodes w/ ptrs to EdgeNodes 
   int size;                         //the number of Nodes in the graph

   //utility function for 'buildGraph'
   bool insertEdge(int, int);
   //helper function for 'depthFirstSearch'
   void depthFirstSearch(int);
   //utility function for 'destructor'
   void makeEmpty();
   //helper function for 'makeEmpty'
   void makeEmpty(EdgeNode*);
};
#endif
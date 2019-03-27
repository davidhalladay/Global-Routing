/**************************************************************************
 * File       [ router.h ]
 * Author     [ Wan Cyuan Fan ]
/**************************************************************************/
#ifndef ROUTER_H
#define ROUTER_H

#include <vector>
#include <fstream>
#include <string>
#include <utility> // for pair
#include <climits>
#include <math.h>
#include <iostream>

using namespace std;

//Global type define
typedef pair<pair<int,int>,pair<int,int>> r_edge;

struct tile{
   float d;
   pair<int,int> coord_now;
   pair<int,int> coord_from;
   bool visit;
};

struct coor_pair{
   pair<int,int> t1;
   pair<int,int> t2;
};
//Global func
static bool comp_dis(tile* a, tile* b){ return a->d < b->d;}
static float edge_cost(int x,int c){ return pow(10.0,float(x)/c) + 2.0*float(x)/c;}
//return pow(10.0,float(x)/c) + 2.0*float(x)/c;
//Graph class
class graph
{
public:
   graph (){ }
   virtual ~graph (){ }
   //set initial
   void set_capacity(const int cap){ capacity = cap; }
   void set_netNum(const int num){ netNum = num; }
   void set_row_col(const int r,const int c){ row = r; col = c; }
   void set_graph(const int,const int);
   void set_gr_pair(const int,const int,const int,const int,const int);
   //Dijkstra's Alogrithm
   void Dijkstra();
   void initialize_single_source();
   tile* Extract_Min(vector<tile*>);
   void relax(tile*,tile*);
   float get_edge(tile* ,tile* );
   //save the path
   void store_path();
   //fileopen
   void setfile(const char*);
   void writefile();
   void writefile_scout();

private:
   //graph vari.
   vector<vector<tile>> grid;   //store the vertex
   vector<vector<int>> edge_y;   //store the vertical edge weight
   vector<vector<int>> edge_x;   //store the horizontal edge weight
   //parameter vari.
   int capacity;
	int netNum;
   int count = 0;
	int row, col;
   //Dijkstra's Alogrithm parameter
   vector<tile*> Q;
   //path storage
   vector<int> gr_pair;
   vector<coor_pair> gr_path;
   //file
   fstream myfile;

};

#endif

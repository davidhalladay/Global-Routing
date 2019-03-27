/**************************************************************************
 * File       [ router.cpp ]
 * Author     [ Wan Cyuan Fan ]
 * Synopsis   [ demonstration for the usage of parser.h ]
 * Usage      [ ./parser [inputfileName] ]
/**************************************************************************/
#include <vector>
#include <algorithm>
#include <queue>
#include "router.h"


void
graph::set_graph(const int row,const int col)
{
   //resize grid and equip tile
   grid.resize(row);
   for (size_t i = 0; i < row; ++i) {
		grid[i].resize(col);
	}
   for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			grid[i].push_back(tile());
		}
	}
   //initialize the tile
   for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			grid[i][j].coord_now = make_pair(i,j);
         grid[i][j].visit = false;
		}
	}
   //initialize the edge
   edge_x.resize(col-1);
	for (int i = 0; i < col-1; ++i) {
		edge_x[i].resize(row);
	}
	edge_y.resize(row);
	for (int i = 0; i < row; ++i) {
		edge_y[i].resize(col-1);
	}
   for (int i = 0; i < col-1; ++i) {
		for (int j = 0; j < row; ++j) {
			edge_x[i][j] = 0;
		}
	}
   for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col-1; ++j) {
			edge_y[i][j] = 0;
		}
	}
}

void
graph::set_gr_pair(const int n,const int x1,const int y1,const int x2,const int y2){
   gr_pair.clear();
   gr_pair.push_back(n);
   gr_pair.push_back(x1);
   gr_pair.push_back(y1);
   gr_pair.push_back(x2);
   gr_pair.push_back(y2);
}


//-----------------------------------------------//
//            Dijkstra's algorithm
//-----------------------------------------------//
void
graph::Dijkstra(){
   initialize_single_source(); // include Q = G.V
   while (!Q.empty()) {
		tile* u = Extract_Min(Q);
      u->visit = true;
		if (u->coord_now.first - 1 >= 0) {
			relax(&grid[u->coord_now.first][u->coord_now.second], &grid[u->coord_now.first-1][u->coord_now.second]);
		}

		if (u->coord_now.second + 1 < row) {
			relax(&grid[u->coord_now.first][u->coord_now.second], &grid[u->coord_now.first][u->coord_now.second+1]);
		}

		if (u->coord_now.second - 1 >= 0) {
			relax(&grid[u->coord_now.first][u->coord_now.second], &grid[u->coord_now.first][u->coord_now.second-1]);
		}

		if (u->coord_now.first + 1 < col) {
			relax(&grid[u->coord_now.first][u->coord_now.second], &grid[u->coord_now.first +1][u->coord_now.second]);
		}
	}

}

void
graph::initialize_single_source(){
   for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
         grid[i][j].d = INT_MAX;
         Q.push_back(&grid[i][j]);
         grid[i][j].coord_from = make_pair(NAN,NAN);
		}
	}
   grid[gr_pair[1]][gr_pair[2]].d = 0;
}

tile*
graph::Extract_Min(vector<tile*>){
   tile* min;
	std::sort(Q.begin(), Q.end(), comp_dis);
	min = Q.front();
	Q.erase(Q.begin());
	return min;
}

void
graph::relax(tile* u,tile* v){
   float weight = get_edge(u, v);
   if (v->d > u->d + weight) {
		v->d = u->d + weight;
      int x = u->coord_now.first;
      int y = u->coord_now.second;
		v->coord_from = make_pair(x,y);
	}
}

float
graph::get_edge(tile* u,tile* v){
   int demand;
   //y
   if(u->coord_now.first == v->coord_now.first){
      if(u->coord_now.second < v->coord_now.second){
         demand = edge_y[u->coord_now.first][u->coord_now.second];
      }
      else{
         demand = edge_y[u->coord_now.first][v->coord_now.second];
      }
   }
   //x
   else{
      if(u->coord_now.first < v->coord_now.first){
         demand = edge_x[u->coord_now.first][u->coord_now.second];
      }
      else{
         demand = edge_x[v->coord_now.first][u->coord_now.second];
      }
   }
   return edge_cost(demand,capacity);
}

//-----------------------------------------------//
//                   store_path
//-----------------------------------------------//
void
graph::store_path(){
   int end_x = gr_pair[3];
   int end_y = gr_pair[4];
   int curr_x, curr_y;
   count = 0 ;
   curr_x = end_x;
   curr_y = end_y;

   while (1) {
   	int x1 = grid[curr_x][curr_y].coord_now.first;
   	int y1 = grid[curr_x][curr_y].coord_now.second;
   	int x2 = grid[curr_x][curr_y].coord_from.first;
   	int y2 = grid[curr_x][curr_y].coord_from.second;
      coor_pair tmp_pair;
      tmp_pair.t1 = make_pair(x1,y1);
      tmp_pair.t2 = make_pair(x2,y2);

      //update the edge_x,edge_y
      //y
      if(tmp_pair.t1.first == tmp_pair.t2.first){
         if(tmp_pair.t1.second < tmp_pair.t2.second){
            edge_y[tmp_pair.t1.first][tmp_pair.t1.second]++;
         }
         else{
            edge_y[tmp_pair.t1.first][tmp_pair.t2.second]++;
         }
      }
      //x
      else{
         if(tmp_pair.t1.first < tmp_pair.t2.first){
            edge_x[tmp_pair.t1.first][tmp_pair.t1.second]++;
         }
         else{
            edge_x[tmp_pair.t2.first][tmp_pair.t1.second]++;
         }
      }
      //gr_path store
      count++;
   	gr_path.push_back(tmp_pair);
   	curr_x = x2;
   	curr_y = y2;
   	if (curr_x == gr_pair[1] && curr_y == gr_pair[2])
   		break;
   	}

}

void
graph::setfile(const char* filename){
	myfile.open(filename, fstream::out);
	if(!myfile.is_open())
	{
	    cerr << "Error: Can't create the file..." << endl;
	}
}

void
graph::writefile(){
   myfile << gr_pair[0] << " " << count << endl;

	while(!gr_path.empty()) {
      pair<int,int> s1 = gr_path.back().t1;
      pair<int,int> s2 = gr_path.back().t2;
      gr_path.pop_back();
		myfile << s2.first << " " << s2.second << " ";
		myfile << s1.first << " " << s1.second << endl;
	}
}

void
graph::writefile_scout(){
   for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
         myfile << "pt ";
         myfile << grid[i][j].coord_now.first << " " << grid[i][j].coord_now.second << " ";
         myfile << "black 0" << endl;
		}
	}

	while(!gr_path.empty()) {
      pair<int,int> s1 = gr_path.back().t1;
      pair<int,int> s2 = gr_path.back().t2;
      gr_path.pop_back();
      myfile << "line ";
		myfile << s2.first << " " << s2.second << " ";
		myfile << s1.first << " " << s1.second ;
      myfile << " red" << endl;
	}
}

#ifndef _DEFINE_PARSER_
#define _DEFINE_PARSER_

#include <string>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <fstream>

using namespace std;

class AlgParser
{
  public:
    AlgParser(void){}

    // specify the parsing file name and then parse the file
    bool read( char* inputFileName );

    // return # of tiles in horizontal direction
    int gNumHTiles(){ return numHTilesm; }

    // return # of tiles in vertical direction
    int gNumVTiles(){ return numVTilesm; }

    // return the capacity of each tile edge
    int gCapacity(){ return capacity; }

    // return # of nets
    int gNumNets(){ return numNets; }

    // return the starting x and y position for the net
    pair<int,int> gNetStart( int id ){ return netsPos[ id ].first; }

    // return the ending x and y position for the net
    pair<int,int> gNetEnd( int id ){ return netsPos[ id ].second; }

  private:
    int numHTilesm, numVTilesm, capacity, numNets;
    typedef pair<int,int> Pos;
    typedef pair<Pos,Pos> NetPos;
    vector<NetPos> netsPos;
};

class AlgTimer
{
  public:
    AlgTimer(void){}

    // Strat the timer
	void Begin(void);

    // Return the accumulated time in seconds
	double End(void);

  private:
    long begin_clock;
};

#endif

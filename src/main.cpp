/**************************************************************************
 * File       [ main.cpp ]
 * Author     [ Wan Cyuan Fan ]
 * Synopsis   [ demonstration for the usage of parser.h ]
 * Usage      [ ./parser [inputfileName] ]
/**************************************************************************/

#include "parser.h"
#include "router.h"

int main(int argc, char **argv)
{
   if( argc <= 2 ){ cout << "Usage: ./router [input_file_name] [output_file_name]" << endl; return 1; }

   AlgParser parser;
   graph router_graph;

   // read the file in the first argument
   if( ! parser.read( argv[1] ) ) { return 1; }

   // show the information of the input
   cout << "Start loading data..." << endl;
   cout << "grid " << parser.gNumHTiles() << " " << parser.gNumVTiles() << endl;
   cout << "capacity " << parser.gCapacity() << endl;
   cout << "num net " << parser.gNumNets() << endl;
   for (int idNet = 0; idNet < parser.gNumNets(); ++idNet){
      pair<int, int> posS = parser.gNetStart( idNet );
      pair<int, int> posE = parser.gNetEnd( idNet );
      cout << idNet << " " << posS.first << " " << posS.second << " "
                             << posE.first << " " << posE.second << endl;
   }

	cout << "----------------------" << endl;
	cout << "-- Complete parsing --" << endl;
	cout << "----------------------" << endl;

   cout << "@ Start routing data..." << endl;
   cout << "@ Start setting data..." << endl;
   router_graph.set_row_col(parser.gNumHTiles(),parser.gNumVTiles());
   router_graph.set_capacity(parser.gCapacity());
   router_graph.set_netNum(parser.gNumNets());
   cout << "@ Setting data successed..." << endl;
   cout << "@ Start graph..." << endl;
   router_graph.set_graph(parser.gNumHTiles(),parser.gNumVTiles());
   cout << "@ Setting graph successed..." << endl;
   router_graph.setfile(argv[2]);
   cout << "@ Start routing..." << endl;
   for (int idNet = 0; idNet < parser.gNumNets(); ++idNet){
      pair<int, int> posS = parser.gNetStart( idNet );
      pair<int, int> posE = parser.gNetEnd( idNet );
      router_graph.set_gr_pair(idNet,posS.first,posS.second,posE.first,posE.second);
      router_graph.Dijkstra();
      router_graph.store_path();
      router_graph.writefile();
   }

   return 0;
}

//

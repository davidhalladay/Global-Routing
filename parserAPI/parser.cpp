#include "parser.h"
#include <ctime>

bool AlgParser::read(char *inputFileName)
{
    ifstream infile( inputFileName );
    if (!infile) {
        cout << "Incorrect [input_file_name]: " << inputFileName << endl;
        cout << "Usage: ./parser [input_file_name]" << endl;
        return false;
    }

    string s, buf;
    while( infile >> s ){
        if( s == "grid" ){ infile >> numHTilesm >> numVTilesm; }
        else if( s == "capacity" ){ infile >> capacity; }
        else if( s == "num" ){ infile >> buf >> numNets; break; }
        else { cout << s << " does not follow the rule" << endl; break; }
    }
    netsPos.resize( numNets );
    for( size_t i = 0; i < numNets; ++i ){
        int id, sx, sy, ex, ey;
        infile >> id >> sx >> sy >> ex >> ey;
        Pos sPos = pair<int,int>(sx,sy);
        Pos ePos = pair<int,int>(ex,ey);
        netsPos[ id ] = pair<Pos,Pos>(sPos,ePos);
    }
    infile.close();
	cout << "file parsed completely." << endl;
	return true;
}

void AlgTimer::Begin(void)
{
    begin_clock = clock();
}

double AlgTimer::End(void)
{
    return ( (double)( clock() - begin_clock ) / (double)CLOCKS_PER_SEC );
}

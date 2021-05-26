#include <fstream>
#include <graph/graphalg.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


int nmain(int argv, const char* arg[]) {
	ifstream inp;
	ofstream out;
	int nodeBeging,nodeEnd;
	int mode=2;
	nodeBeging=-1;
	nodeEnd=-1;
	for(int i=1;i<argv;++i) {
		string t=arg[i];
		try {
			if(t=="-i") {
				i++;
				if(i>=argv) throw string("no argument for -i");
				string tt=arg[i];
				inp.open(tt,ifstream::in);
				if(!inp.is_open()|| inp.bad()) {
					throw string("File not found");
				}
				
				continue;
			}
			else if(t=="-o") {
				i++;
				if(i>=argv) throw string("no argument for -o");
				string tt=arg[i];
				out.open(tt,ofstream::out);
				continue;
			}
			else if(t=="-m") {
				++i;
				if(i>=argv) throw string("no argument for -m");
				string tt=arg[i];
				if(tt=="sp") {
					mode =0;
				} else if(tt=="lp") {
					mode=1;
				} else if(tt=="cp") {
					mode =2;
				} else throw "invalid argument for -m, expected [sp, lp, cp], found "+tt;
				continue;
			}
			
			int g=stoi(t);
			if(nodeBeging==-1) {
				nodeBeging=g;
				continue;
			}
			else if(nodeEnd==-1) {
				nodeEnd=g;
				continue;
			}
			else throw "too much arguments ("+t+")";
			
			
		} catch(invalid_argument &e) {
			cout << "what is "+t+"?"<<endl;
			return 0;
		} catch(string &e) {
			cout << e << endl;
			return 0;
		} catch(exception &e) {
			cout << e.what() << endl;
		} 
		
		
	}
	
	nodeBeging--;
	nodeEnd--;
	
	if(!(nodeBeging>=0 && nodeEnd>=0)) {
		cout << "no argument for begin node or end node" << endl;
		return 0;
	}
	
	if(inp.is_open())
		cin.rdbuf(inp.rdbuf());
	
	
	
	int nodeCount, edgeCount;
	if(!(cin >> nodeCount >> edgeCount)) {
		cout << "count of verticies and edge must be number\n";
		return 0;
	}
	
	if(nodeCount<=nodeBeging || nodeCount <=nodeEnd) {
		cout << "begin node or end node is not in range\n";
		return 0;
	}
	
	vector<vector<int> > g(nodeCount, vector<int>(nodeCount,-1));
	for (int i = 0; i < edgeCount; ++i) {
	    int a, b, w;
	    if (!(cin >> a >> b >> w)) {
	      cout << "parameters of each edge must be follow this pattern: [(from "
	              "verticy) (to verticy) (weight)] all must be number\n";
	      return 0;
	    }
	    if (!((a > 0 && a <= nodeCount) && (b > 0 && b <= nodeCount))) {
	      cout << "information about edges is iscorrect\n";
	      return 0;
	    }
	    g[a - 1][b - 1] = w;
  	}
	if(inp.is_open()) inp.close();
	
	auto streambuf=cout.rdbuf();
	if(out.is_open())
		streambuf=out.rdbuf();
	ostream baseout(streambuf);
	
	/*cout << endl;
	for(int i=0;i<nodeCount;++i) {
		for(int j=0;j<nodeCount; ++j)
			baseout << g[i][j] <<" ";
		baseout << endl;
	}*/

  cout << endl;
  for (int i = 0; i < nodeCount; ++i) {
    for (int j = 0; j < nodeCount; ++j)
      baseout << g[i][j] << " ";
    baseout << endl;
  }

  response res;

  switch (mode) {
  	case 0:
    	res = calcShortestPath(g, nodeCount, nodeBeging, nodeEnd);
    	break;
  	case 1:
    	break;
  	case 2:
  		res = calcCountPaths(g, nodeCount, nodeBeging, nodeEnd);
    	break;
  }
	if(res.code==0) {
		baseout << res.answer << endl;
	}
	else {
		baseout << res.message << endl;
	}

	if (out.is_open())
		out.close();
	return 0;
}

#ifndef _MTEST
int main(int argv, const char* arg[]) {
	
	nmain(argv,arg);
}
#endif

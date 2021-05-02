#include <graphalg.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;



int main(int argv, char* arg[]) {
	
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
	
	if(inp.is_open())
		cin.rdbuf(inp.rdbuf());
	
	
	
	int nodeCount, edgeCount;
	if(!(cin >> nodeCount >> edgeCount)) {
		cout << "count of verticies and edge must be number\n";
		return 0;
	}
	vector<vector<int> > g(nodeCount, vector<int>(nodeCount,-1));
	for(int i=0;i<edgeCount;++i) {
		int a,b,w;
		if(!(cin >> a >> b >> w)) {
			cout << "parameters of each edge must be follow this pattern: [(from verticy) (to verticy) (weight)] all must be number\n";
			return 0;
		}
		g[a-1][b-1]=w;
	}
	if(inp.is_open()) inp.close();
	
	auto streambuf=cout.rdbuf();
	if(out.is_open())
		streambuf=out.rdbuf();
	ostream baseout(streambuf);
	
	cout << endl;
	for(int i=0;i<nodeCount;++i) {
		for(int j=0;j<nodeCount; ++j)
			baseout << g[i][j] <<" ";
		baseout << endl;
	}
	switch(mode) {
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
	}
	if(out.is_open()) out.close();
	return 0;
}

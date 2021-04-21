//#include <graphtask/graphalg.h>
#include "graphalg.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

int main(int argv, char* arg[]) {
	vector<vector<int> > g;
	ifstream inp;
	ofstream out;
	int a,b;
	int mode=2;
	a=-1;
	b=-1;
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
			if(a==-1) {
				a=g;
				continue;
			}
			else if(b==-1) {
				b=g;
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
	while(!inp.eof()) {
		string t;
		inp >> t;
		cout << t << endl;
	}
	if(inp.is_open()) inp.close();
	if(out.is_open()) out.close();
	return 0;
}

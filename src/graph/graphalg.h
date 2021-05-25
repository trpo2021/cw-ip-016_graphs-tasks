#pragma once

#include <vector>


struct response {
	int code;		//Response code
	int answer;		//Answer of calculations
	char* message;	//Message about response
};

response calcCountPaths(std::vector<std::vector<int> > g, int n, int fromNode, int toNode);
response calcShortestPath(std::vector<std::vector<int> > g, int n, int fromNode, int toNode);
response calcLongestPath(std::vector<std::vector<int> > g, int n, int fromNode, int toNode);
bool aCycleGraph(std::vector<std::vector<int> > g, int n, int fromNode);

//g - info about edges of graph
//n - count of vertices
//fromNode - index of Node, where start calculations
//toNode - index of Node, where end calculations

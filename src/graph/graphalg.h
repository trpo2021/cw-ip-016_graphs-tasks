#pragma once

#include <vector>
#include <string>


struct response {
	int code;		//Response code
	int answer;		//Answer of calculations
	std::string message;	//Message about response
};

response calcCountPaths(std::vector<std::vector<int> > g, int n, int fromNode, int toNode);
response calcShortestPath(std::vector<std::vector<int> > g, int n, int fromNode, int toNode);
response calcLongestPath(std::vector<std::vector<int> > g, int n, int fromNode, int toNode);
bool aCycleGraph(std::vector<std::vector<int> > g, int n, int fromNode, int toNode);
void clearNonPath(std::vector<std::vector<int> > &g, int n, int fromNode, int toNode);

//g - info about edges of graph
//n - count of vertices
//fromNode - index of Node, where start calculations
//toNode - index of Node, where end calculations

#include <test/ctest.h>
#include <graph/graphalg.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <string>

extern std::string mPath;

int nmain(int argv, const char* arg[]);

CTEST_DATA(suite) {
	std::ifstream f;
	std::stringstream ss;
};

CTEST_SETUP(suite) {
	data->f.open(mPath+"tests/suite.test");
	
	std::cin.rdbuf(data->f.rdbuf());
	std::cout.rdbuf(data->ss.rdbuf());
}

CTEST_TEARDOWN(suite) {
	std::cin.rdbuf(data->f.rdbuf());
	std::cout.rdbuf(data->ss.rdbuf());
	data->f.close();
}


CTEST2(suite, test1) {
	data->f.good();
	const char *args[] = {mPath.c_str(),"4","5","-m","sp"};
	const std::string result="6\n";
	nmain(5,args);
	std::string a=data->ss.str();
	ASSERT_STR(result.c_str(), a.c_str());
}


CTEST2(suite, test2) {
	data->f.good();
	const char *args[] = {mPath.c_str(),"4","5","-m"};
	const std::string result="no argument for -m\n";
	nmain(4,args);
	std::string a=data->ss.str();
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST2(suite, test3) {
	data->f.good();
	const char *args[] = {mPath.c_str(),"4","5","-m","bb"};
	const std::string result="invalid argument for -m, expected [sp, lp, cp], found bb\n";
	nmain(5,args);
	std::string a=data->ss.str();
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST2(suite, test4) {
	data->f.good();
	const char *args[] = {mPath.c_str(),"4","5","-i"};
	const std::string result="no argument for -i\n";
	nmain(4,args);
	std::string a=data->ss.str();
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST2(suite, test5) {
	data->f.good();
	const char *args[] = {mPath.c_str(),"4","5","-o"};
	const std::string result="no argument for -o\n";
	nmain(4,args);
	std::string a=data->ss.str();
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST2(suite, test6) {
	data->f.good();
	const char *args[] = {mPath.c_str(),"4","5","6"};
	const std::string result="too much arguments (6)\n";
	nmain(4,args);
	std::string a=data->ss.str();
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST2(suite, test7) {
	data->f.good();
	const char *args[] = {mPath.c_str(),"4","5","boba"};
	const std::string result="what is boba?\n";
	nmain(4,args);
	std::string a=data->ss.str();
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST2(suite, test8) {
	data->f.good();
	const char *args[] = {mPath.c_str(),"4","5","-i","not/found/file.txt"};
	const std::string result="File not found\n";
	nmain(5,args);
	std::string a=data->ss.str();
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST2(suite, test9) {
	data->f.good();
	const char *args[] = {mPath.c_str(),"4","-m","sp"};
	const std::string result="no argument for begin node or end node\n";
	nmain(4,args);
	std::string a=data->ss.str();
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST2(suite, test10) {
	data->f.good();
	const char *args[] = {mPath.c_str(),"1","20"};
	const std::string result="begin node or end node is not in range\n";
	nmain(3,args);
	std::string a=data->ss.str();
	ASSERT_STR(result.c_str(), a.c_str());
}




CTEST(cycle, test1) {
	std::string p=mPath+"tests/cycle.test";
	std::string po=mPath+"tests/out";
	const char *args[] = {mPath.c_str(),"1","6","-m","cp","-i",p.c_str(),"-o",po.c_str()};
	nmain(9,args);
	std::ifstream f(po);
	std::string result="loop";
	std::string a="";
	if(f.is_open()) {
		f >> a;
		f.close();
		std::remove(po.c_str());
	}
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST_DATA(serr) {
	std::stringstream ss;
};

CTEST_SETUP(serr) {
	std::cout.rdbuf(data->ss.rdbuf());
}

CTEST_TEARDOWN(serr) {
	std::cout.rdbuf(data->ss.rdbuf());
}

CTEST2(serr, test1) {
	std::string p=mPath+"tests/incorrect.test";
	
	const char *args[] = {mPath.c_str(),"1","4","-m","cp","-i",p.c_str()};
	nmain(7,args);
	std::string result="information about edges is iscorrect\n";
	std::string a="";
	a=data->ss.str();
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST2(serr, test2) {
	std::string p=mPath+"tests/incorvert.test";
	
	const char *args[] = {mPath.c_str(),"1","4","-m","cp","-i",p.c_str()};
	nmain(7,args);
	std::string result="count of verticies and edge must be number\n";
	std::string a="";
	a=data->ss.str();
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST2(serr, test3) {
	std::string p=mPath+"tests/incoredge.test";
	
	const char *args[] = {mPath.c_str(),"1","4","-m","cp","-i",p.c_str()};
	nmain(7,args);
	std::string result="parameters of each edge must be follow this pattern: [(from "
	              "verticy) (to verticy) (weight)] all must be number\n";
	std::string a="";
	a=data->ss.str();
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST(calc, shortest) {
	const int n=4;
	std::vector<std::vector<int> > g = {
	{-1,3,2,-1},
	{-1,-1,2,-1},
	{-1,-1,-1,1},
	{-1,1,-1,-1}
	};
	response res=calcShortestPath(g,n,0,3);
	ASSERT_EQUAL(res.code, 0);
	ASSERT_EQUAL(res.answer, 3);
}

CTEST(calc, shortest2) {
	const int n=4;
	std::vector<std::vector<int> > g = {
	{-1,3,2,-1},
	{-1,-1,2,-1},
	{-1,-1,-1,-1},
	{-1,1,-1,-1}
	};
	response res=calcShortestPath(g,n,0,3);
	std::string result = "No path";
	ASSERT_EQUAL(res.code, 1);
	ASSERT_STR(res.message.c_str(),result.c_str());
}

CTEST(calc, shortest3) {
	const int n=6;
	std::vector<std::vector<int> > g = {
	{-1, 13, 6, 7, -1, -1 },
	{13, -1, -1, -1, -1, 10},
	{6, -1, -1, 20, 1, -1 }, 
	{7, 9, 20, -1, 13, 12},
	{-1, -1, 1, 13, -1, 4},
	{-1, 10, -1, 12, 4, -1} 
	};
	response res=calcShortestPath(g,n,0,4);
	ASSERT_EQUAL(0, res.code);
	ASSERT_EQUAL(7, res.answer);
}

CTEST(calc, shortest4) {
	const int n=6;
	std::vector<std::vector<int> > g = {
	{-1, 13, 6, 7, -1, -1 },
	{13, -1, -1, -1, -1, 10},
	{6, -1, -1, 20, 1, -1 }, 
	{7, 9, 20, -1, 13, 12},
	{-1, -1, 1, 13, -1, 4},
	{-1, 10, -1, 12, 4, -1} 
	};
	response res=calcShortestPath(g,n,4,1);
	ASSERT_EQUAL(0, res.code);
	ASSERT_EQUAL(14, res.answer);
}

CTEST(calc, shortest5) {
	const int n=6;
	std::vector<std::vector<int> > g = {
	{-1, 13, 6, 7, -1, -1 },
	{13, -1, -1, -1, -1, 10},
	{6, -1, -1, 20, 1, -1 }, 
	{7, 9, 20, -1, 13, 12},
	{-1, -1, 1, 13, -1, 4},
	{-1, 10, -1, 12, 4, -1} 
	};
	response res=calcShortestPath(g,n,3,2);
	ASSERT_EQUAL(0, res.code);
	ASSERT_EQUAL(13, res.answer);
}


CTEST(calc, longest1) {
	const int n=6;
	std::vector<std::vector<int> > g = {
	{-1, 13, 6, 7, -1, -1 },
	{13, -1, -1, -1, -1, 10},
	{6, -1, -1, 20, 1, -1 }, 
	{7, 9, 20, -1, 13, 12},
	{-1, -1, 1, 13, -1, 4},
	{-1, 10, -1, 12, 4, -1} 
	};
	response res=calcLongestPath(g,n,0,4);
	ASSERT_EQUAL(1, res.code);
	ASSERT_STR("loop", res.message.c_str());
}

CTEST(calc, longest2) {
	const int n=4;
	std::vector<std::vector<int> > g = {
	{-1,3,2,-1},
	{-1,-1,2,-1},
	{-1,-1,-1,1},
	{-1,1,-1,-1}
	};
	response res=calcLongestPath(g,n,0,3);
	ASSERT_EQUAL(res.code, 0);
	ASSERT_EQUAL(res.answer, 6);
}

CTEST(calc, longest3) {
	const int n=4;
	std::vector<std::vector<int> > g = {
	{-1,3,2,3},
	{-1,-1,2,-1},
	{-1,1,-1,-1},
	{-1,1,-1,-1}
	};
	response res=calcLongestPath(g,n,0,3);
	ASSERT_EQUAL(res.code, 0);
	ASSERT_EQUAL(res.answer, 3);
}





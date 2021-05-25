#include <test/ctest.h>

#include <fstream>
#include <iostream>
#include <sstream>
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
	CTEST_LOG("%s",a.c_str());
	ASSERT_STR(result.c_str(), a.c_str());
}


CTEST2(suite, test2) {
	data->f.good();
	const char *args[] = {mPath.c_str(),"4","5","-m"};
	const std::string result="no argument for -m\n";
	nmain(4,args);
	std::string a=data->ss.str();
	CTEST_LOG("%s",a.c_str());
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST2(suite, test3) {
	data->f.good();
	const char *args[] = {mPath.c_str(),"4","5","-m","bb"};
	const std::string result="invalid argument for -m, expected [sp, lp, cp], found bb\n";
	nmain(5,args);
	std::string a=data->ss.str();
	CTEST_LOG("%s",a.c_str());
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST2(suite, test4) {
	data->f.good();
	const char *args[] = {mPath.c_str(),"4","5","-i"};
	const std::string result="no argument for -i\n";
	nmain(4,args);
	std::string a=data->ss.str();
	CTEST_LOG("%s",a.c_str());
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST2(suite, test5) {
	data->f.good();
	const char *args[] = {mPath.c_str(),"4","5","-o"};
	const std::string result="no argument for -o\n";
	nmain(4,args);
	std::string a=data->ss.str();
	CTEST_LOG("%s",a.c_str());
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST2(suite, test6) {
	data->f.good();
	const char *args[] = {mPath.c_str(),"4","5","6"};
	const std::string result="too much arguments (6)\n";
	nmain(4,args);
	std::string a=data->ss.str();
	CTEST_LOG("%s",a.c_str());
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST2(suite, test7) {
	data->f.good();
	const char *args[] = {mPath.c_str(),"4","5","boba"};
	const std::string result="what is boba?\n";
	nmain(4,args);
	std::string a=data->ss.str();
	CTEST_LOG("%s",a.c_str());
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST2(suite, test8) {
	data->f.good();
	const char *args[] = {mPath.c_str(),"4","5","-i","not/found/file.txt"};
	const std::string result="File not found\n";
	nmain(5,args);
	std::string a=data->ss.str();
	CTEST_LOG("%s",a.c_str());
	ASSERT_STR(result.c_str(), a.c_str());
}

CTEST2(suite, test9) {
	data->f.good();
	const char *args[] = {mPath.c_str(),"4","-m","sp"};
	const std::string result="no argument for begin node or end node\n";
	nmain(4,args);
	std::string a=data->ss.str();
	CTEST_LOG("%s",a.c_str());
	ASSERT_STR(result.c_str(), a.c_str());
}






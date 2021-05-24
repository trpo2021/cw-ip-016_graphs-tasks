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
	int a;
	std::cin >> a;
	CTEST_LOG("%d",a);
	ASSERT_STR("foo", "foo");
}



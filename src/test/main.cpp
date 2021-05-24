#define CTEST_MAIN
#define __STDC_FORMAT_MACROS
#include <inttypes.h>


//#define CTEST_SEGFAULT
//#define CTEST_COLOR_OK
#define CTEST_NO_COLORS

#include <test/ctest.h>

#include <iostream>
#include <string>

std::string mPath;



int main(int argc, const char *argv[]) {
	std::string mPath= argv[0];
	mPath=mPath.substr(0,mPath.rfind("bin"));
	return ctest_main(argc, argv);
}

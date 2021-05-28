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
	mPath= argv[0];
	unsigned int b=mPath.rfind("bin");
	if(b<mPath.length())
		mPath=mPath.substr(0,b);
	else
		mPath="../";
	return ctest_main(argc, argv);
}

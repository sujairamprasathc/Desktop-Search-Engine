#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include "Indexer.h"
//#include "DocumentIDManager.h"
using namespace std;



int main(int argc, char **argv)
{
	Indexer i;
	string file_name;
	
	if (argc < 2) {
		cout << "USAGE : " << argv[0] << " [index <filename>]/[computeinvertedindex]" << endl;
		return -1;
	}
	
	if (strcmp(argv[1], "index") == 0) {
		file_name = string(argv[2]);
		i.index(file_name);
	}
	else if (strcmp(argv[1], "computeinvertedindex") == 0) {
		i.computeInvertedIndex();
	}
	else {
		cout << "USAGE : " << argv[0] << " [index <filename>]/[computeinvertedindex]" << endl;
		return -2;
	}

	return 0;
}

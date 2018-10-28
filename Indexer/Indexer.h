#ifndef INDEXER_H
#define INDEXER_H

#include <map>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <sys\stat.h>
#include <filesystem>

#include "hash.h"
#include "FileConstants.h"
#include "DocumentIDManager.h"


class Indexer
{
private:
	DocumentIDManager document_id_manager;

public:
	Indexer();
	~Indexer();

	std::string index(std::string&);	// Send absolute path
	void computeInvertedIndex();
};

#endif // !INDEXER_H
#ifndef INDEXER_H
#define INDEXER_H

#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include <list>
#include <map>
#include <sstream>
#include <string>

#include "DocumentIDManager.h"
#include "FileConstants.h"
#include "hash.h"

class Indexer {
 private:
  DocumentIDManager document_id_manager;

 public:
  Indexer();
  ~Indexer();

  std::string index(std::string&);  // Send absolute path
  void computeInvertedIndex();
};

#endif  // !INDEXER_H

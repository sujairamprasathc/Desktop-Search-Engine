#ifndef DOCUMENT_ID_MANAGER
#define DOCUMENT_ID_MANAGER

#include "FileConstants.h"
#include <fstream>
#include <string>


class DocumentIDManager
{
private:
	std::fstream document_id_store;
	std::fstream document_id_map;

public:
	DocumentIDManager();
	~DocumentIDManager();

	unsigned int getDocumentID(const std::string&);
	unsigned int getNumberOfDocuments();
	unsigned int getNewDocumentID(const std::string&);
	std::string getDocument(unsigned int);
};


#endif // !DOCUMENT_ID_MANAGER
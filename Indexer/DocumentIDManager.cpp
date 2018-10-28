#define _CRT_SECURE_NO_WARNINGS
#include "DocumentIDManager.h"
// TODO : Add exceptions to the file instead of abrupt termination
#include <iostream>
using namespace std;



DocumentIDManager::DocumentIDManager()
{
	// Check if file exists
	document_id_store.open(LOCAL_APP_DATA_DIRECTORY + "lastdocumentid", ios::binary | ios::in | ios::out);

	if (!document_id_store.is_open()) {
		// File not exist - fatal error
		document_id_store.open(LOCAL_APP_DATA_DIRECTORY + "lastdocumentid", ios::binary | ios::in | ios::out | ios::trunc);
		unsigned int x = 0;
		document_id_store.write(reinterpret_cast<char*>(&x), sizeof(x));
	}
	else {
		// success
	}

	document_id_map.open(LOCAL_APP_DATA_DIRECTORY + "documentidmap", ios::in | ios::out | ios::app);
}



DocumentIDManager::~DocumentIDManager()
{
	if (document_id_store.is_open()) {
		document_id_store.close();
	}
	if (document_id_map.is_open()) {
		document_id_store.close();
	}
}



unsigned int DocumentIDManager::getDocumentID(const string& document_path)
{
	string path;
	unsigned int document_id;

	document_id_map.seekg(0, ios::beg);
	
	while (!(getline(document_id_map >> document_id, path)).eof()) {
		if (path == document_path) {
			return document_id;
		}
	}

	document_id_map.clear();

	if (path == document_path) {
		return document_id;
	}
	return 0;
}



unsigned int DocumentIDManager::getNumberOfDocuments()
{
	unsigned int document_id = 0;

	document_id_store.seekg(0, ios::beg);
	document_id_store.read(reinterpret_cast<char*>(&document_id), sizeof(document_id));

	return document_id;
}



unsigned int DocumentIDManager::getNewDocumentID(const std::string &document_path)
{
	unsigned int document_id = 0;

	document_id_store.seekg(0, ios::beg);
	document_id_store.read(reinterpret_cast<char*>(&document_id), sizeof(document_id));

	document_id += 1;

	document_id_store.seekp(0, ios::beg);
	document_id_store.write(reinterpret_cast<char*>(&document_id), sizeof(document_id));
	document_id_store.flush();

	document_id_map << document_id << " " << document_path << endl;

	return document_id;
}



std::string DocumentIDManager::getDocument(unsigned int document_id)
{
	document_id_map.seekg(ios::beg);
	char documment_path[65536];
	unsigned int doc_id;

	while (document_id_map.peek() != ifstream::traits_type::eof())
	{
		(document_id_map >> doc_id). getline(documment_path, 65536);
		if (doc_id == document_id) {
			document_id_map.clear();
			return documment_path;
		}
	}

	document_id_map.clear();
	throw "Not found";
}
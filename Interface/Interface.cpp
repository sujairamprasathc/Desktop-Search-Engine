// The main interface
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <list>

#include "FileConstants.h"
#include "DocumentIDManager.h"
using namespace std;




int main(int argc, char **argv)
{
	if (argc < 2) {
		cout << "USAGE : " << argv[0] << " <word> [<boolean operator> <word> <boolean operator> <word> ...]" << endl;
		exit(-1);
	}

	for (int i = 1; i < argc; ++i) {
		for (unsigned int j = 0; j < strlen(argv[i]); ++j) {
			argv[i][j] = tolower(argv[i][j]);
		}
	}

	vector<list<unsigned int>> search_results;

	for (int i = 1; i < argc; i += 2)
	{
		list<unsigned int> single_word_hits;
		unsigned int document_id = 0, word_count = 0;

		ifstream inverted_index(INVERTED_INDEX_STORAGE_DIRECTORY + argv[i]);
		if (inverted_index.is_open())
		{
			while (!(inverted_index >> document_id >> word_count).eof()) {
				single_word_hits.push_back(document_id);
			}

			inverted_index.close();
		}

		search_results.push_back(single_word_hits);
	}

	list<unsigned int> final_search_results = search_results[0];

	for (int i = 2, j = 0; i < argc; i += 2, ++j) {
		if (strcmp(argv[i], "and") == 0) {
			list<unsigned int> temp_result_storage(final_search_results.size());
			set_intersection(search_results[j + 1].begin(), search_results[j + 1].end(), final_search_results.begin(), final_search_results.end(), temp_result_storage.begin());
			final_search_results = temp_result_storage;
		}
		else if (strcmp(argv[i], "or") == 0) {
			list<unsigned int> temp_result_storage(final_search_results.size() + search_results[j + 1].size());
			set_union(search_results[j + 1].begin(), search_results[j + 1].end(), final_search_results.begin(), final_search_results.end(), temp_result_storage.begin());
			final_search_results = temp_result_storage;
		}
		else if (strcmp(argv[i], "stem") == 0) {
			list<unsigned int> temp_result_storage(final_search_results.size());
			set_difference(final_search_results.begin(), final_search_results.end(), search_results[j + 1].begin(), search_results[j + 1].end(), temp_result_storage.begin());
			final_search_results = temp_result_storage;
		}

		// Remove extra elements
		final_search_results.erase(find(final_search_results.begin(), final_search_results.end(), 0), final_search_results.end());
	}

	DocumentIDManager doc_id_manager;
	for (auto each_result : final_search_results) {
		cout << doc_id_manager.getDocument(each_result) << endl;
	}

	return 0;
}

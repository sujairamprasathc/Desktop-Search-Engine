#define _CRT_SECURE_NO_WARNINGS
#include "Indexer.h"
using namespace std;

// Auxilary functions declaration
static string removeSpecialCharacters(string);
static string convertToLowerCase(string);

Indexer::Indexer() {
  // Set up inverted index
  struct stat info;
  if (stat(INVERTED_INDEX_STORAGE_DIRECTORY.c_str(), &info) != 0) {
    filesystem::create_directories(INVERTED_INDEX_STORAGE_DIRECTORY);
  }

  // Set up forward index
  if (stat(FORWARD_INDEX_STORAGE_DIRECTORY.c_str(), &info) != 0) {
    filesystem::create_directories(FORWARD_INDEX_STORAGE_DIRECTORY);
  }
}

Indexer::~Indexer() {}

string Indexer::index(string& document_file_name) {
  /**
   *	Each word in the document is converted into its wordID
   *	Then, the word is inserted into the @HitList of the document
   *
   *	TODO : Hits
   *	Hit List : WordID->Word->Count->Hits->Hits->Hits
   *					 ->Word->Count->Hits->Hits...
   *
   *	Hits : {Position, Font Size, Additional Attributes}
   *
   *	TODO : Use a secondary hash in place of @Word in @HitList
   *	TODO : Use a self balancing binary search tree to store the words
   *temporarily before creating the actual forward index
   */

  ifstream document_file(document_file_name);

  if (!document_file.is_open()) {
    throw "File not found";
  }

  map<unsigned int, map<string, unsigned int>> word_map;
  string word;
  unsigned int wordID;
  while (!document_file.eof()) {
    document_file >> word;
    word = removeSpecialCharacters(word);
    if (!word.empty()) {
      word = convertToLowerCase(word);
      wordID = indexer::hash(word);
      word_map[wordID][word] = word_map[wordID][word] + 1;
    }
  }

  char buffer[20] = {0};
  ofstream forward_index_output_file(
      FORWARD_INDEX_STORAGE_DIRECTORY +
      to_string(document_id_manager.getNewDocumentID(document_file_name)));

  for (auto each_word_id : word_map) {
    forward_index_output_file << each_word_id.first << " ";
    for (auto each_word : each_word_id.second) {
      forward_index_output_file << each_word.first << " " << each_word.second
                                << " ";
    }
    forward_index_output_file << endl;
  }

  return string(buffer);
}

void Indexer::computeInvertedIndex() {
  /** Word -> {DocID, nTimes}  **/
  char buffer[20] = {0};

  for (unsigned int i = 1; i <= document_id_manager.getNumberOfDocuments();
       ++i) {
    ifstream forward_index(FORWARD_INDEX_STORAGE_DIRECTORY + to_string(i));

    unsigned int word_id, count;
    string word_list, word;

    while (!forward_index.eof()) {
      forward_index >> word_id;
      getline(forward_index, word_list);
      stringstream words_stream(word_list);
      do {
        words_stream >> word >> count;

        // Append entry to the doc list
        fstream inverted_index(INVERTED_INDEX_STORAGE_DIRECTORY + word,
                               ios::in | ios::out | ios::app);

        inverted_index << to_string(i) << " " << count << endl;
        inverted_index.close();

      } while (!words_stream.peek() == ifstream::traits_type::eof());
    }
  }
}

static string removeSpecialCharacters(string word) {
  if (word.empty()) {
    return string();
  }

  /*while (word.find('.') != string::npos) {
          word.erase(word.find('.'), 1);
  }*/
  if (word[word.length() - 1] == '.') {
    word.erase(word.rfind('.'));
  }

  while (word.find(',') != string::npos) {
    word.erase(word.find(','), 1);
  }

  while (word.find('(') != string::npos) {
    word.erase(word.find('('), 1);
  }

  while (word.find(')') != string::npos) {
    word.erase(word.find(')'), 1);
  }

  while (word.find(',') != string::npos) {
    word.erase(word.find(','), 1);
  }

  while (word.find('+') != string::npos) {
    word.erase(word.find('+'), 1);
  }

  while (word.find('-') != string::npos) {
    word.erase(word.find('-'), 1);
  }

  while (word.find('*') != string::npos) {
    word.erase(word.find('*'), 1);
  }

  while (word.find('=') != string::npos) {
    word.erase(word.find('='), 1);
  }

  while (word.find('/') != string::npos) {
    word.erase(word.find('/'), 1);
  }

  while (word.find('\\') != string::npos) {
    word.erase(word.find('\\'), 1);
  }

  while (word.find('|') != string::npos) {
    word.erase(word.find('|'), 1);
  }

  while (word.find('{') != string::npos) {
    word.erase(word.find('{'), 1);
  }

  while (word.find('}') != string::npos) {
    word.erase(word.find('}'), 1);
  }

  while (word.find('[') != string::npos) {
    word.erase(word.find('['), 1);
  }

  while (word.find(']') != string::npos) {
    word.erase(word.find(']'), 1);
  }

  while (word.find('!') != string::npos) {
    word.erase(word.find('!'), 1);
  }

  while (word.find(';') != string::npos) {
    word.erase(word.find(';'), 1);
  }

  while (word.find('<') != string::npos) {
    word.erase(word.find('<'), 1);
  }

  while (word.find('>') != string::npos) {
    word.erase(word.find('>'), 1);
  }

  while (word.find('?') != string::npos) {
    word.erase(word.find('?'), 1);
  }

  while (word.find('\"') != string::npos) {
    word.erase(word.find('\"'), 1);
  }

  while (word.find('\'') != string::npos) {
    word.erase(word.find('\''), 1);
  }

  while (word.find((signed char)-109) != string::npos) {
    word.erase(word.find((signed char)-109), 1);
  }

  while (word.find((signed char)-108) != string::npos) {
    word.erase(word.find((signed char)-108), 1);
  }

  while (word.find((unsigned char)145) != string::npos) {
    word.erase(word.find((unsigned char)145), 1);
  }

  while (word.find((unsigned char)146) != string::npos) {
    word.erase(word.find((unsigned char)146), 1);
  }

  return word;
}

static string convertToLowerCase(string word) {
  for (unsigned int i = 0; i < word.length(); ++i) {
    word[i] = tolower(word[i]);
  }

  return word;
}

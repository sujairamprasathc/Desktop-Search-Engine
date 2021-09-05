#include <queue>
#include <string>
#include <iostream>
#include <filesystem>

#ifdef _WIN32
	#include <Windows.h>
#endif

using namespace std;

queue<string> file_queue;
queue<string> folder_queue;



// This function lists all files recursively starting from the @root_path
// The full path to the files are enqueued automatically to the file_queue
void listFiles(string root_path)
{
	std::filesystem::path path(root_path);
	folder_queue.push(string(root_path));

	while (!folder_queue.empty())
	{
		string folder_name = folder_queue.front();
		folder_queue.pop();

		for (auto folder_item : std::filesystem::directory_iterator(folder_name))
		{
			if (is_directory(folder_item.path())) {
				folder_queue.push(string(folder_item.path().generic_string()));
			}
			else if (is_regular_file(folder_item.path())) {
				file_queue.push(string(folder_item.path().generic_string()));
			}
		}
	}
}



// This function lists all drives in a Windows operating system.
// This function only works on Windows
void listDrives()
{
	/*int dr_type = 99;
	char dr_avail[256];
	GetLogicalDriveStrings(256, dr_avail);

	char *temp = dr_avail;

	while (dr_avail != NULL)
	{
		dr_type = GetDriveType(dr_avail);
		switch (dr_type)
		{
		case 0:
			//Unknown Drive type
			break;

		case 1:
			//Drive is invalid
			break;

		case 2:
			//Removable Drive
			break;

		case 3:
			//Hard Disk (Fixed)
			listFiles(temp);
			break;

		case 4:
			//Remote (Network) Drive
			break;

		case 5:
			//CD-Rom/DVD-Rom
			break;

		case 6:
			//Ram Drive
			break;
		}
		temp += lstrlen(temp) + 1;
	}
	*/
}



int main()
{
	string root_path;

	cout << "Enter root path: " << endl;
	cin >> root_path;

	listFiles(root_path);

	cout << "Indexing" << endl;

	// Only txt files are indexed. TODO: Read pdf, doc files
	while (!file_queue.empty()) {
		string file_path = file_queue.front();
		file_queue.pop();

		string extension = ".txt";
		if (file_path.substr(file_path.length() - 4) == extension) {
#ifdef _WIN32
			string command = (string("Indexer.exe index ") + '\"' + file_path + '\"');
#else
			string command = (string("./indexer index ") + '\"' + file_path + '\"');
#endif
			if (system(command.c_str()) != 0) {
				cout << "Failed to index " << file_path << endl;
			}
		}
	}
}

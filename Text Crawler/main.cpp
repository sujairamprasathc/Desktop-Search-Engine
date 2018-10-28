#include <string>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include<queue>

using namespace std;

queue<string> file_queue;
queue<string> folder_queue;



void listFiles(string root_path)
{
	std::experimental::filesystem::path path(root_path);
	folder_queue.push(string(root_path));

	while (!folder_queue.empty())
	{
		string folder_name = folder_queue.front();
		folder_queue.pop();

		for (auto folder_item : std::experimental::filesystem::directory_iterator(folder_name))
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



int main()
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
	
	listFiles("E:/");

	cout << "Indexing" << endl;

	while (!file_queue.empty()) {
		string file_path = file_queue.front();
		file_queue.pop();

		string extension = ".txt";
		if (file_path.substr(file_path.length() - 4) == extension) {
			string command = (string("Indexer.exe index ") + '\"' + file_path + '\"');
			if (system(command.c_str()) != 0) {
				cout << "Failed to index " << file_path << endl;
			}
		}
	}
}
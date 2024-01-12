#include "File.h";
#include <iostream>;
#include <string>;
#include <fstream>
#include <filesystem>;
#include <chrono>
#include <iomanip>

using namespace std;

File::File(string name, double size) : ExistingItem(name, "", size)
{

}

File::~File() 
{

}


string File::getName() {
	return name;
}


void File::createFile(string fileName) 
{
	//string filePath = name + "\\" + fileName;
	ofstream newFile(name);

	if (newFile.is_open()) {
		cout << "File created successfully: " << fileName << endl;
		newFile.close();

		auto currentTime = chrono::system_clock::now();
		time_t creationTime = chrono::system_clock::to_time_t(currentTime);

		tm creationTm;
		localtime_s(&creationTm, &creationTime); // Use localtime_s for safety

		char buffer[80];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &creationTm);

		timestamp = buffer; // Set the timestamp within the File class
	}
	else {
		cout << "Failed to create file: " << fileName << endl;
	}
}






//void File::deleteFile() 
//{
//
//}
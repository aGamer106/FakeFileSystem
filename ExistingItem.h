#pragma once
#include <iostream>
#include <filesystem>
#include <string>


using namespace std;


class ExistingItem
{

protected:
	string name;
	string timestamp;
	double size;

public:
	ExistingItem(string name, string timestamp, double size);
	~ExistingItem();
	virtual void navigate(); 
	void listDirectories(string path);
	static const tm convertTime(const filesystem::file_time_type& timestamp);
	void searchDirectory(string name);
	void displayCommands();
	void useDirCommand(const string& path); // this method is used only for the "dir" command
};

  
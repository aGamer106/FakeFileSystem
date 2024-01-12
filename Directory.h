#pragma once
#include <iostream>;
#include <filesystem>;
#include "ExistingItem.h";

using namespace std;

class Directory : ExistingItem
{
private:
	string currentPath;

public:
	Directory(string name, double size);
	~Directory();
	string getName();
	virtual bool browseThroughDirectories(const string& cmd, const string& root_path); //method that uses the "cd" command
};


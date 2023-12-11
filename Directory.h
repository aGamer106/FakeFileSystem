#pragma once
#include<iostream>
#include <filesystem>
#include "ExistingItem.h";

using namespace std;

class Directory : ExistingItem
{

private:
	string path;
	string name;
	double size;
	string timeOfEdit;

public:
	void remove();
	void rename();
	Directory();
	~Directory();
	Directory(char* path, char* name, double size, char* timeOfEdit);

};


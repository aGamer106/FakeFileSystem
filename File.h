#pragma once
#include <iostream>;
#include <filesystem>;
#include "ExistingItem.h";

using namespace std;

class File : ExistingItem
{
public:
	File(string name, double size);
	~File();
	virtual void createFile(string fileName);
	string getName();

};


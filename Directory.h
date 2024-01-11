#pragma once
#include <iostream>;
#include <filesystem>;
#include "ExistingItem.h";

using namespace std;

class Directory : ExistingItem
{
public:
	Directory(string name, double size);
	virtual void browseThroughDirectories(); //method that uses the "cd" command
};


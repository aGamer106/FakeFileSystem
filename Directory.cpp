#include "Directory.h"
#include "ExistingItem.h"
#include <filesystem>
#include <stdio.h>
#include <iostream>

using namespace std;

Directory::Directory(string name, double size) : ExistingItem(name, size) 
{

}

Directory::~Directory() 
{

}

//browsing through folders using the "cd" commands method
//TODO - overall implementation;
void Directory::browseThroughDirectories() {
	
	string filePath = name + "\\";


}
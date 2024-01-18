#pragma once
#include "ExistingItem.h"
#include <iostream>

using namespace std;

class File : public ExistingItem {


public:
    File(std::string name, double size);
    ~File();
    string getName();
    void createFile(string fileName);
};


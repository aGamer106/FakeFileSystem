#pragma once
#include "Directory.h"
#include "File.h"
#include "ExistingItem.h"
#include <iostream>

File::File(std::string name, double size) : ExistingItem(name, "", size) {}

File::~File() {}

string File::getName() {
    return name;
}

void File::createFile(string fileName)
{
    // Set the name of the file
    this->name = fileName;

    // Simulate the file creation timestamp
    auto currentTime = chrono::system_clock::now();
    time_t creationTime = chrono::system_clock::to_time_t(currentTime);

    tm creationTm;
    localtime_s(&creationTm, &creationTime); // Use localtime_s for safety

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &creationTm); // Format creation time

    timestamp = buffer; // Set the timestamp within the File class

    cout << "Simulated file created: " << fileName << " with timestamp " << timestamp << endl;
}




//void File::deleteFile() 
//{
//
//}
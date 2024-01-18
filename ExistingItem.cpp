#pragma once
#include "ExistingItem.h"
#include "File.h"
#include "Directory.h"
#include <iostream>
#include <string>
#include <map>
#include <filesystem>
#include <memory>
#include <sys/stat.h>

using namespace std;


ExistingItem::ExistingItem(string name, string timestamp, double size) : name(name), timestamp(timestamp), size(size)
{

}

ExistingItem::~ExistingItem()
{

}

void ExistingItem::searchDirectory(string path)
{
    for (const filesystem::directory_entry& item : filesystem::directory_iterator(path))
    {
        if (item.is_directory())
        {
            string subpath = item.path().string(); // Create a new string for subpath
            std::cout << subpath << endl;
            searchDirectory(subpath); // Use the new subpath
        }
        else
        {
            std::cout << item.path().string() << endl;
        }
    }
}


void ExistingItem::useDirCommand(const string& path)
{
    cout << "Contents of " << path << ":\n";

    // Printing real files
    vector<shared_ptr<Directory>> directoriesInMemory;
    vector<shared_ptr<File>> filesInMemory;

    // Iterate through the real files and directories
    for (const auto& item : filesystem::directory_iterator(path)) {
        string itemName = item.path().filename().string();

        if (item.is_directory()) {
            cout << "Directory: " << itemName << endl;

            // Create a Directory object and add it to the in-memory list
            auto dir = make_shared<Directory>(itemName, 0.0);
            directoriesInMemory.push_back(dir);
        }
        else {
            cout << "File: " << itemName << endl;

            // Create a File object and add it to the in-memory list
            auto file = make_shared<File>(itemName, 0.0); // Assuming size is 0.0
            filesInMemory.push_back(file);
        }
    }
    
}



void ExistingItem::displayCommands() {
    cout << " " << endl;
    cout << "1. dir" << endl;
    cout << "2. sortsize" << endl;
    cout << "3. sortname" << endl;
    cout << "4. cd + ENTER + [name]" << endl;
    cout << "5. mkdir + ENTER + [name]" << endl;
    cout << "6. mkfile + ENTER + [name]" << endl;
    cout << "7. del + ENTER + [name]" << endl;
    cout << "8. exit" << endl;
    cout << " " << endl;
}


// we need to do a little conversion between what the filesystem returns for time stamps and something usable
// just use this function and don't worry about how it works
const tm ExistingItem::convertTime(const filesystem::file_time_type& timestamp)
{
    using namespace chrono;  // just for this function, use chrono to save us prefixing chrono:: everywhere
    system_clock::time_point delta = time_point_cast<system_clock::duration>(timestamp - filesystem::file_time_type::clock::now() + system_clock::now());
    time_t conversion = system_clock::to_time_t(delta);

    tm result;
    localtime_s(&result, &conversion);
    return result;
}


void ExistingItem::listDirectories(string path) {

    cout << "(C) Razvan-Daniel Besleaga. All rights reserved." << '\n';
    cout << "================================================" << '\n';
    cout << "Initialisation complete..." << '\n';
    cout << "Here is a list of files in " << path << "\n\n";

    // use an implicit iterator to enumerate the path
    for (const filesystem::directory_entry& item : filesystem::directory_iterator(path))
    {
        if (item.is_directory()) // check if this is a directory
        {
            // get and display the name of the current item
            string name = item.path().filename().string();
            cout << "A directory called " << name;

            // get the timestamp into a format that allows us to manage it
            tm timestamp = convertTime(item.last_write_time());
            cout << " timestamp: ";
            cout << "Year: " << (timestamp.tm_year + 1900); // tm_year start at 0 for 1900 so add 1900
            cout << " Month: " << (timestamp.tm_mon + 1); // tm_mon starts at 0 for January so add 1
            cout << " Day: " << timestamp.tm_mday;
            cout << " Hour: " << timestamp.tm_hour;
            cout << " Min: " << timestamp.tm_hour;
            cout << "\n";
        }
        else
        {
            // another way to get at the data held in the filename as a c-string (array of characters)
            string tmp = item.path().filename().string();
            const char* name = tmp.c_str();

            cout << "A file called " << name;

            // get the size of the file - __int64 is just an integer value, but using 64 bits to store it (8 bytes)
            __int64 filesize = item.file_size();
            cout << " size: " << filesize;
            cout << "\n";
        }
    }
}



void ExistingItem::navigate()
{
    string input;
    map<string, int> commands = {
        {"dir", 1},
        {"sortsize", 2},
        {"sortname", 3},
        {"cd", 4},
        {"mkdir", 5},
        {"mkfile", 6},
        {"del", 7},
        {"exit", 8},
        {"commands", 0}
    };

    // Create a root directory for the simulated file system
    auto currentDirectory = make_shared<Directory>(name, 0.0);

    while (true)
    {
        cout << currentDirectory->getName() << ":>";
        cout << " ";
        getline(cin, input);

        auto commandIt = commands.find(input);
        if (commandIt != commands.end())
        {
            int command = commandIt->second;
            switch (command)
            {
            case 0:
                displayCommands();
                break;
            case 1:
                useDirCommand(currentDirectory->getName());
                break;
            case 2:
                // Implement sort by size
                break;
            case 3:
                // Implement sort by name
                break;
            case 4:
            {
                string directoryName;
                cout << "Directory name: ";
                getline(cin, directoryName);

                if (currentDirectory->browseThroughDirectories("cd " + directoryName, "C:\\Users\\User\\Desktop\\DummyData")) {
                    cout << "Succesfully changed directory to: " << currentDirectory->getName() << endl;
                }
                // Here you can add logic to change the current directory
                // This requires maintaining a hierarchy or path in your simulated file system
                break;
            }
            case 5: // "mkdir"
            {
                string directoryName;
                cout << "Directory Name: ";
                getline(cin, directoryName);

                if (!currentDirectory->createDirectory(directoryName)) {
                    cout << "Error: A directory with the name '" << directoryName << "' already exists." << endl;
                    break;
                }
                else {
                    // Display confirmation message with timestamp
                    auto currentTime = chrono::system_clock::now();
                    time_t creationTime = chrono::system_clock::to_time_t(currentTime);
                    tm creationTm;
                    localtime_s(&creationTm, &creationTime);
                    char buffer[80];
                    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &creationTm);
                    cout << "Directory \"" << directoryName << "\" created successfully with timestamp " << buffer << endl;
                }
                
                currentDirectory->listContents();
                break;
            }

            case 6:
            {
                string fileName;
                cout << "File Name: ";
                getline(cin, fileName);

                // Check if a file with the same name already exists in the current directory
                if (currentDirectory->fileExists(fileName)) {
                    cout << "File already exists in the current directory, try a new name." << endl;
                }
                else {
                    // Create a new File object
                    auto newFile = make_shared<File>(fileName, 0.0); 
                    currentDirectory->addSimulatedFile(newFile);
                    
                    newFile->createFile(fileName);
                    cout << "Simulated file \"" << fileName << "\" created successfully in directory " << currentDirectory->getName() << endl;
                    currentDirectory->listContents();
                }
                break;
            }


            case 7:
                // Implement delete functionality
                break;
            case 8:
                exit(0);
                break;
            default:
                cout << "Command not implemented yet.\n";
                break;
            }
        }
        else
        {
            cout << "Invalid command. Type 'commands' to see available commands.\n";
        }
    }
}




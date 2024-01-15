#include "Directory.h"
#include "ExistingItem.h"
#include <filesystem>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <direct.h>
#include <memory>

using namespace std;

Directory::Directory(string name, double size) : ExistingItem(name, "", size)
{
    currentPath = name;
}

Directory::~Directory() 
{

}

//getter for the name attribute
string Directory::getName() {
    return name;
}

//browsing through folders using the "cd" commands method
inline bool Directory::browseThroughDirectories(const string& cmd, const string& rootPath)
{
    if (cmd == "cd ..") //check if the command is ".."
    {
        //check if the current directory is not the root directory of the fake files
        if (name != rootPath)
        {
            
            filesystem::path parent_path = filesystem::path(name).parent_path(); //get the parent path - move one level up in the directories
            name = parent_path.string(); //update the current directory name
            return true;
        }
        else //handle errors and throw suitable messages to the screen
        {
            cout << "Error: Already at the root directory." << endl;
            return false;
        }
    }
    else if (cmd.length() >= 4 && cmd.substr(0, 3) == "cd ") // Check if the command starts with "cd "
    {
        
        string arg = cmd.substr(3); //extract the argument from the "cd" command
        filesystem::path new_path = name + "\\" + arg; //combine the current path with the new directory name

        if (filesystem::is_directory(new_path))
        {
            name = new_path.string(); //update the current directory name
            return true;
        }
        else
        {
            cout << "Error: \"" << arg << "\" is not a valid directory" << endl;
            return false;
        }
    }
    else
    {
        cout << "Error: Invalid 'cd' command format. Use 'cd <directory>' or 'cd ..'." << endl;
        return false;
    }
}


bool Directory::createDirectory(string directoryName)
{
    string newFolderPath = currentPath + "\\" + directoryName; // Use currentPath for path construction

    if (!filesystem::exists(newFolderPath))
    {
        try {
            filesystem::create_directory(newFolderPath);
            cout << "Successfully created directory: " << directoryName << endl;
            return true;
        }
        catch (const std::exception& e) {
            cout << "Exception caught: " << e.what() << endl;
            return false;
        }
    }
    else
    {
        cout << "Error: The folder " << directoryName << " already exists. Try a new name." << endl;
        return false;
    }
}


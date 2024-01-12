#include "Directory.h"
#include "ExistingItem.h"
#include <filesystem>
#include <fstream>
#include <stdio.h>
#include <iostream>

using namespace std;

Directory::Directory(string name, double size) : ExistingItem(name, "", size)
{

}

Directory::~Directory() 
{

}

string Directory::getName() {
    return name;
}

//browsing through folders using the "cd" commands method
//TODO - overall implementation;
inline bool Directory::browseThroughDirectories(const string& cmd, const string& rootPath)
{
    if (cmd == "cd ..") // Check if the command is "cd .."
    {
        // Check if the current directory is not the root directory of your "fake" file system
        if (name != rootPath)
        {
            // Get the parent path (move one level up)
            filesystem::path parent_path = filesystem::path(name).parent_path();
            name = parent_path.string(); // Update the current directory name
            return true;
        }
        else
        {
            cout << "Error: Already at the root directory." << endl;
            return false;
        }
    }
    else if (cmd.length() >= 4 && cmd.substr(0, 3) == "cd ") // Check if the command starts with "cd "
    {
        // Extract the argument from the "cd" command
        string arg = cmd.substr(3);

        // Combine the current path with the new directory name
        filesystem::path new_path = name + "\\" + arg;

        if (filesystem::is_directory(new_path))
        {
            name = new_path.string(); // Update the current directory name
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



    //if (cmd.length() < 4) return false;
    //string arg = cmd.substr(3);

    //filesystem::path new_path = current_path / arg;
    //if (filesystem::is_directory(new_path)) {
    //    name = new_path.string();  // Update the current directory
    //    return true;
    //}
    //else {
    //    cout << "Error: \"" << arg << "\" is not a valid directory" << endl;
    //    return false;
    //}
}

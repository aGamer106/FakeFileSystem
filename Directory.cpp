#pragma once
#include "Directory.h"

Directory::Directory(std::string name, double size) : ExistingItem(name, "", size), currentPath(name)
{
    currentPath = name;
}

Directory::~Directory() {}

string Directory::getName()
{
    return name;
}

void Directory::setRoot(std::shared_ptr<Directory> root)
{
    this->root = root;
}

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

void Directory::clearContents()
{
    realFiles.clear();
    fakedFiles.clear();
    directories.clear();
}



void Directory::listContents() const {
    // List directories
    for (const auto& dir : directories) {
        std::cout << "Directory: " << dir->getName() << std::endl;
    }

    // List real files
    for (const auto& realFile : realFiles) {
        std::cout << "Real File: " << realFile->getName() << std::endl;
    }

    // List simulated files
    for (const auto& simulatedFile : fakedFiles) {
        std::cout << "Simulated File: " << simulatedFile->getName() << std::endl;
    }
}


bool Directory::fileExists(const std::string& fileName) const {
    for (const auto& realFile : realFiles) {
        if (realFile->getName() == fileName) {
            return true;
        }
    }

    for (const auto& fakeFile : fakedFiles) {
        if (fakeFile->getName() == fileName) {
            return true;
        }
    }

    return false;
}

void Directory::addRealFile(const std::shared_ptr<File>& realFile)
{
    realFiles.push_back(realFile);
}


void Directory::listSimulatedFiles() const
{
    cout << "Listing the instances created here: " << endl;
    for (const auto& simulatedFile : fakedFiles) {
        cout << "FF: " << simulatedFile->getName() << endl;
    }
}

void Directory::addSimulatedFile(const std::shared_ptr<File>& fakedFile)
{
    fakedFiles.push_back(fakedFile);
}

const std::vector<std::shared_ptr<File>>& Directory::getRealFiles() const
{
    return realFiles;
}

const std::vector<std::shared_ptr<File>>& Directory::getSimulatedFiles() const
{
    return fakedFiles;
}

void Directory::addFileToMemory(const std::shared_ptr<File>& file)
{
    realFiles.push_back(file);
}

void Directory::addDirectoryToMemory(const std::shared_ptr<Directory>& directory)
{
    directories.push_back(directory);
}


bool Directory::createDirectory(const std::string& directoryName) {
    // Check if a directory with this name already exists
    for (const auto& dir : directories) {
        if (dir->getName() == directoryName) {
            return false; // Directory already exists
        }
    }

    // If directory doesn't exist, create it
    auto newDirectory = std::make_shared<Directory>(directoryName, 0.0);
    directories.push_back(newDirectory);
    return true; // Directory created successfully
}


const std::vector<std::shared_ptr<Directory>>& Directory::getDirectories() const
{
    return directories;
}




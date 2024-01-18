//#pragma once
#include "ExistingItem.h"
#include "File.h"
#include <vector>
#include <memory>

class Directory : public ExistingItem {
private:
    std::vector<std::shared_ptr<Directory>> directories;
    std::vector<std::shared_ptr<File>> realFiles;
    std::vector<std::shared_ptr<File>> fakedFiles;
    string currentPath;
    std::shared_ptr<Directory> root;

public:
    Directory(std::string name, double size);
    ~Directory();
    virtual bool createDirectory(const std::string& directoryName);
    string getName();
    void listContents() const;
    void listSimulatedFiles() const;
    void clearContents();
    void sortByName();
    bool deleteItem(const std::string& name);
    const std::vector<std::shared_ptr<Directory>>& getDirectories() const;
    bool fileExists(const std::string& fileName) const;
    virtual bool browseThroughDirectories(const string& cmd, const string& rootPath);
    void addRealFile(const std::shared_ptr<File>& realFile); // Function to add real files
    void addSimulatedFile(const std::shared_ptr<File>& simulatedFile); // Function to add simulated files
    const std::vector<std::shared_ptr<File>>& getRealFiles() const; // Function to get real files
    const std::vector<std::shared_ptr<File>>& getSimulatedFiles() const; // Function to get simulated files
    void addFileToMemory(const std::shared_ptr<File>& file);
    void addDirectoryToMemory(const std::shared_ptr<Directory>& directory);
};

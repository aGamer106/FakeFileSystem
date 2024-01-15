#include <crtdbg.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <filesystem>  // file system needs cpp standard 17 or above.  This is enabled in this project, but if you recreated from scratch, set -std=c++17 flags
#include "ExistingItem.h";
#include "File.h";

using namespace std;




// C++ entry point
int main()
{
#ifdef _DEBUG
  // make sure we are checking for memory leaks when the application ends, but only in the _DEBUG variant
  _onexit(_CrtDumpMemoryLeaks);
#endif

  // root path to enumerate
  // CHANGE PATH IF DEVELOPING / TESTING ON ANOTHER PC!!!!
  const string path="C:\\Users\\User\\Desktop\\DummyData"; // this is just the local path, so the project's data folder; UPDATE IF ON OTHER MACHINE;

  ExistingItem *root = new ExistingItem(path, "root_timestamp", 0.0);

  root->listDirectories(path);
  root->searchDirectory(path);
  root->navigate();

  delete root;


  return 0;
}


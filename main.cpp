#pragma once
#include <crtdbg.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <filesystem>  // file system needs cpp standard 17 or above.  This is enabled in this project, but if you recreated from scratch, set -std=c++17 flags
#include "ExistingItem.h";
#include "File.h";
#include "Directory.h"

using namespace std;


//This is the final version completely adapted. The previous version was
//handling all commands perfectly however it was touching and working
//with the real files inside the folder instead of in-memory instances.


// C++ entry point
int main()
{
#ifdef _DEBUG
  // make sure we are checking for memory leaks when the application ends, but only in the _DEBUG variant
  _onexit(_CrtDumpMemoryLeaks);
#endif

  // root path to enumerate
  const string path="C:\\Users\\User\\Desktop\\DummyData"; // this is just the local path, so the project's data folder; UPDATE IF ON OTHER MACHINE;

  ExistingItem *root = new ExistingItem(path, "root_timestamp", 0.0);

  root->listDirectories(path);
  root->searchDirectory(path);
  root->navigate();

  delete root;


  return 0;
}


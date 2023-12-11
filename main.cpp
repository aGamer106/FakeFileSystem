/*
 * This is the starting project for the Advanced Programming assessment - 2023-4
 * This project enumerates just the directory specified and does not descend into subdirectories
*/

#include <crtdbg.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <filesystem>  // file system needs cpp standard 17 or above.  This is enabled in this project, but if you recreated from scratch, set -std=c++17 flags

using namespace std;

// function prototype of a helper method to convert timestamps
const tm convertTime(const filesystem::file_time_type& timestamp);


static void searchDirectory(string path) {
	for (const filesystem::directory_entry& item : filesystem::directory_iterator(path)) {
		if (item.is_directory()) {
			path = item.path().string();
			std::cout << path << "\n";
			searchDirectory(path);
		}
		else {
			std::cout << item.path().string() << endl;
		}
	}
}


// C++ entry point
int main()
{
#ifdef _DEBUG
  // make sure we are checking for memory leaks when the application ends, but only in the _DEBUG variant
  _onexit(_CrtDumpMemoryLeaks);
#endif




  // root path to enumerate
  const string path="C:\\Users\\User\\Desktop\\DummyData"; // this is just the local path, so the project folder
  searchDirectory(path);

  //ca idee - pot sa imi fac un meniu folosind un "switch statement"
  //care sa traverseze printre toate directoarele, asadar
  //chemand toate functiile necesare respecting the commands 














  //cout << "Here is a list of files in " << path << "\n\n";

  //// use an implicit iterator to enumerate the path
  //for (const filesystem::directory_entry& item : filesystem::directory_iterator(path))
  //{
  //  if (item.is_directory()) // check if this is a directory
  //  {
  //    // get and display the name of the current item
  //    string name=item.path().filename().string();
  //    cout << "A directory called " << name;
  //    
  //    // get the timestamp into a format that allows us to manage it
  //    tm timestamp=convertTime(item.last_write_time());
  //    cout << " timestamp: ";
  //    cout << "Year: " << (timestamp.tm_year+1900); // tm_year start at 0 for 1900 so add 1900
  //    cout << " Month: " << (timestamp.tm_mon+1); // tm_mon starts at 0 for January so add 1
  //    cout << " Day: " << timestamp.tm_mday;
  //    cout << " Hour: " << timestamp.tm_hour;
  //    cout << " Min: " << timestamp.tm_hour;
  //    cout << "\n";
  //  }
  //  else
  //  {
  //    // another way to get at the data held in the filename as a c-string (array of characters)
  //    string tmp=item.path().filename().string();
  //    const char* name=tmp.c_str();

  //    cout << "A file called " << name;

  //    // get the size of the file - __int64 is just an integer value, but using 64 bits to store it (8 bytes)
  //    __int64 filesize=item.file_size();
  //    cout << " size: " << filesize;
  //    cout << "\n";
  //  }
  //}

  return 0;
}

// we need to do a little conversion between what the filesystem returns for time stamps and something usable
// just use this function and don't worry about how it works
const tm convertTime(const filesystem::file_time_type& timestamp)
{
  using namespace chrono;  // just for this function, use chrono to save us prefixing chrono:: everywhere
  system_clock::time_point delta=time_point_cast<system_clock::duration>(timestamp-filesystem::file_time_type::clock::now()+system_clock::now());
  time_t conversion=system_clock::to_time_t(delta);

  tm result;
  localtime_s(&result, &conversion);
  return result;
}




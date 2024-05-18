#ifndef FILE_MANIPULATOR_HPP
#define FILE_MANIPULATOR_HPP

#include <iostream>
#include <fstream>
#include <string>
// Für tests
#include <sstream>


#include "directory.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

// Wenn sich Header gegenseitig inkludieren dann Vorwärtsdeklaration benutzen 
class Directory;

// Diese Funktion liest den Text aus einer gegebenen Datei
// und gibt diesen als String zurück
string readAndReturn(string path);

// Die Funktion schreibt den genommen Text in einen neuen File
// auf dem genommenen Path
void writeToFile(string path, string text, string filename);

#endif
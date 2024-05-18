#ifndef SAVE_HPP
#define SAVE_HPP

#include <iostream>
#include "directory.hpp"


void saveApiKeyToFile(const string apiKey);

string readApiKeyFromFile();

#endif
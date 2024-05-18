#ifndef PROMPT_HPP
#define PROMPT_HPP

#include "directory.hpp"

// Alle Codes aus dem genommenem Directory werden in dieser Funktion in eine struktorierte Form gebracht z.b:
// 
// complex.hpp:
// 
// ......
// 
// 
// complex.cpp:
//
// ......
// 
// 
// main.cpp:
// 
// ......
// 
// 
// makefile: 
// 
// ......
string createPrompt(Directory dir);

// Nimmt eine Datei und komprimiert diese so das nur noch die includes 
// exestieren. Diese Funktion nimmt einen fertigen Prompt aus create
// Prompt und löscht alle Zeilen die nicht mit # (includes) oder mit - (Zeichen für erkennbare
// Trennung von files) beginnen. Makefiles werden ganz gelassen
string extractIncludes(const string fileContents, Directory dir);


// Nimmt eine Datei und komprimiert diese so das nur noch die includes 
// exestieren. Diese Funktion nimmt einen fertigen Prompt aus create
// Prompt und löscht alle Zeilen die nicht mit # (includes) oder mit - (Zeichen für erkennbare
// Trennung von files) beginnen. Make files werden ganz gelassen
string makelegitPrompt(string prompt, Directory dir);
int countWords(const std::string& input);

#endif
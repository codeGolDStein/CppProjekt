#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <iostream>
#include <string>
#include <vector>
#include <experimental/filesystem> 
#include <unordered_map>
#include <cstdlib> 

#include "file_manipulator.hpp"

using std::string;
using std::vector;
using std::pair;
using std::unordered_map;
namespace fs = std::experimental::filesystem;

// In diesem struct werden die eingelesenen Files gespeichert
struct FileEntry{
    string name;
    string type;
    bool isDirectory;
    string text;
};


// Diese klasse repräsentiert die Struktur Projekts/Directorys auf
// mehrere Art und Weisen
class Directory{
  private: 
    string path;

    // In diesem Vector liegen alle Files und Ordner unsortiert
    vector<FileEntry> unsorted;

    // Hier wird alles erstmal nach Ordner oder File sortiert und die Files 
    // werden dann noch nach ihrem type sortiert also cpp oder hpp. 
    // Der Grund für diese Strukur ist das man Später dem Benutzer ein Sortierte
    // Übersicht zu dem Directory geben kann.  
    // Ich habe ein Pair verwendet da man Erstmal in Datei und Ordner unterscheidet
    //                          "hpp": ["complex"....]               Alle Ordner
    pair<unordered_map<string, vector<FileEntry>>, vector<FileEntry>> sortedByType;
    // Ich muss mich noch genauer um die Grenzfälle kümmern wie die makefiles oder die
    // main Dateien. Ich bin auch am überlegen den Vector für die Ordner raus zunehmen,
    // da es ja eigentlich Voraussetzung ist das das Projekt den Aufbau eines Übungsblattes 
    // hat.

    // Diese Struktur ist für ChatGPT Eingabe später.
    pair<vector<pair<FileEntry, FileEntry>>, vector<FileEntry>> sortedByPair;

  public:
    // Mit der Erstellung einer Instanz werden mit den Funktionen unten
    // direkt alle Member initialisiert.
    Directory(string givenPath){
      path = givenPath;
      fillFilesandFolders(givenPath);
      sortByType(unsorted);
      sortByPair(unsorted);
    }

    // MIt diesen Funktionen wird die Klasse aufgebaut:
    void fillFilesandFolders(const string path);
    void sortByType(const vector<FileEntry> unsorted);
    void sortByPair(const vector<FileEntry> unsorted);

    // Getter Funktionen 
    string getPath();
    FileEntry getFile(string filename);
    vector<FileEntry> getUnsorted();
    pair<unordered_map<string, vector<FileEntry>>, vector<FileEntry>> getSortedByType();
    pair<vector<pair<FileEntry, FileEntry>>, vector<FileEntry>> getSortedByPair();

};

#endif

#include "directory.hpp"

void Directory::fillFilesandFolders(const string path)
{
    vector<FileEntry> result;

    // Iterating throu the given Path and adding all file names to result
    for (const auto &entry : fs::directory_iterator(path))
    {
        // directory_iterator gives back an directory_entry object
        // which contains informations like the filename, size and
        // the timestomp of the file.
        FileEntry fileEntry;

        // Get name with out the Type:
        string fullName = entry.path().filename().string();
        size_t dotPosition = fullName.find('.');
        if (dotPosition != string::npos)
        {
            // Extrahieren des Teilstrings vor dem Punkt
            string subString = fullName.substr(0, dotPosition);
            fileEntry.name = subString;
        }
        else
        {
            // Der Geprüfte File hat keinen Punkt z.b. Makefile
            fileEntry.name = fullName;
        }

        fileEntry.isDirectory = fs::is_directory(entry);

        // std::cout << fileEntry.name << "\n" << std::endl;

        if (!fileEntry.isDirectory)
        {
            fileEntry.type = entry.path().extension().string();
            // fileEntry.text = readAndReturn(entry.path().filename().string());                  clean
            fileEntry.text = readAndReturn(path + "/" + fileEntry.name + fileEntry.type);
            // std::cout << fileEntry.text << "\n\n" << std::endl;                                clean
        }

        result.push_back(fileEntry);
    }

    unsorted = result;
}

void Directory::sortByType(const vector<FileEntry> unsorted)
{
    pair<unordered_map<string, vector<FileEntry>>, vector<FileEntry>> result;

    for (const FileEntry entry : unsorted)
    {
        if (entry.isDirectory)
        {
            result.second.push_back(entry);
        }
        else
        {
            result.first[entry.type].push_back(entry);
        }
    };

    sortedByType = result;
}

void Directory::sortByPair(const vector<FileEntry> unsorted)
{

    // Die Funktion sortiert die FileEntrys so das sie später schnell in einem
    // struktorierten Format in eine Textdatei einfügen kann und dann an ChatGPT sendet.
    // In einem Pair befindet sich immer  die .hpp Datei als erstes
    // Es wird als erstes nach files gesucht die einen gleichen Namen haben als z.b.
    // bdd.hpp und bdd.cpp diese werden dann in den Pair Vektor eingefügt. Die files
    // die keinen Partner haben werden kommen dann in den 2ten Vektor.

    //                                     Paare                   keine Paare
    pair<vector<pair<FileEntry, FileEntry>>, vector<FileEntry>> result;
    int index = 0;

    unordered_map<string, vector<FileEntry>> fileGroups;

    // Alle Dateien werden sortiert nach ihren Namen in ein dict
    // geschoben z.B. complex -> [complex.cpp, complex.hpp]
    for (const FileEntry file : unsorted)
    {
        fileGroups[file.name].push_back(file);
    }

    for (const auto pair : fileGroups)
    {

        vector<FileEntry> group;

        // Hier werden die Files raus gefiltert die keine Paare haben
        // also Ordner, makefiles oder Main Dateien,
        if (pair.second.size() != 2)
        {
            // zb makefiles oder mains
            for (FileEntry entry : pair.second)
            {
                result.second.push_back(entry);
            }
            continue;
        };

        // Alle Paar Datein werden in diesem pair zusammengesetzt und dann
        // in result eingefügt
        std::pair<FileEntry, FileEntry> filepair;

        // Hier wird geschaut ob das hpp oder cpp File zu erst ist
        // falls nötig wird getauscht.
        if (pair.second[0].type == ".hpp" || pair.second[0].type == ".h")
        {
            filepair.first = pair.second[0];
            filepair.second = pair.second[1];
        }
        else
        {
            filepair.first = pair.second[1];
            filepair.second = pair.second[0];
        }

        result.first.push_back(filepair);
    }

    sortedByPair = result;
}

// Getter Funktionen:

string Directory::getPath()
{
    return path;
}

FileEntry Directory::getFile(string filename)
{
    for (FileEntry entry : unsorted)
    {
        if (entry.name == filename)
        {
            return entry;
        }
    }
    FileEntry fail = FileEntry();
    fail.name = "notfound";
    return fail; // Nicht gefunden!!
}

vector<FileEntry> Directory::getUnsorted()
{
    return unsorted;
}
pair<std::unordered_map<string, vector<FileEntry>>, vector<FileEntry>> Directory::getSortedByType()
{
    return sortedByType;
}
pair<vector<pair<FileEntry, FileEntry>>, vector<FileEntry>> Directory::getSortedByPair()
{
    return sortedByPair;
}
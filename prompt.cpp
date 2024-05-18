
#include "prompt.hpp"

string createPrompt(Directory dir)
{
    string result;

    // std::cout << dir.getSortedByPair().first.size() << std::endl;

    // std::cout << dir.getSortedByPair().second.size() << std::endl;

    for (const pair<FileEntry, FileEntry> pair : dir.getSortedByPair().first)
    {
        // hpp:             complex              hpp
        string firstname = "-------- " + pair.first.name + pair.first.type + ": \n ";
        string firstcode = pair.first.text + "\n \n";

        // cpp:              complex                cpp
        string secondname = "-------- " + pair.second.name + pair.second.type + ": \n \n"; // Warum 2
        string secondcode = pair.second.text + "\n \n";

        result = result + firstname + firstcode + secondname + secondcode;
    }

    for (const FileEntry entry : dir.getSortedByPair().second)
    {
        string name = "-------- " + entry.name + entry.type + ": \n \n ";
        string code = entry.text + "\n \n";

        result = result + name + code;
    }

    return result;
}

string extractIncludes(const string fileContents, Directory dir)
// Es wird das Directory übergeben um Files die nicht gelöscht werden
// sollen zu übergeben
{
    std::stringstream iss(fileContents);
    vector<string> includeLines;

    string line;
    while (std::getline(iss, line))
    {
        size_t startPos = line.find_first_not_of(" \t"); // zum ignorieren von Leerzeichen
        if (startPos != string::npos && (line[startPos] == '#' || line[startPos] == '-'))
        {   // überprüfen ob die Zeile mit # oder - beginnt

            // Es kann sein das die Zeile so aussieht "------- makefile:" In so einem Fall sollen die Zeilen
            // die danach kommen nicht gelöcht da wir das makefile trotz komprimierung mitsenden wollen
            if(line.find("makefile") != string::npos || line.find("Makefile") != string::npos){
                // Makefile anhängen da dieser ja nicht weggelassen werden soll
                if(dir.getFile("Makefile").name == "notfound"){
                    string makefilecontent = dir.getFile("makefile").text;
                    line = line + "\n" + makefilecontent;
                }else{
                    string makefilecontent = dir.getFile("Makefile").text;
                    line = line + "\n" + makefilecontent;
                } 
            }
            includeLines.push_back(line);   
        }
        
    }

    // Verbinde die Zeilen wieder zu einem String
    std::ostringstream oss;
    for (const auto includeLine : includeLines)
    {
        oss << includeLine << '\n';
    }

    // std::cout << oss.str() << std::endl;

    return oss.str();
}


int countWords(const string& input) {
    std::stringstream ss(input); // String in einen stringstream einfügen
    string word;
    int wordCount = 0;

    while (ss >> word) {
        wordCount++;
    }

    return wordCount;
}


string makelegitPrompt(string prompt, Directory dir){
    // dir wird nur mit gegeben da es sein kann 
    // das extractIncludes(prompt, dir); es braucht

    if(countWords(prompt) >= 1500){
        return extractIncludes(prompt, dir);
    }
}

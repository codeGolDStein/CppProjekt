// Copyright 2023, University of Freiburg 
// Author: Alex Greb

#include "apiservice.hpp"
#include "directory.hpp"
#include "file_manipulator.hpp"
#include "save.hpp"
#include "ui.hpp"
#include "prompt.hpp"

using std::getline;

int main()
{
    // API Key einrichten:
    // Hat Der User keinen wird ein Dokument formatiert was er
    // selber prompten kann
    string apiKey;
    if (readApiKeyFromFile() == "")
    {
        string input;
        cout << "Hast Du einen Api_Key? [y/n]: ";
        getline(cin, input);
        cout << "\n";
        if (input == "y" || input == "Y")
        {
            string key;
            cout << "Api_Key: ";
            getline(cin, key);
            cout << "\n";
            saveApiKeyToFile(key);
            apiKey = readApiKeyFromFile();
        }
        else
        {
            cout << "Da du keinen API-Key hast werden keine Anfragen an ChatGPT gesendet.\nJedoch wird der Ein Prompt, angepasst auf dein Projekt in einem Textdokument gespeichert";
            cout << "\n \n";
        }
    }
    else
    {
        apiKey = readApiKeyFromFile();
    }


    // Path zum Projekt wird von User genommen:
    std::string path;
    std::cout << "Path zum Projekt an: ";
    std::getline(std::cin, path);
    std::cout << "\n";

    // Das ist das Directory mit dem Projekt:
    Directory dir = Directory(path);

    // Dem User wird eine Übersicht über sein Projekt gegeben:
    printDir(dir);
    std::cout << "\n \n";

    // Erstellen des Promptes:
    string comment;
    std::cout << "Kommentar zum Projekt: ";
    std::getline(std::cin, comment);
    string prompt = createPrompt(dir);
    string legitPrompt = makelegitPrompt(prompt, dir) + "\n\n" +comment;
    std::cout << "\n \n";

    if(apiKey == ""){
        string input;
        cout << "Willst du deinen Prompt in einer .txt Datei Speichern? [y/n]:";
        getline(cin, input);
        cout << "\n";
        if (input == "y" || input == "Y"){
            string path;
            cout << "Path: ";
            getline(cin, input);
            cout << "\n";

            writeToFile(path, legitPrompt, "legitPrompt.txt");
            return 0;
        }

        cout << "\n \n" << endl;
        cout << "Komprimiert:" << endl;
        cout << legitPrompt << endl;
        cout << "\n \n \n" << endl;

        cout << "Normal:" << endl;
        cout << prompt << endl;
        cout << "\n \n \n" << endl;
        return 0;
    }

    // Erhalten der Antwort:
    string response = getCompletion(legitPrompt, apiKey);

    // Ausgeben der Antwort:
    prettyResponse(response);

    return 0;
}


#include "file_manipulator.hpp"


string readAndReturn(string path)
{
    ifstream file(path);
    if (!file)
    {
        cerr << "Fehler beim Öffnen der Datei: " << path << endl;
        return ""; // Leerer String bei Fehler zurückgeben
    }

    string text;
    string line;
    while (std::getline(file, line))
    {
        text += line + "\n"; // Füge die gelesene Zeile und einen Zeilenumbruch zum Text hinzu
    }

    file.close();
    return text;
};


void writeToFile(string path, string text, string filename)
{
    std::ofstream outputFile(path + "/" + filename); // Pfad zum Dokument und Dateiname
    if (outputFile.is_open())
    {
        outputFile << text;
        outputFile.close();
        cout << "Das Textdokument wurde erfolgreich erstellt." << endl;
    }
    else
    {
        cerr << "Fehler beim Erstellen des Textdokuments." << endl;
    }
}









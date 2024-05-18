#include "save.hpp"

void saveApiKeyToFile(const string apiKey)
{
    std::ofstream file("apikey.txt");
    if (file.is_open())
    {
        file << apiKey;
        file.close();
        cout << "API-Schlüssel wurde erfolgreich gespeichert.\n";
        cout << "\n";
    }
    else
    {
        cerr << "Fehler beim Speichern des API-Schlüssels in die Datei.\n";
    }
}

string readApiKeyFromFile()
{
    std::ifstream file("apikey.txt");
    string apiKey;
    if (file.is_open())
    {
        std::getline(file, apiKey);
        file.close();
    }
    return apiKey;
}
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>

using std::string;

// Hier den Dateinamen angeben, der in der saveApiKeyToFile-Funktion verwendet wird.
const string apiKeyFileName = "test_api_key.txt";

// Deklaration der Funktionen, die wir testen wollen
void saveApiKeyToFile(const std::string apiKey);
std::string readApiKeyFromFile();

TEST(SaveApiKeyToFileTest, SaveApiKeyToFile_Success)
{
    const std::string apiKey = "test-api-key";

    // API-Schlüssel in die Datei speichern
    saveApiKeyToFile(apiKey);

    // Datei lesen und überprüfen, ob der gespeicherte API-Schlüssel korrekt ist
    std::ifstream file(apiKeyFileName);
    std::string readApiKey;
    if (file.is_open())
    {
        std::getline(file, readApiKey);
        file.close();
    }

    ASSERT_EQ(apiKey, readApiKey);
}

TEST(ReadApiKeyTest, FileExists)
{
    // Testvorbereitung: Eine temporäre Testdatei erstellen
    std::ofstream testFile("apikey.txt");
    testFile << "my_test_api_key" << std::endl;
    testFile.close();

    // Funktion aufrufen und das Ergebnis überprüfen
    std::string apiKey = readApiKeyFromFile();
    ASSERT_EQ(apiKey, "my_test_api_key");

    // Die temporäre Testdatei löschen
    remove("apikey.txt");
}



// Dateien löschen, die im Testfall erstellt wurden
void deleteTestFiles()
{
    std::remove("apikey.txt");
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    int testResult = RUN_ALL_TESTS();
    
    // Dateien löschen, die im Testfall erstellt wurden
    deleteTestFiles();
    
    return testResult;
}

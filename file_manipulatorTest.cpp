#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <experimental/filesystem> 

using std::string;
namespace fs = std::experimental::filesystem;

string readAndReturn(string path);
void writeToFile(std::string path, std::string text, std::string filename);

// Test für readAndReturn function:
TEST(ReadAndReturnTest, TestValidFile)
{
    string test_file_path = "readAndReturn.txt";
    string expected_text = "Test 1\nTest 2\nTest 3\n";

    // Testfile erstellen und etwas reinschreiben:
    std::ofstream file(test_file_path);
    file << expected_text;
    file.close();

    string result = readAndReturn(test_file_path);

    EXPECT_EQ(result, expected_text);

    // Zum entfernen des Testfiles
    std::remove(test_file_path.c_str());
}


TEST(WriteToFileTest, TestWriteToFile)
{
    string test_dir_path = "test_dir";
    string test_file_name = "test_file.txt";
    string expected_text = "Das ist ein Text.";

    // Damit wird der path für den Parameter der Funktion erstellt 
    fs::create_directory(test_dir_path);

    // Ausführen
    writeToFile(test_dir_path, expected_text, test_file_name);

    // Assert:
    std::ifstream file(test_dir_path + "/" + test_file_name);
    EXPECT_TRUE(file.is_open());
    if (file.is_open())
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        string file_content = buffer.str();
        EXPECT_EQ(file_content, expected_text) << "Keine Übereinstimmung bei writeToFileTest";
        file.close();
    }

    // Clean
    fs::remove_all(test_dir_path);
}
















int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

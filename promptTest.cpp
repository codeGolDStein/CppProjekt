#include <gtest/gtest.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "directory.hpp"


string createPrompt(Directory dir);
string extractIncludes(const std::string fileContents, Directory dir);
int countWords(const std::string& input);
std::string makelegitPrompt(std::string prompt, Directory dir);


// Test case for createPrompt function
TEST(CreatePromptTest, TestCreatePrompt)
{

    fs::create_directory("test_dir");

    Directory testDirectory("test_dir");

    FileEntry entry1{ "file1", ".hpp", false, "..." };
    FileEntry entry2{ "file1", ".cpp", false, "..." };
    FileEntry entry3{ "file2", ".cpp", false, "..." };
    FileEntry entry4{ "file3", ".txt", false, "..." };

    testDirectory.getSortedByPair().first.push_back(std::make_pair(entry1, entry2));
    testDirectory.getSortedByPair().first.push_back(std::make_pair(entry2, entry3));
    testDirectory.getSortedByPair().second.push_back(entry4);

    // Aussführen
    std::string result = createPrompt(testDirectory);

    // Check
    std::string expectedOutput =
        "-------- file1.hpp: \n ... \n \n"
        "-------- file1.cpp: \n ... \n \n"
        "-------- file2.cpp: \n ... \n \n"
        "-------- file3.txt: \n ... \n \n";

    EXPECT_EQ(result, expectedOutput) << "Keine Übereinstimmung";

    // Keine Ahnung warum der Test nicht funktioniert
}


TEST(CountWordsTest, TestCountWords)
{
    string input1 = "Das ist ein Test";
    string input2 = "Moin";
    string input3 = " ";

    int wordCount1 = countWords(input1);
    int wordCount2 = countWords(input2);
    int wordCount3 = countWords(input3);

    EXPECT_EQ(wordCount1, 4) << "Incorrect word count for input1.";
    EXPECT_EQ(wordCount2, 1) << "Incorrect word count for input2.";
    EXPECT_EQ(wordCount3, 0) << "Incorrect word count for input3.";

}




int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

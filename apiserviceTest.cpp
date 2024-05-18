#include "apiservice.hpp" 
#include "gtest/gtest.h"

TEST(GetCompletionTest1, BasicTest) {
    // Test 1:
    std::string prompt = "Antworte mit: Das ist ein Test";
    std::string result = getCompletion(prompt, "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");
    EXPECT_EQ(result, "Das ist ein Test.");


}

TEST(GetCompletionTest2, BasicTest) {
    // Test 2:
    std::string prompt = "Was ist 2*3? Gebe nur die Ergebnisszahl";
    std::string result = getCompletion(prompt, "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");
    EXPECT_EQ(result, "6");
}

 
int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
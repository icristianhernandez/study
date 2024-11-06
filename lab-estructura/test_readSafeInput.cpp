#include "ConsoleUtils.h"
#include <cassert>
#include <iostream>
#include <sstream>

void test_readSafeInput() {
    // Redirect cin to use a stringstream
    std::istringstream input_stream;
    std::streambuf *original_cin = std::cin.rdbuf(input_stream.rdbuf());

    // Test case 1: Valid integer input
    input_stream.str("42\n");
    auto [value1, isValid1] = readSafeInput<int>();
    assert(isValid1 == true);
    assert(value1 == 42);

    // Test case 2: Invalid integer input
    input_stream.clear();
    input_stream.str("invalid\n");
    auto [value2, isValid2] = readSafeInput<int>();
    assert(isValid2 == false);

    // Test case 3: Valid float input
    input_stream.clear();
    input_stream.str("3.14\n");
    auto [value3, isValid3] = readSafeInput<float>();
    assert(isValid3 == true);
    assert(value3 == 3.14f);

    // Test case 4: Invalid float input
    input_stream.clear();
    input_stream.str("invalid\n");
    auto [value4, isValid4] = readSafeInput<float>();
    assert(isValid4 == false);

    // Test case 5: Valid string input
    input_stream.clear();
    input_stream.str("hello\n");
    auto [value5, isValid5] = readSafeInput<std::string>();
    assert(isValid5 == true);
    assert(value5 == "hello");

    // Test case 6: Empty input
    input_stream.clear();
    input_stream.str("\n");
    auto [value6, isValid6] = readSafeInput<int>();
    assert(isValid6 == false);

    // Test case 7: String of varios words
    input_stream.clear();
    input_stream.str("Hello, World!\n");
    auto [value7, isValid7] = readSafeInput<std::string>();
    assert(isValid7 == true);

    // Restore original cin
    std::cin.rdbuf(original_cin);

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    test_readSafeInput();
    return 0;
}

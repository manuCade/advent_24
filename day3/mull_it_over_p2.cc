// --- Part Two ---

// As you scan through the corrupted memory, you notice that some of the conditional statements are also still intact. If you handle some of the uncorrupted conditional statements in the program, you might be able to get an even more accurate result.
// There are two new instructions you'll need to handle:
//     The do() instruction enables future mul instructions.
//     The don't() instruction disables future mul instructions.
// Only the most recent do() or don't() instruction applies. At the beginning of the program, mul instructions are enabled.
// For example:
// xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))
// This corrupted memory is similar to the example from before, but this time the mul(5,5) and mul(11,8) instructions are disabled because there is a don't() instruction before them. The other mul instructions function normally, including the one at the end that gets re-enabled by a do() instruction.
// This time, the sum of the results is 48 (2*4 + 8*5).
// Handle the new instructions; what do you get if you add up all of the results of just the enabled multiplications?

#include <iostream>
#include <string>
#include <regex>

int main(int argc, char* argv[]) {
  char c{};
  std::string text{};
  while (std::cin >> c) text += c;
  std::string line;
  std::regex mul_parentheses(R"((do\(\))|(don't\(\))|(mul\((\d+),(\d+)\)))");
  bool enabled{true};
  auto begin = std::sregex_iterator(text.begin(), text.end(), mul_parentheses);
  auto end = std::sregex_iterator();
  long int multiplication{0};
  for (std::sregex_iterator i{begin}; i != end; ++i) {
      std::smatch match = *i;
      if (match[0].str().starts_with("don't")) {
        enabled = false;
        continue;
      }
      if (match[0].str().starts_with("do")) {
        enabled = true;
        continue;
      }
      if (enabled) {
        multiplication += std::stoi(match[4].str()) * std::stoi(match[5].str());
      }
  }
  std::cout << multiplication << std::endl;
}
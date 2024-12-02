// --- Part Two ---

// The engineers are surprised by the low number of safe reports until they realize they forgot to tell you about the Problem Dampener.
// The Problem Dampener is a reactor-mounted module that lets the reactor safety systems tolerate a single bad level in what would otherwise be a safe report. It's like the bad level never happened!
// Now, the same rules apply as before, except if removing a single level from an unsafe report would make it safe, the report instead counts as safe.
// More of the above example's reports are now safe:
//     7 6 4 2 1: Safe without removing any level.
//     1 2 7 8 9: Unsafe regardless of which level is removed.
//     9 7 6 2 1: Unsafe regardless of which level is removed.
//     1 3 2 4 5: Safe by removing the second level, 3.
//     8 6 4 4 1: Safe by removing the third level, 4.
//     1 3 6 7 9: Safe without removing any level.
// Thanks to the Problem Dampener, 4 reports are actually safe!
// Update your analysis by handling situations where the Problem Dampener can remove a single level from unsafe reports. How many reports are now safe?

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int WhoBad(const std::vector<int>& list) {
  bool increasing{false}, decreasing{false};
  for (size_t i{0}; i < list.size() - 1; ++i) {
    int prev_num{list[i]}, num{list[i + 1]};
    if (prev_num - num > 0) {
      if (increasing) return i + 1;
      decreasing = true;
    } else if (prev_num - num < 0) {
      if (decreasing) return i + 1;
      increasing = true;
    }
    const int distance{std::abs(prev_num - num)};
    if (distance < 1 || distance > 3) return i + 1;
    prev_num = num;
  }
  return -1;
}



int main(int argc, char* argv[]) {
  int safety_reports{0};
  std::string input_file{argv[1]};
  std::ifstream file(input_file);
  std::string line{};
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::vector<int> list{};
    int num{};
    while (iss >> num) {
      list.push_back(num);
    }
    for (size_t i{0}; i < list.size(); ++i) {
      std::vector<int> minus_one_list = list;
      minus_one_list.erase(minus_one_list.begin() + i);
      if (WhoBad(minus_one_list) == -1) {
        ++safety_reports;
        break;
      }
    }
  }
  std::cout << safety_reports << std::endl;
}
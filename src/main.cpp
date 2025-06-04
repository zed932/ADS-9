#include "tree.h"
#include <vector>
#include <chrono>
#include <fstream>

int main() {
  std::vector<char> in = {'1', '3', '5', '7'};
  PMTree tree(in);

  std::ofstream results("/Users/zed932/Documents/Учеба/С++/ads9test/ads9test/experiement.csv");
  results << "Function,Size,Time (seconds)\n";

  auto start = std::chrono::high_resolution_clock::now();
  std::vector<std::vector<char>> perms = tree.getAllPerms();
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  results << "getAllPerms," << in.size() << "," << duration.count() << "\n";

  for (int i = 1; i <= perms.size(); ++i) {
    start = std::chrono::high_resolution_clock::now();
    std::vector<char> result1 = tree.getPerm1(i);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    results << "getPerm1," << in.size() << "," << duration.count() << "\n";
  }

  for (int i = 1; i <= perms.size(); ++i) {
    start = std::chrono::high_resolution_clock::now();
    std::vector<char> result2 = tree.getPerm2(i);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    results << "getPerm2," << in.size() << "," << duration.count() << "\n";
  }

  results.close();
  return 0;
}

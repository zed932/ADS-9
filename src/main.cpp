// Copyright 2022 NNTU-CS
#include <vector>
#include <chrono>
#include <fstream>
#include <random>
#include "tree.h"

int main() {
  const std::vector<int> sizes = {1, 2, 3, 4, 5, 6, 7, 8};
  std::ofstream results(
      "/Users/zed932/Documents/Учеба/С++/ads9test/ads9test/experiement.csv");
  results << "n,getAllPerms,getPerm1,getPerm2\n";

  for (int n : sizes) {
    std::vector<char> in;
    for (int i = 0; i < n; ++i) {
      in.push_back('1' + i);
    }

    PMTree tree(in);

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<char>> perms = getAllPerms(tree);
    auto end = std::chrono::high_resolution_clock::now();
    double duration_all = std::chrono::duration<double>(end - start).count();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(perms.size()) - 1);
    auto random_index = dist(gen);

    start = std::chrono::high_resolution_clock::now();
    std::vector<char> result1 = getPerm1(tree, random_index);
    end = std::chrono::high_resolution_clock::now();
    double duration1 = std::chrono::duration<double>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    std::vector<char> result2 = getPerm2(tree, random_index);
    end = std::chrono::high_resolution_clock::now();
    double duration2 = std::chrono::duration<double>(end - start).count();

    results << n << "," << duration_all << "," << duration1 << ","
            << duration2 << "\n";
  }

  results.close();
  return 0;
}

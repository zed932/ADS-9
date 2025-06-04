// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <vector>
#include "tree.h"

int main() {
  std::vector<char> symbols = {'1', '2', '3'};
  PermutationTree tree(symbols);

  auto perms = tree.getAllPermutations();
  std::cout << "Total permutations: " << perms.size() << "\n";

  std::ofstream dataFile("/Users/zed932/Documents/Учеба/С++/ads9test/ads9test/experiement.csv");
  dataFile << "n,getAllPermutations,getPermutationByIndex1,getPermutationByIndex2\n";

  std::random_device rd;
  std::mt19937 gen(rd());

  for (int n = 3; n <= 9; ++n) {
    auto testSymbols = generateSymbolSet(n);
    PermutationTree testTree(testSymbols);
    std::uniform_int_distribution<int> dist(1, testTree.getPermutationCount());
    int testIndex = dist(gen);

    auto start = std::chrono::high_resolution_clock::now();
    auto all = testTree.getAllPermutations();
    auto end = std::chrono::high_resolution_clock::now();
    double timeAll = std::chrono::duration<double>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    auto perm1 = testTree.getPermutationByIndex1(testIndex);
    end = std::chrono::high_resolution_clock::now();
    double time1 = std::chrono::duration<double>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    auto perm2 = testTree.getPermutationByIndex2(testIndex);
    end = std::chrono::high_resolution_clock::now();
    double time2 = std::chrono::duration<double>(end - start).count();

    dataFile << n << "," << timeAll << "," << time1 << "," << time2 << "\n";
  }

  dataFile.close();
  std::cout << "Experiment data saved to experiment.csv\n";
  return 0;
}

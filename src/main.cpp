// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>

int main() {
  std::vector<char> in = {'1', '2', '3'};
  PMTree tree(in);

  auto perms = tree.getAllPerms();
  for (const auto& perm : perms) {
    for (char c : perm) {
      std::cout << c;
    }
    std::cout << std::endl;
  }

  for (int i = 1; i <= 6; ++i) {
    auto perm1 = tree.getPerm1(i);
    auto perm2 = tree.getPerm2(i);
    for (char c : perm1) std::cout << c;
    std::cout << " ";
    for (char c : perm2) std::cout << c;
    std::cout << std::endl;
  }

  return 0;
}

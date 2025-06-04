// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMTree {
 public:
  struct Node {
    char value;
    std::vector<std::shared_ptr<Node>> children;
    explicit Node(char val) : value(val) {}
  };

  explicit PMTree(const std::vector<char>& elements);
  std::vector<std::vector<char>> getAllPerms() const;
  std::vector<char> getPerm1(int num) const;
  std::vector<char> getPerm2(int num) const;
  size_t getTotalPermutations() const;

 private:
  std::shared_ptr<Node> root;
  size_t total_permutations;

  void buildTree(std::shared_ptr<Node> parent,
                 const std::vector<char>& remaining);
};

#endif  // INCLUDE_TREE_H_

// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PermutationTree {
 public:
  struct TreeNode {
    char value;
    std::vector<std::shared_ptr<TreeNode>> children;
    explicit TreeNode(char val) : value(val) {}
  };

  explicit PermutationTree(const std::vector<char>& symbols);
  std::vector<std::vector<char>> getAllPermutations() const;
  std::vector<char> getPermutationByIndex1(int index) const;
  std::vector<char> getPermutationByIndex2(int index) const;
  int getPermutationCount() const;

 private:
  std::shared_ptr<TreeNode> root;
  int permutationCount;

  void buildTree(std::shared_ptr<TreeNode> node,
                const std::vector<char>& remaining);
};

std::vector<char> generateSymbolSet(int size);

#endif  // INCLUDE_TREE_H_

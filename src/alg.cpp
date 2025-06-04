// Copyright 2022 NNTU-CS
#include "tree.h"

void collectPermutations(const std::shared_ptr<PermutationTree::TreeNode>& node,
                        std::vector<char>& current,
                        std::vector<std::vector<char>>& result) {
  if (node->value != '\0') {
    current.push_back(node->value);
  }

  if (node->children.empty()) {
    if (!current.empty()) {
      result.push_back(current);
    }
  } else {
    for (const auto& child : node->children) {
      collectPermutations(child, current, result);
    }
  }

  if (node->value != '\0') {
    current.pop_back();
  }
}

PermutationTree::PermutationTree(const std::vector<char>& symbols) {
  if (symbols.empty()) {
    root = nullptr;
    permutationCount = 0;
    return;
  }

  permutationCount = 1;
  for (size_t i = 1; i <= symbols.size(); ++i) {
    permutationCount *= i;
  }

  root = std::make_shared<TreeNode>('\0');
  buildTree(root, symbols);
}

void PermutationTree::buildTree(std::shared_ptr<TreeNode> node,
                              const std::vector<char>& remaining) {
  for (size_t i = 0; i < remaining.size(); ++i) {
    auto child = std::make_shared<TreeNode>(remaining[i]);
    node->children.push_back(child);

    std::vector<char> newRemaining;
    for (size_t j = 0; j < remaining.size(); ++j) {
      if (j != i) {
        newRemaining.push_back(remaining[j]);
      }
    }
    buildTree(child, newRemaining);
  }
}

std::vector<std::vector<char>> PermutationTree::getAllPermutations() const {
  std::vector<std::vector<char>> result;
  if (!root) {
    return result;
  }
  std::vector<char> current;
  collectPermutations(root, current, result);
  return result;
}

std::vector<char> PermutationTree::getPermutationByIndex1(int index) const {
  if (index < 1 || index > permutationCount) {
    return {};
  }
  auto allPerms = getAllPermutations();
  return allPerms[index - 1];
}

std::vector<char> PermutationTree::getPermutationByIndex2(int index) const {
  if (index < 1 || index > permutationCount) {
    return {};
  }

  std::vector<char> result;
  auto currentNode = root;
  int remainingIndex = index - 1;

  while (!currentNode->children.empty()) {
    int branchSize = 1;
    for (int i = 2; i <= static_cast<int>(currentNode->children.size()); ++i) {
      branchSize *= i;
    }
    branchSize /= currentNode->children.size();

    int selected = remainingIndex / branchSize;
    result.push_back(currentNode->children[selected]->value);
    remainingIndex %= branchSize;
    currentNode = currentNode->children[selected];
  }

  return result;
}

int PermutationTree::getPermutationCount() const {
  return permutationCount;
}

std::vector<char> generateSymbolSet(int size) {
  std::vector<char> symbols;
  for (int i = 0; i < size; ++i) {
    symbols.push_back('1' + i);
  }
  return symbols;
}

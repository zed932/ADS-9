// Copyright 2022 NNTU-CS
#include "tree.h"
#include <vector>
#include <memory>

PMTree::PMTree(const std::vector<char>& elements) {
  if (elements.empty()) {
    root = nullptr;
    total_permutations = 0;
    return;
  }

  total_permutations = 1;
  for (size_t i = 1; i <= elements.size(); ++i) {
    total_permutations *= i;
  }

  root = std::make_shared<Node>('\0');
  buildTree(root, elements);
}

void PMTree::buildTree(std::shared_ptr<Node> parent,
                       const std::vector<char>& remaining) {
  for (size_t i = 0; i < remaining.size(); ++i) {
    auto child = std::make_shared<Node>(remaining[i]);
    parent->children.push_back(child);

    std::vector<char> new_remaining;
    for (size_t j = 0; j < remaining.size(); ++j) {
      if (j != i) {
        new_remaining.push_back(remaining[j]);
      }
    }
    buildTree(child, new_remaining);
  }
}

void collectPermutations(const std::shared_ptr<PMTree::Node>& node,
                         std::vector<char>& current,
                         std::vector<std::vector<char>>& result) {
  if (node->value != '\0') {
    current.push_back(node->value);
  }

  if (node->children.empty()) {
    result.push_back(current);
  } else {
    for (const auto& child : node->children) {
      collectPermutations(child, current, result);
    }
  }

  if (node->value != '\0') {
    current.pop_back();
  }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;
  if (!tree.getRoot()) {
    return result;
  }

  std::vector<char> current;
  collectPermutations(tree.getRoot(), current, result);
  return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  if (num < 1 || static_cast<size_t>(num) > tree.getTotalPermutations()) {
    return {};
  }

  auto all_perms = getAllPerms(tree);
  return all_perms[num - 1];
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  if (num < 1 || !tree.getRoot() || static_cast<size_t>(num) > tree.getTotalPermutations()) {
    return {};
  }

  std::vector<char> result;
  auto current = tree.getRoot();
  int remaining_num = num - 1;

  while (!current->children.empty()) {
    size_t n = current->children.size();
    size_t branch_size = 1;
    for (size_t i = 1; i < n; ++i) {
      branch_size *= i;
    }

    size_t selected = remaining_num / branch_size;
    if (selected >= n) {
      return {};
    }
    
    result.push_back(current->children[selected]->value);
    remaining_num %= branch_size;
    current = current->children[selected];
  }

  return result;
}

size_t PMTree::getTotalPermutations() const {
  return total_permutations;
}

std::shared_ptr<PMTree::Node> PMTree::getRoot() const {
  return root;
}

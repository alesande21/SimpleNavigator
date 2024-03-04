//
// Created by Alesander Britni on 10/31/23.
//

#ifndef SIMPLENAVIGATOR_DATASTRUCT_H
#define SIMPLENAVIGATOR_DATASTRUCT_H

#include <vector>

namespace s21 {
struct VerticesData {
  int vertices_{};
  std::vector<std::vector<int>> matrix_adjacency_;

  void Clear() {
    vertices_ = 0;
    matrix_adjacency_.clear();
  }

  float GetData(size_t from, size_t to) { return matrix_adjacency_[from][to]; }
};
}  // namespace s21

#endif  // SIMPLENAVIGATOR_DATASTRUCT_H

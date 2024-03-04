//
// Created by Alesander Britni on 10/30/23.
//

#ifndef SIMPLENAVIGATOR_CONTROLLER_H
#define SIMPLENAVIGATOR_CONTROLLER_H

#include <iostream>
#include <queue>

#include "../../Models/include/Graph/Graph.h"
#include "../../Models/include/Graph/GraphAlgorithms.h"

namespace s21 {
class Controller {
 public:
  Controller() = default;

  void ReadFile(const std::string& filename);
  void ExportFile(const std::string& filename);
  std::vector<size_t> DFS(int start_vertex);
  std::vector<size_t> BFS(int start_vertex);
  int ShortestPath(int vertex1, int vertex2);
  std::vector<std::vector<int>> ShortestPath();
  std::vector<std::vector<int>> SpanningTree();
  TsmResult TSP();

 private:
  Graph graph_;
  GraphAlgorithms algo_;
};
}  // namespace s21

#endif  // SIMPLENAVIGATOR_CONTROLLER_H

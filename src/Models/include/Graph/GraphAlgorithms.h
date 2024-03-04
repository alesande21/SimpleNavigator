//
// Created by Alesander Britni on 10/30/23.
//

#ifndef SIMPLENAVIGATOR_GRAPHALGORITHMS_H
#define SIMPLENAVIGATOR_GRAPHALGORITHMS_H

#include <cmath>
#include <set>
#include <vector>

#include "../Conteiners/s21_queue.h"
#include "../Conteiners/s21_stack.h"
#include "../DataStruct/CostData.h"
#include "Graph.h"
#include "Tsm.h"

namespace s21 {
class GraphAlgorithms {
 public:
  std::vector<size_t> DepthFirstSearch(Graph &graph, int start_vertex);
  std::vector<size_t> BreadthFirstSearch(Graph &graph, int start_vertex);
  int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(
      Graph &graph);
  std::vector<std::vector<int>> GetLeastSpanningTree(Graph &graph);
  TsmResult SolveTravelingSalesmanProblem(Graph &graph);

 private:
  std::vector<size_t> visited_;
  Tsm tsm_;
};
}  // namespace s21

#endif  // SIMPLENAVIGATOR_GRAPHALGORITHMS_H

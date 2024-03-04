//
// Created by Alesander Britni on 10/30/23.
//

#ifndef SIMPLENAVIGATOR_VIEW_H
#define SIMPLENAVIGATOR_VIEW_H

#include <filesystem>
#include <queue>
#include <stack>

#include "../../Controllers/include/Controller.h"
#include "Selection.h"

namespace s21 {
class View {
 public:
  View(Controller &controller);

  void RunView();

 private:
  Controller &controller_;
  std::queue<size_t> visited_;

  void LoadMenu();
  void LoadFile();
  void ExportToFile();
  void BFS();
  void DFS();
  void ShortestPathDijkstra();
  void ShortestPathFloydWarshall();
  void SpanningTree();
  void TSP();
};
}  // namespace s21

#endif  // SIMPLENAVIGATOR_VIEW_H

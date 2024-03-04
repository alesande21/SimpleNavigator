//
// Created by Alesander Britni on 10/30/23.
//

#include "../include/Controller.h"

namespace s21 {

void Controller::ReadFile(const std::string &filename) {
  graph_.LoadGraphFromFile(filename);
}

void Controller::ExportFile(const std::string &filename) {
  graph_.ExportGraphToDot(filename);
}

std::vector<size_t> Controller::BFS(int start_vertex) {
  return algo_.BreadthFirstSearch(graph_, start_vertex);
}

std::vector<size_t> Controller::DFS(int start_vertex) {
  return algo_.DepthFirstSearch(graph_, start_vertex);
}

int Controller::ShortestPath(int start, int finish) {
  return algo_.GetShortestPathBetweenVertices(graph_, start, finish);
}

std::vector<std::vector<int>> Controller::ShortestPath() {
  return algo_.GetShortestPathsBetweenAllVertices(graph_);
}

std::vector<std::vector<int>> Controller::SpanningTree() {
  return algo_.GetLeastSpanningTree(graph_);
}

TsmResult Controller::TSP() {
  return algo_.SolveTravelingSalesmanProblem(graph_);
}

}  // namespace s21
//
// Created by Alesander Britni on 10/30/23.
//
#include "../../include/Graph/GraphAlgorithms.h"

namespace s21 {
std::vector<size_t> GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                      int start_vertex) {
  visited_.clear();
  if (start_vertex < 0 || start_vertex >= graph.SendData().vertices_) {
    std::cerr << "         Error! The starting vertex must be between: " << 1
              << " and " << graph.SendData().vertices_ << std::endl;
    return visited_;
  }
  s21::Stack<size_t> to;

  std::vector<bool> visited(graph.SendData().vertices_, false);
  auto matrix = graph.SendData().matrix_adjacency_;

  to.Push(start_vertex);
  size_t row{};

  while (!to.Empty()) {
    row = to.Top();
    if (!visited[row]) visited_.push_back(row + 1);
    visited[row] = true;
    to.Pop();

    for (int col = matrix.size() - 1; col >= 0; --col) {
      if (matrix[row][col] != 0 && !visited[col]) {
        to.Push(col);
      }
    }
    ++row;
  }

  return visited_;
}

std::vector<size_t> GraphAlgorithms::BreadthFirstSearch(s21::Graph &graph,
                                                        int start_vertex) {
  visited_.clear();
  if (start_vertex < 0 || start_vertex >= graph.SendData().vertices_) {
    std::cerr << "         Error! The starting vertex must be between: " << 1
              << " and " << graph.SendData().vertices_ << std::endl;
    return visited_;
  }
  s21::Queue<size_t> to;
  std::vector<bool> visited(graph.SendData().vertices_, false);
  auto matrix = graph.SendData().matrix_adjacency_;

  to.Push(start_vertex);
  visited[start_vertex] = true;
  size_t row{};

  while (!to.Empty()) {
    visited_.push_back(to.Front() + 1);
    row = to.Front();
    to.Pop();

    for (size_t col = 0; col < matrix.size(); ++col) {
      if (matrix[row][col] != 0 && !visited[col]) {
        visited[col] = true;
        to.Push(col);
      }
    }
    ++row;
  }

  return visited_;
}

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                    int vertex2) {
  if (vertex1 < 0 || vertex2 < 0 || vertex1 >= graph.SendData().vertices_ ||
      vertex2 >= graph.SendData().vertices_) {
    std::cerr << "            Ошибка! Начальная/конечная позиция выходят за "
                 "пределы размера графа: "
              << 1 << " и " << graph.SendData().vertices_ << std::endl;
    return std::numeric_limits<int>::max();
  }

  std::vector<CostData> vertices(graph.SendData().vertices_,
                                 {false, std::numeric_limits<int>::max(), -1});
  auto matrix = graph.SendData().matrix_adjacency_;

  s21::Queue<size_t> to;
  to.Push(vertex1);
  vertices[vertex1].cost_ = 0;

  size_t row{};

  while (!to.Empty()) {
    vertices[to.Front()].visited_ = true;
    row = to.Front();
    to.Pop();

    for (size_t col = 0; col < matrix.size(); ++col) {
      if (matrix[row][col] != 0) {  // && !vertices[col].visited_
        if (vertices[col].cost_ == std::numeric_limits<int>::max() ||
            vertices[col].cost_ > matrix[row][col] + vertices[row].cost_) {
          vertices[col].cost_ = matrix[row][col] + vertices[row].cost_;
          vertices[col].path_ = row;
          to.Push(col);
        }
      }
    }
    ++row;
  }
  return vertices[vertex2].cost_;
}

std::vector<std::vector<int>>
GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
  std::vector<std::vector<int>> cost_matrix(
      graph.SendData().vertices_,
      std::vector<int>(graph.SendData().vertices_,
                       std::numeric_limits<int>::max()));

  auto matrix = graph.SendData().matrix_adjacency_;
  for (size_t i = 0; i < graph.SendData().matrix_adjacency_.size(); ++i) {
    for (size_t j = 0; j < graph.SendData().matrix_adjacency_.size(); ++j) {
      if (i == j) {
        cost_matrix[i][j] = 0;
      }
      if (matrix[i][j] != 0) {
        cost_matrix[i][j] = matrix[i][j];
      }
    }
  }

  for (size_t k = 0; k < matrix.size(); ++k) {
    std::vector<std::vector<int>> path_matrix(
        graph.SendData().vertices_,
        std::vector<int>(graph.SendData().vertices_,
                         std::numeric_limits<int>::max()));
    for (size_t row = 0; row < matrix.size(); ++row) {
      for (size_t col = 0; col < matrix.size(); ++col) {
        if (cost_matrix[row][k] == std::numeric_limits<int>::max() ||
            cost_matrix[k][col] == std::numeric_limits<int>::max())
          path_matrix[row][col] = cost_matrix[row][col];
        else
          path_matrix[row][col] = std::min(
              cost_matrix[row][col], cost_matrix[row][k] + cost_matrix[k][col]);
      }
    }
    cost_matrix = path_matrix;
  }

  return cost_matrix;
}

std::vector<std::vector<int>> GraphAlgorithms::GetLeastSpanningTree(
    Graph &graph) {
  std::vector<std::vector<int>> cost_matrix(
      graph.SendData().vertices_,
      std::vector<int>(graph.SendData().vertices_, 0));
  std::vector<CostData> vertices(graph.SendData().vertices_,
                                 {false, std::numeric_limits<int>::max(), -1});
  auto matrix = graph.SendData().matrix_adjacency_;

  std::map<int, size_t> to;
  std::multiset<int> a;
  to.insert({0, 0});
  vertices[0].cost_ = 0;
  size_t row{};
  while (!to.empty()) {
    if (vertices[to.begin()->second].visited_) {
      to.erase(to.begin());
      continue;
    }

    row = to.begin()->second;
    vertices[row].visited_ = true;
    to.erase(to.begin());

    for (size_t col = 0; col < matrix.size(); ++col) {
      if (matrix[row][col] != 0 && !vertices[col].visited_) {
        if (vertices[col].cost_ == std::numeric_limits<int>::max() ||
            vertices[col].cost_ > matrix[row][col]) {
          if (vertices[col].path_ != -1) {
            cost_matrix[vertices[col].path_][col] = 0;
            cost_matrix[col][vertices[col].path_] = 0;
          }
          cost_matrix[row][col] = matrix[row][col];
          if (matrix[row][col] == matrix[col][row]) {
            cost_matrix[col][row] = matrix[row][col];
          }
          vertices[col].cost_ = matrix[row][col];
          vertices[col].path_ = row;
          to.insert({matrix[row][col], col});
        }
      }
    }
  }

  return cost_matrix;
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
  tsm_.SetSettings(50, 1, 1);
  return tsm_.RunAlgorithm(graph);
}

}  // namespace s21
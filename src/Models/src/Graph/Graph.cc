//
// Created by Alesander Britni on 10/30/23.
//
#include "../../include/Graph/Graph.h"

namespace s21 {

Graph::data_type Graph::LoadGraphFromFile(std::string filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return data_;
  }
  ClearData();
  std::string line;
  std::getline(file, line);
  if (!SetRowsCols(line)) return {};

  while (std::getline(file, line)) {
    ReadLine(line);
  }

  is_graph_directed_ = IsGraphDirected();

  return data_;
}

bool Graph::SetRowsCols(const std::string& line) {
  std::istringstream iss(line);
  iss >> data_.vertices_;
  if (data_.vertices_ > 0 && data_.vertices_ <= 50) return true;
  return false;
}

void Graph::ReadLine(const std::string& line) {
  std::istringstream iss(line);
  std::vector<int> vec;
  int val{};
  for (int i = 0; i < data_.vertices_; ++i) {
    if (!(iss >> val)) return;
    vec.push_back(val);
  }
  data_.matrix_adjacency_.push_back(vec);
}

void Graph::ExportGraphToDot(std::string filename) {
  if (data_.matrix_adjacency_.empty()) return;
  std::string file_path{filename + ".dot"};
  std::ofstream out;
  out.open(file_path);
  if (!out.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    out.close();
    return;
  }

  out << "graph "
      << "graphname"
      << "{" << std::endl;

  for (size_t r = 0; r < data_.matrix_adjacency_.size(); ++r) {
    out << r + 1 << ";"
        << "\n";
  }

  int r = 1;

  for (const auto& row : data_.matrix_adjacency_) {
    int c = 1;
    for (const auto& param : row) {
      if (((r < c) && !is_graph_directed_) && param)
        out << r << " -- " << c << " [label=" << param << "];" << std::endl;
      if (is_graph_directed_ && param)
        out << r << " -> " << c << " [label=" << param << "];" << std::endl;
      c += 1;
    }
    r += 1;
  }

  out << "}" << std::endl;
}

bool Graph::IsGraphDirected() {
  if (data_.matrix_adjacency_.empty()) return false;
  for (size_t i = 0; i < data_.matrix_adjacency_.size(); ++i) {
    for (size_t j = 0; j < data_.matrix_adjacency_.size(); ++j) {
      if (data_.matrix_adjacency_[i][j] != 0 &&
          data_.matrix_adjacency_[j][i] == 0)
        return true;
    }
  }
  return false;
}

Graph::data_type& Graph::SendData() { return data_; }

void Graph::Print() {
  std::cout << "___print___" << std::endl;
  std::cout << "param___" << data_.vertices_ << std::endl;
  std::cout << "graph___" << is_graph_directed_ << std::endl;
  std::cout << "size___" << data_.matrix_adjacency_.size() << std::endl;
  for (const auto& row : data_.matrix_adjacency_) {
    for (const auto& col : row) {
      std::cout << col << " ";
    }
    std::cout << std::endl;
  }
}

}  // namespace s21
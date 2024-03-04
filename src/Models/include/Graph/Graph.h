//
// Created by Alesander Britni on 10/30/23.
//

#ifndef SIMPLENAVIGATOR_GRAPH_H
#define SIMPLENAVIGATOR_GRAPH_H

#include <cstring>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stack>
#include <string>

#include "../Conteiners/s21_stack.h"
#include "../DataStruct/VerticesData.h"

namespace s21 {
class Graph {
 public:
  using data_type = VerticesData;

  Graph() = default;
  data_type LoadGraphFromFile(std::string filename);
  void ExportGraphToDot(std::string filename);
  data_type& SendData();

 private:
  VerticesData data_;
  bool is_graph_directed_ = false;
  bool IsGraphDirected();
  inline void ClearData() { data_.Clear(); }
  void ReadLine(const std::string& line);
  bool SetRowsCols(const std::string& line);
  void Print();
};
}  // namespace s21

#endif  // SIMPLENAVIGATOR_GRAPH_H

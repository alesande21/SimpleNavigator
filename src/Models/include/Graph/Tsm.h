//
// Created by Alesander Britni on 11/16/23.
//

#ifndef SIMPLENAVIGATOR_TSM_H
#define SIMPLENAVIGATOR_TSM_H

#include <map>
#include <random>

#include "../DataStruct/TsmResult.h"
#include "Graph.h"

namespace s21 {
class Tsm {
 public:
  Tsm() = default;
  void SetSettings(int round, double alfa, double beta);
  TsmResult RunAlgorithm(Graph &graph);

 private:
  int count_{};
  int round_{};
  double alfa_{};
  double beta_{};
  std::vector<std::vector<float>> pheromones_;

  float GetRandom();
};
}  // namespace s21

#endif  // SIMPLENAVIGATOR_TSM_H

//
// Created by Alesander Britni on 11/16/23.
//

#include "../../include/Graph/Tsm.h"

namespace s21 {

void Tsm::SetSettings(int round, double alfa, double beta) {
  round_ = round;
  alfa_ = alfa;
  beta_ = beta;
}

TsmResult Tsm::RunAlgorithm(Graph &graph) {
  int count = 0;
  TsmResult best_way;
  best_way.distance = std::numeric_limits<int>::max();

  std::vector<std::vector<float>> pheromones_(
      graph.SendData().vertices_,
      std::vector<float>(graph.SendData().vertices_));
  for (size_t i = 0; i < pheromones_.size(); i++) {
    for (size_t j = 0; j < pheromones_[i].size(); j++) {
      pheromones_[i][j] = (i != j) ? 0.200f : 0;
    }
  }
  auto matrix = graph.SendData().matrix_adjacency_;

  while (round_) {
    std::vector<TsmResult> ants_ways;
    for (size_t ant = 0; ant < matrix.size(); ++ant) {
      std::multimap<float, size_t> to;
      std::vector<bool> visited(graph.SendData().vertices_, false);

      TsmResult ant_way;
      to.insert({1, ant});
      size_t row = ant;
      while (!to.empty()) {
        to.clear();
        visited[row] = true;
        ant_way.vertices.push_back(row);
        float sum_p = 0;
        for (size_t col = 0; col < matrix.size(); ++col) {
          if (matrix[row][col] != 0 && !visited[col]) {
            float p = 100 * powf(1 / matrix[row][col], beta_) *
                      powf(pheromones_[row][col], alfa_);
            sum_p += p;
          }
        }
        for (size_t col = 0; col < matrix.size(); ++col) {
          if (matrix[row][col] != 0 && !visited[col]) {
            float p = 100 * powf(1 / matrix[row][col], beta_) *
                      powf(pheromones_[row][col], alfa_);
            to.insert({p / sum_p, col});
          }
        }

        if (!to.empty()) {
          float random = GetRandom();
          auto new_way = to.upper_bound(random);
          new_way = new_way == to.end() ? --new_way : new_way;
          ant_way.distance += matrix[row][new_way->second];
          row = new_way->second;
        }
      }
      if (matrix[ant_way.vertices.back()][ant_way.vertices.front()] != 0) {
        ant_way.distance +=
            matrix[ant_way.vertices.back()][ant_way.vertices.front()];
        ant_way.vertices.push_back(ant_way.vertices.front());
        if (!ants_ways.empty() &&
            (ants_ways.back().distance < ant_way.distance)) {
          std::swap(ants_ways.back(), ant_way);
        }
        ants_ways.push_back(ant_way);
      }
    }

    if (best_way.distance > ants_ways.back().distance) {
      best_way.distance = ants_ways.back().distance;
      best_way.vertices = ants_ways.back().vertices;
      round_ = 50;
    }

    for (size_t i = 0; i < ants_ways.size(); ++i) {
      for (size_t j = 1; j < ants_ways[i].vertices.size(); ++j) {
        pheromones_[j - 1][ants_ways[i].vertices[j]] =
            1 * pheromones_[j - 1][ants_ways[i].vertices[j]] +
            4 / ants_ways[i].distance;
      }
    }

    --round_;
    ++count;
  }

  return best_way;
}

float Tsm::GetRandom() {
  std::random_device r;
  std::default_random_engine e1(r());
  std::uniform_real_distribution<float> uniform_dist(0, 1);
  return uniform_dist(e1);
}
}  // namespace s21

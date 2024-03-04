//
// Created by Alesander Britni on 11/13/23.
//

#ifndef SIMPLENAVIGATOR_VERTEXDATA_H
#define SIMPLENAVIGATOR_VERTEXDATA_H

namespace s21 {
struct CostData {
  bool visited_ = false;
  int cost_{};
  int path_{};
};
}  // namespace s21

#endif  // SIMPLENAVIGATOR_VERTEXDATA_H

//
// Created by Slava on 07.11.2023.
//

#include <cassert>

#include "../Models/include/Graph/GraphAlgorithms.h"

void TestDFS_1() {
  s21::Graph graph;
  graph.LoadGraphFromFile("./ResourceFiles/ma_1_(5_u_uw).txt");
  s21::GraphAlgorithms algo;
  auto vec = algo.DepthFirstSearch(graph, 0);

  std::vector<size_t> answer{1, 2, 3, 5, 4};
  assert(vec == answer);
  std::cout << "\033[32m"
            << "TestDFS_1 passed!"
            << "\033[0m" << std::endl;
}

void TestDFS_2() {
  s21::Graph graph;
  graph.LoadGraphFromFile("./ResourceFiles/ma_2_(5_d_uw).txt");
  s21::GraphAlgorithms algo;
  auto vec = algo.DepthFirstSearch(graph, 3);

  std::vector<size_t> answer{4, 2, 1, 3, 5};
  assert(vec == answer);
  std::cout << "\033[32m"
            << "TestDFS_2 passed!"
            << "\033[0m" << std::endl;
}

void TestDFS_3() {
  s21::Graph graph;
  graph.LoadGraphFromFile("./ResourceFiles/ma_3_(15_u_uw).txt");
  s21::GraphAlgorithms algo;
  auto vec = algo.DepthFirstSearch(graph, 0);

  std::vector<size_t> answer{1, 2, 4, 7, 3, 14, 6, 9, 8, 5, 12, 10, 11, 15, 13};
  assert(vec == answer);
  std::cout << "\033[32m"
            << "TestDFS_3 passed!"
            << "\033[0m" << std::endl;
}

void TestDFS_4() {
  s21::Graph graph;
  graph.LoadGraphFromFile("./ResourceFiles/ma_3_(15_u_uw).txt");
  s21::GraphAlgorithms algo;
  auto vec = algo.DepthFirstSearch(graph, 2);

  std::vector<size_t> answer{3, 1, 2, 4, 7, 6, 9, 8, 5, 12, 10, 11, 15, 14, 13};
  assert(vec == answer);
  std::cout << "\033[32m"
            << "TestDFS_4 passed!"
            << "\033[0m" << std::endl;
}

void TestBFS_1() {
  s21::Graph graph;
  graph.LoadGraphFromFile("./ResourceFiles/ma_1_(5_u_uw).txt");
  s21::GraphAlgorithms algo;
  auto vec = algo.BreadthFirstSearch(graph, 0);

  //    std::vector<size_t> answer{0,1,2,3,4};
  std::vector<size_t> answer{1, 2, 3, 4, 5};
  assert(vec == answer);
  std::cout << "\033[32m"
            << "TestBFS_1 passed!"
            << "\033[0m" << std::endl;
}

void TestBFS_2() {
  s21::Graph graph;
  graph.LoadGraphFromFile("./ResourceFiles/ma_2_(5_d_uw).txt");
  s21::GraphAlgorithms algo;
  auto vec = algo.BreadthFirstSearch(graph, 3);

  //    std::vector<size_t> answer{3,1,4,0,2};
  std::vector<size_t> answer{4, 2, 5, 1, 3};
  assert(vec == answer);
  std::cout << "\033[32m"
            << "TestBFS_2 passed!"
            << "\033[0m" << std::endl;
}

void TestBFS_3() {
  s21::Graph graph;
  graph.LoadGraphFromFile("./ResourceFiles/ma_13_(17_d_uw).txt");
  s21::GraphAlgorithms algo;
  auto vec = algo.BreadthFirstSearch(graph, 2);

  //    std::vector<size_t> answer{3,1,4,0,2};
  std::vector<size_t> answer{3,  2,  4,  6,  7,  9,  10, 12,
                             11, 13, 14, 15, 16, 18, 17, 8};
  assert(vec == answer);
  std::cout << "\033[32m"
            << "TestBFS_3 passed!"
            << "\033[0m" << std::endl;
}

void TestShortWayBetweenTwoVertex_4() {
  s21::Graph graph;
  graph.LoadGraphFromFile("./ResourceFiles/ma_4_(8_u_w).txt");
  s21::GraphAlgorithms algo;
  auto cost = algo.GetShortestPathBetweenVertices(graph, 0, 7);

  assert(cost == 9);
  std::cout << "\033[32m"
            << "TestShortWayBetweenTwoVertex_4 passed!"
            << "\033[0m" << std::endl;
}

void TestShortWayBetweenTwoVertex_5() {
  s21::Graph graph;
  graph.LoadGraphFromFile("./ResourceFiles/ma_5_(8_u_w).txt");
  s21::GraphAlgorithms algo;
  auto cost = algo.GetShortestPathBetweenVertices(graph, 0, 7);

  assert(cost == 8);
  std::cout << "\033[32m"
            << "TestShortWayBetweenTwoVertex_5 passed!"
            << "\033[0m" << std::endl;
}

void TestShortWayBetweenTwoVertex_3() {
  s21::Graph graph;
  graph.LoadGraphFromFile("./ResourceFiles/ma_3_(15_u_uw).txt");
  s21::GraphAlgorithms algo;
  auto cost = algo.GetShortestPathBetweenVertices(graph, 0, 4);

  assert(cost == 2);
  std::cout << "\033[32m"
            << "TestShortWayBetweenTwoVertex_3 passed!"
            << "\033[0m" << std::endl;
}

void TestShortWayBetweenTwoVertex_13() {
  s21::Graph graph;
  graph.LoadGraphFromFile("./ResourceFiles/ma_13_(17_d_uw).txt");
  s21::GraphAlgorithms algo;
  auto cost = algo.GetShortestPathBetweenVertices(graph, 4, 13);

  assert(cost == 5);
  std::cout << "\033[32m"
            << "TestShortWayBetweenTwoVertex_13 passed!"
            << "\033[0m" << std::endl;
}

void TestShortWayBetweenTwoVertex_13_2() {
  s21::Graph graph;
  graph.LoadGraphFromFile("./ResourceFiles/ma_13_(17_d_uw).txt");
  s21::GraphAlgorithms algo;
  auto cost = algo.GetShortestPathBetweenVertices(graph, 3, 4);

  assert(cost == std::numeric_limits<int>::max());
  std::cout << "\033[32m"
            << "TestShortWayBetweenTwoVertex_13_2 passed!"
            << "\033[0m" << std::endl;
}

void TestShortWayBetweenAllVertices() {
  s21::Graph graph;
  graph.LoadGraphFromFile("./ResourceFiles/ma_6_(4_d_w_FloydWarshall).txt");
  s21::GraphAlgorithms algo;
  s21::Graph answer;
  answer.LoadGraphFromFile("./ResourceFiles/answer/answerFloydWarshall.txt");
  auto cost = algo.GetShortestPathsBetweenAllVertices(graph);

  assert(cost == answer.SendData().matrix_adjacency_);
  std::cout << "\033[32m"
            << "TestShortWayBetweenAllVertices passed!"
            << "\033[0m" << std::endl;
}

void TestGetLeastSpanningTree_10() {
  s21::Graph graph;
  graph.LoadGraphFromFile("./ResourceFiles/ma_10_(9_u_w_SpanningTree).txt");
  s21::GraphAlgorithms algo;
  s21::Graph answer;
  answer.LoadGraphFromFile("./ResourceFiles/answer/answerSpanningTree_10.txt");
  auto tree = algo.GetLeastSpanningTree(graph);

  assert(tree == answer.SendData().matrix_adjacency_);
  std::cout << "\033[32m"
            << "TestGetLeastSpanningTree_10 passed!"
            << "\033[0m" << std::endl;
}

void TestGetLeastSpanningTree_9() {
  s21::Graph graph;
  graph.LoadGraphFromFile("./ResourceFiles/ma_9_(6_u_w_SpanningTree).txt");
  s21::GraphAlgorithms algo;
  s21::Graph answer;
  answer.LoadGraphFromFile("./ResourceFiles/answer/answerSpanningTree_9.txt");
  auto tree = algo.GetLeastSpanningTree(graph);

  assert(tree == answer.SendData().matrix_adjacency_);
  std::cout << "\033[32m"
            << "TestGetLeastSpanningTree_9 passed!"
            << "\033[0m" << std::endl;
}

void SolveTravelingSalesmanProblem() {
  s21::Graph graph;
  graph.LoadGraphFromFile("./ResourceFiles/ma_12_(18_u_w).txt");
  s21::GraphAlgorithms algo;

  auto tsm = algo.SolveTravelingSalesmanProblem(graph);

  assert(tsm.distance <= 26);
  std::cout << "\033[32m"
            << "SolveTravelingSalesmanProblem passed!"
            << "\033[0m" << std::endl;
}

int main() {
  TestDFS_1();
  TestDFS_2();
  TestDFS_3();
  TestDFS_4();
  TestBFS_1();
  TestBFS_2();
  TestBFS_3();
  TestShortWayBetweenTwoVertex_3();
  TestShortWayBetweenTwoVertex_4();
  TestShortWayBetweenTwoVertex_5();
  TestShortWayBetweenTwoVertex_13();
  TestShortWayBetweenTwoVertex_13_2();
  TestShortWayBetweenAllVertices();
  TestGetLeastSpanningTree_9();
  TestGetLeastSpanningTree_10();
  SolveTravelingSalesmanProblem();
  return 0;
}

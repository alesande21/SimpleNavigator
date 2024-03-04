//
// Created by Alesander Britni on 10/30/23.
//
#include "../include/View.h"

#include <iostream>

namespace s21 {

View::View(s21::Controller& controller) : controller_(controller) {}

void View::LoadMenu() {
  std::cout << "\033[97m" << std::endl
            << "*******************************_Главное "
               "меню_*******************************"
            << std::endl;
  std::cout << "1. Загрузка графа из файла в формате матрицы смежности"
            << std::endl;
  std::cout << "2. Выгрузить граф в файл в формате dot" << std::endl;
  std::cout
      << "3. Нерекурентный поиск в глубину в графе от заданной вершины (DFS)"
      << std::endl;
  std::cout << "4. Поиск в ширину в графе от заданной вершины (BFS)"
            << std::endl;
  std::cout << "5. Поиск кратчайшего пути между двумя вершинами в графе "
               "(алгоритм Дейкстры)"
            << std::endl;
  std::cout << "6. Поиск кратчайших путей между всеми парами вершин в графе "
               "(алгоритм Флойда-Уоршелла)"
            << std::endl;
  std::cout << "7. Поиск минимального остовного дерева (алгоритм Прима)"
            << std::endl;
  std::cout << "8. Задача коммивояжера" << std::endl;
  std::cout << "0. Выйти из главного меню"
            << "\033[0m" << std::endl;
}

void View::RunView() {
  bool stop_view = false;
  int selection{};
  //        std::cout << Selection::LOAD_FILE << std::endl;
  while (!stop_view) {
    LoadMenu();
    std::cout << std::endl
              << "\033[93m"
              << "   Введите пункт из главного меню: "
              << "\033[0m";
    if (!(std::cin >> selection)) {
      std::cout
          << "\033[91m"
          << "      Некорректный ввод данных! Выберите из списка главного меню."
          << "\033[0m" << std::endl;
    }
    if (Selection::LOAD_FILE == (Selection)selection) {
      std::cout << "      Введите путь к файлу: " << std::endl;
      LoadFile();
    } else if (Selection::EXPORT_TO_DOT == (Selection)selection) {
      std::cout << "      Введите название файла для сохранения: " << std::endl;
      ExportToFile();
    } else if (Selection::BFS == (Selection)selection) {
      BFS();
    } else if (Selection::DFS == (Selection)selection) {
      DFS();
    } else if (Selection::SP_DIJKSTRA == (Selection)selection) {
      std::cout << "      Введите начальную и конечную позицию: " << std::endl;
      ShortestPathDijkstra();
    } else if (Selection::SP_FLOYD_WARSHALL == (Selection)selection) {
      ShortestPathFloydWarshall();
    } else if (Selection::SPANNING_TREE == (Selection)selection) {
      SpanningTree();
    } else if (Selection::TSP == (Selection)selection) {
      TSP();
    } else if (Selection::EXIT == (Selection)selection) {
      std::cout << "На этом всё!" << std::endl;
      stop_view = true;
    }
  }
}

void View::ExportToFile() {
#if 1
  std::string filename;
  if (!(std::cin >> filename)) {
    std::cout
        << "         Некорректный ввод названия файла! Попробуйте ещё раз."
        << std::endl;
    LoadFile();
  }
#elif 0
  std::string filename = "ResourceFiles/toDot";
#endif
  controller_.ExportFile(filename);
}

void View::LoadFile() {
#if 1
  std::string filename;
  if (!(std::cin >> filename)) {
    std::cout << "Некорректный ввод названия файла! Попробуйте ещё раз."
              << std::endl;
    LoadFile();
  }
#elif 0
  std::string filename = "ResourceFiles/ma_12_(18_u_w).txt";
#endif

  controller_.ReadFile(filename);
}

void View::BFS() {
  std::cout << "      Введите начальную позицую: ";
  size_t start_vertex{};
  if (!(std::cin >> start_vertex)) {
    std::cout
        << "         Некорректный ввод начальной позиции! Попробуйте ещё раз."
        << std::endl;
    BFS();
    return;
  }
  auto visited = controller_.BFS(start_vertex - 1);
  std::cout << "            Обход графа: ";
  for (const auto& elem : visited) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

void View::DFS() {
  std::cout << "      Введите начальную позицую: ";
  size_t start_vertex{};
  if (!(std::cin >> start_vertex)) {
    std::cout
        << "         Некорректный ввод начальной позиции! Попробуйте ещё раз."
        << std::endl;
    DFS();
    return;
  }
  auto visited = controller_.DFS(start_vertex - 1);
  std::cout << "            Обход графа: ";
  for (const auto& elem : visited) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

void View::ShortestPathDijkstra() {
  size_t vertex1{};
  size_t vertex2{};
  std::cout << "         Стартовая позиция: ";
  if (!(std::cin >> vertex1)) {
    std::cout << " - Некорректный ввод начальной позиции! Попробуйте ещё раз."
              << std::endl;
    ShortestPathDijkstra();
    return;
  }
  std::cout << "         Конечная позиция: ";
  if (!(std::cin >> vertex2)) {
    std::cout << " - Некорректный ввод конечной позиции! Попробуйте ещё раз."
              << std::endl;
    ShortestPathDijkstra();
    return;
  }
  auto cost = controller_.ShortestPath(vertex1 - 1, vertex2 - 1);
  std::cout << "            Короткий путь от " << vertex1 << " до " << vertex2
            << " равен: ";
  if (cost == std::numeric_limits<int>::max())
    std::cout << "inf"
              << " - пути нет!" << std::endl;
  else
    std::cout << cost << std::endl;
}

void View::ShortestPathFloydWarshall() {
  std::cout << "   Матрица кротчайших путей: " << std::endl;
  auto cost_matrix = controller_.ShortestPath();
  for (const auto& row : cost_matrix) {
    std::cout << "      ";
    for (const auto& col : row) {
      //                std::cout << "      " << col << " ";
      if (col == std::numeric_limits<int>::max())
        std::cout << "\u221E"
                  << " ";
      else
        std::cout << col << " ";
    }
    std::cout << std::endl;
  }
}

void View::SpanningTree() {
  std::cout << "      Матрица смежности для минимального остовного дерева: "
            << std::endl;
  auto cost_matrix = controller_.SpanningTree();

  for (const auto& row : cost_matrix) {
    std::cout << "        ";
    for (const auto& col : row) {
      std::cout << col << " ";
    }
    std::cout << std::endl;
  }
}

void View::TSP() {
  std::cout << "      Самый выгодный маршрут: " << std::endl;
  auto tsm_struct = controller_.TSP();
  std::cout << "         Дистанция: " << tsm_struct.distance << " Вершины: ";
  for (const auto& elem : tsm_struct.vertices) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

}  // namespace s21
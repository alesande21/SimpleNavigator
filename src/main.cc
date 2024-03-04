//
// Created by Alesander Britni on 10/30/23.
//

#include "./Views/include/View.h"
#if WIN
#include <windows.h>
#endif

int main() {
#if WIN
    SetConsoleOutputCP(CP_UTF8);
#endif
//    s21::Splice splicer;
    s21::Controller controller;
    s21::View view (controller);
    view.RunView();
    return 0;
}
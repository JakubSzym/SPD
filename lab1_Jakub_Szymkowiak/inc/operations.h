/*
* Sterowanie procesami ciągłymi
* Laboratorium nr 1
* Autor: Jakub Szymkowiak, 252868
* Plik nagłówkowy zawierający klasę Operations
*/

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <string>
#include <vector>
#include <algorithm>

#include "task.h"

class Operations
{
  public:

  static std::vector<Task> readAllData(std::string filename);

  static int duration(std::vector<Task> tasks);

  static void arrange(std::vector<Task> &tasks, int depth);
};

#endif // #ifndef OPERATIONS_H
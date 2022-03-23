/*
* Sterowanie procesami ciągłymi
* Laboratorium nr 1
* Autor: Jakub Szymkowiak, 252868
* Plik nagłówkowy zawierający strukturę Task
*/

#ifndef TASK_H
#define TASK_H

#include <fstream>

struct Task
{
  int delivery_;
  int working_;
  int stopping_;
};

std::fstream &operator >>(std::fstream &file, Task &task);

#endif // #ifndef TASK_H
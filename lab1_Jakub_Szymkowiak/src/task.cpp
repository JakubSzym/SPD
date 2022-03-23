/*
* Sterowanie procesami ciągłymi
* Laboratorium nr 1
* Autor: Jakub Szymkowiak, 252868
* Plik źródłowy zawierający funkcję odczytującą strukturę Task z pliku
*/

#include "task.h"

std::fstream &operator >>(std::fstream &file, Task &task)
{
  file >> task.delivery_ >> task.working_ >> task.stopping_;
  return file;
}
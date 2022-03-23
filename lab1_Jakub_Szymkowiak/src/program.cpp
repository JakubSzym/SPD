/*
* Sterowanie procesami ciągłymi
* Laboratorium nr 1
* Autor: Jakub Szymkowiak, 252868
* Program główny
*/

#include <iostream>

#include "operations.h"

#define DEFAULT_DEPTH 15

using namespace std;

int main()
{
  vector<Task> tasks;
  int sum = 0;

  for (int set = 1; set <= 4; set++)
  {
    string path = "data/" + to_string(set);
    tasks = Operations::readAllData(path);
    Operations::arrange(tasks, DEFAULT_DEPTH);
    int processTime = Operations::duration(tasks);

    cout << "Obliczona dlugosc procesu nr " << set << ": " << processTime << endl;
    sum += processTime;
  }

  cout << "Dlugosc wszystkich procesow: " << sum << endl;
}
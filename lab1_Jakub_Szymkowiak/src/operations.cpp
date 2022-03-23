/*
* Sterowanie procesami ciągłymi
* Laboratorium nr 1
* Autor: Jakub Szymkowiak, 252868
* Kod źródłowy metod klasy Operations
*/
#include <iostream>
#include "operations.h"

using namespace std;

vector<Task> Operations::readAllData(string filename)
{
  vector<Task> result;
  int amountOfData;
  fstream file;
  file.open(filename, ios::in);

  file >> amountOfData;

  for (int i = 0; i < amountOfData; i++)
  {
    Task task;
    file >> task;
    result.push_back(task);
  }

  file.close();

  return result;
}

int Operations::duration(vector<Task> tasks)
{
  int help     = 0;
  int duration = 0;

  for (auto &task : tasks)
  {
    help     = max(help, task.delivery_) + task.working_;
    duration = max(duration, help + task.stopping_);
  }
  return duration;
}

void Operations::arrange(vector<Task> &tasks, int depth)
{
  int currentLength = duration(tasks);
  int optimizedLength;

  for (int i = 0; i < depth; i++)
  {
    for (unsigned int j = 0; j < tasks.size(); j++)
    {
      for (unsigned int k = 0; k < tasks.size(); k++)
      {
        swap(tasks[j], tasks[k]);
        optimizedLength = duration(tasks);

        if (optimizedLength < currentLength)
        {
          currentLength = optimizedLength;
        }
        else
        {
          swap(tasks[j], tasks[k]);
        }
      }
    }
  }
}

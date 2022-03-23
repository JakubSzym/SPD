#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct Task
{
  int process;
  int weight;
  int deadline;
  int id;
};

fstream &operator>>(fstream &file, Task &task)
{
  file >> task.process >> task.weight >> task.deadline;
  return file;
}

vector<Task> readData(string filename)
{
  int amount;
  int index = 0;
  vector<Task> result;
  fstream file;

  file.open(filename, ios::in);

  file >> amount;

  for (int i = 0; i < amount; i++)
  {
    Task task;
    file >> task;
    task.id = index;
    index++;
    result.push_back(task);
  }

  return result;
}

int punishment(Task task, int time)
{
  if (task.deadline < time)
  {
    return (time - task.deadline) * task.weight;
  }
  return 0;
}


int optimize(vector<Task> tasks)
{
  int length;
  int costArraySize = pow(2, tasks.size());
  int *costArray = new int[costArraySize];
  costArray[0] = 0;

  for (int i = 1; i < costArraySize; i++)
  {
    length = 0;
    for (int j = 0; j < tasks.size(); j++)
    {
      if (i & (1 << j))
      {
        length += tasks[j].process;
      }
    }

    int cost = INT32_MAX;
    costArray[i] = INT32_MAX;

    for (int j = 0; j < tasks.size(); j++)
    {
      if (i & (1 << j))
      {
        cost = costArray[i - (1 << j)] + punishment(tasks[j], length);
      }

      if (cost < costArray[i])
      {
        costArray[i] = cost;
      }
    }
  }

  int result = costArray[costArraySize - 1];
  delete[] costArray;
  return result;
}

int main()
{
  for (int set = 1; set <= 11; set++)
  {
    string path = "data/" + to_string(set);
    vector<Task> tasks = readData(path);
    cout << "Wynik: " << optimize(tasks) << endl;
  }
}
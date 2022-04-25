#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Task
{
  vector<int> data;
  int id;
  int weight;

  bool operator<(const Task &other)
  {
    return weight < other.weight;
  }
};

void readData(vector<vector<Task>> &list)
{
  string header;
  int machines;
  int tasks;
  int units;

  fstream file;
  file.open("Data.txt", ios::in);

  for (int x = 0; x < 120; x++)
  {
    file >> header >> tasks >> machines;

    vector<Task> tmpVectorTask;
    for (int i = 0; i < tasks; i++)
    {
      Task tmpTask;
      tmpTask.id = i;
      for (int j = 0; j < machines; j++)
      {
        file >> units;
        tmpTask.data.push_back(units);
      }
      tmpVectorTask.push_back(tmpTask);
    }
    list.push_back(tmpVectorTask);
  }

  file.close();
}

int length(int number, vector<Task> &listOfTasks)
{
  vector<int> values;
  for (auto &task: listOfTasks)
  {
    for (auto &item: task.data)
    {
      values.push_back(item);
    }
  }
  vector<int> tmp;
  for (int m = 0; m <= listOfTasks[0].data.size(); m++)
  {
    tmp.push_back(0);
  }
  for (unsigned int i = 0; i < number; i++)
  {
    for (unsigned int j = 1; j <= listOfTasks[i].data.size(); j++)
    {
      tmp[j] = max(tmp[j], tmp[j-1]) + values[(j-1) * i*listOfTasks[i].data.size()];
    }
  }
  return tmp[listOfTasks[0].data.size()];
}

void weights(vector<Task> &listOfTasks)
{
  for (auto &task: listOfTasks)
  {
    task.weight = 0;
    for (auto &item: task.data)
    {
      task.weight += item;
    }
  }

  sort(listOfTasks.begin(), listOfTasks.end());
}

int runNEH(vector<Task> &listOfTasks)
{
  weights(listOfTasks);
  for (unsigned int i = 0; i < listOfTasks.size(); i++)
  {
    int bestPosition = -1;
    int bestLength = INT32_MAX;

    for (int position = i; position >= 0; position--)
    {
      int tmpLength = length(i+1, listOfTasks);
      if (bestLength >= tmpLength)
      {
        bestLength = tmpLength;
        bestPosition = position;
      }
      if (position != 0)
      {
        swap(listOfTasks[position], listOfTasks[position-1]);
      }
    }

    for (int j = 0; i < bestPosition; j++)
    {
      swap(listOfTasks[j], listOfTasks[j+1]);
    }
  }
  return length(listOfTasks.size(), listOfTasks);
}

int main()
{
  vector<vector<Task>> database;
    
  readData(database);

  int result = runNEH(database[50]);
  cout << result << endl;
  /*for (auto &task: database[50])
  {
    cout << task.id << ". ";
    for (auto &item: task.data)
    {
      cout << item << " ";
    }
    cout << endl;
  }*/
}
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#undef TEST

using namespace std;

struct NEHData
{
  vector<int> values;
  vector<int> ids;
  int machines;
  int tasks;
};

struct NEHResult
{
  vector<int> ids;
  int time;
};

void readData(vector<NEHData> &list, vector<NEHResult> &results)
{
  string header;
  int units;
  int id;

  fstream file;
  file.open("data.txt", ios::in);

  //
  // Wczytanie danych
  //

  for (int x = 0; x < 120; x++)
  {
    NEHData tmpData;
    NEHResult tmpResult;
    file >> header >> tmpData.tasks >> tmpData.machines;
    for (int i = 0; i < tmpData.tasks * tmpData.machines; i++)
    {
      file >> units;
      tmpData.values.push_back(units);
    }
    for (int i = 0; i < tmpData.tasks; i++)
    {
      tmpData.ids.push_back(i);
    }
    list.push_back(tmpData);

    file >> header;
    file >> tmpResult.time;
    for (int i = 0; i < tmpData.tasks; i++)
    {
      file >> id;
      tmpResult.ids.push_back(id);
    }
    results.push_back(tmpResult);
  }

  file.close();
}

int length(int number, NEHData &userdata)
{
  vector<int> help;

  //
  // Wypełnienie zerami wektora pomocniczego
  //

  for (int i = 0; i <= userdata.machines; i++)
  {
    help.push_back(0);
  }
  
  //
  // Obliczenie długości wykonywania zadań
  //

  for (int i = 0; i < number; i++)
  {
    for (int j = 1; j <= userdata.machines; j++)
    {
      help[j] = max(help[j], help[j-1]) + userdata.values[(j-1) + userdata.ids[i] * userdata.machines];
    }
  }

  return help[userdata.machines];
}

void sortByWeight(NEHData &userdata)
{
  vector<int> weights;

  //
  // Obliczenie wag
  //

  for (int i = 0; i < userdata.tasks; i++)
  {
    int tmp = 0;
    for (int j = 0; j < userdata.machines; j++)
    {
      tmp += userdata.values[i * userdata.machines + j];
    }
    weights.push_back(tmp);
  }
  
  //
  // Sortowanie wg wag
  //

  for (int i = 0; i < userdata.tasks - 1; i++)
  {
    for (int j = 0; j < userdata.tasks - 1; j++)
    {
      if (weights[j] < weights[j+1])
      {
        swap(weights[j], weights[j+1]);
        swap(userdata.ids[j], userdata.ids[j+1]);
      }
    } 
  }
}

int runNEH(NEHData &userdata)
{
  sortByWeight(userdata);

  for (int i = 0; i < userdata.tasks; i++)
  {
    int optimalPosition = -1;
    int optimalLength   = INT32_MAX;

    for (int pos = i; pos >= 0; pos--)
    {
      int tmpLength = length(i+1, userdata);
      if (optimalLength >= tmpLength)
      {
        optimalLength = tmpLength;
        optimalPosition = pos;
      }

      if (pos != 0)
      {
        swap(userdata.ids[pos], userdata.ids[pos-1]);
      }
    }

    for (int j = 0; j < optimalPosition; j++)
    {
      swap(userdata.ids[j], userdata.ids[j+1]);
    }
  }
  return length(userdata.tasks, userdata);
}

int main()
{
  vector<NEHData> database;
  vector<NEHResult> results;
  int errors = 0;
  readData(database, results);

  for (unsigned int i = 0; i < database.size(); i++)
  {
    int result = runNEH(database[i]);
    
    #ifdef TEST
    
    cout << "Wynik: " << result;
    cout << " Wzor: " << results[i].time << endl;
    
    #endif
    
    if (result != results[i].time)
    {
      errors++;
    }
  }
  cout << "Liczba niezgodnosci: " << errors << endl;
}
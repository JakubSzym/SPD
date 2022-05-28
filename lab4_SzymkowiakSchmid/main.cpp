#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct SchrageData
{
  vector<int> r;
  vector<int> p;
  vector<int> q;
  vector<int> ids;
  int amount;
};

struct SchrageResult
{
  int schrpmtn;
  int schr;
  vector<int> ids;
};


void readData(vector<SchrageData> &userdata, vector<SchrageResult> &results)
{
  fstream file;
  file.open("data.txt", ios::in);
  string header;
  for (int i = 0; i < 9; i++)
  {
    SchrageData tmp;
    tmp.ids.push_back(i);
    SchrageResult tmpRes;
    file >> header;
    file >> tmp.amount;
    for (int j = 0; j < tmp.amount; j++)
    {
      int r, p, q;
      file >> r >> p >> q;
      tmp.r.push_back(r);
      tmp.p.push_back(p);
      tmp.q.push_back(q);
    }
    file >> header;
    file >> tmpRes.schrpmtn;
    file >> header;
    file >> tmpRes.schr;
    for (int j = 0; j < tmp.amount; j++)
    {
      int id;
      file >> id;
      tmpRes.ids.push_back(id);
    }

    userdata.push_back(tmp);
    results.push_back(tmpRes);
  }
}

int schrage(SchrageData &data, int *X)
{
  int *unavailable = new int[data.amount];
  int *available = new int[data.amount];
  int unavailableAmount = data.amount;
  int availableIndex = 0;
  int doneAmount = 0;
  int timeUnit = 0;
  int length = 0;

  for (int i = 0; i < unavailableAmount; i++)
  {
    unavailable[i] = i;
  }

  for (int i = 0; i < unavailableAmount - 1; i++)
  {
    for (int j = 0; j < unavailableAmount - 1; j++)
    {
      if (data.r[unavailable[j]] < data.r[unavailable[j+1]])
      {
        swap(unavailable[j], unavailable[j + 1]);
      }
    }
  }

  while (doneAmount != data.amount)
  {
    if (unavailableAmount != 0)
    {
      if (data.r[unavailable[unavailableAmount-1]] <= timeUnit)
      {
        available[availableIndex] = unavailable[unavailableAmount-1];
        availableIndex++;
        unavailableAmount--;
        for (int i = availableIndex - 1; i>0; i--)
        {
          if (data.q[available[i]] < data.q[available[i-1]])
          {
            swap(available[i], available[i-1]);
          }
        }
        continue;
      }
    }

    if (availableIndex != 0)
    {
      X[doneAmount] = available[availableIndex-1];
      timeUnit += data.p[X[doneAmount]];
      length = max(length, timeUnit + data.q[X[doneAmount]]);
      availableIndex--;
      doneAmount++;
      continue;
    }

    if (availableIndex == 0 && data.r[unavailable[unavailableAmount-1]] > timeUnit)
    {
      timeUnit = data.r[unavailable[unavailableAmount-1]];
    }
  }
  delete[] unavailable;
  delete[] available;

  return length;
}

int schragePMTN(SchrageData &data)
{
  // TO DO
  return 0;
}

int main()
{
  vector<SchrageData> data;
  vector<SchrageResult> results;
  
  readData(data, results);
  for (auto &set: data)
  {
    int *X = new int[set.amount];
    int length = schrage(set, X);
    cout << length << endl;
    delete[] X;
  }

  cout << "==========================" << endl;

  for (auto& item: results)
  {
    cout << item.schr << endl;
  }
}

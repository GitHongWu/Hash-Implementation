/*main.cpp*/

//
// Hashing program for specialized Illinois license plates,
// which processes an input file of license plates and fines.
// The output is the total fines per license plate, in 
// sorted order.
//
// Original author: Prof. Joe Hummel
// Modified by:     << Hongcheng Wu >>
//
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

#include "ILplates.h"

using namespace std;


//
// hashInput:
//
void hashInput(string basename, ILplates& hashplates)
{
  string infilename = basename + ".txt";
  ifstream infile(infilename);

  if (!infile.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << infilename << "', exiting." << endl;
    cout << endl;
    exit(-1);
  }

  //
  // input the plates and fines:
  //
  cout << "Reading '" << infilename << "'..." << endl;

  string fine;
  string plate;

  getline(infile, fine);

  //
  // for each pair (fine, license plate), hash and store/update fine:
  //
  while (!infile.eof())
  {
    getline(infile, plate);

    //cout << fine << endl;
    //cout << plate << endl;

    // 
    // is plate valid?  Only process valid plates:
    //
    if (hashplates.Hash(plate) >= 0) // yes:
    {
      //cout << "search ";
      //cout << "Valid: " << plate << endl;
      int amount = hashplates.Search(plate);

      if (amount < 0)  // not found:
      {
        //cout << "insert1,";
        hashplates.Insert(plate, stoi(fine));
      }
      else  // we found it, so update total in hash table:
      {
        //cout << "insert2,";
        amount += stoi(fine);
        hashplates.Insert(plate, amount);
      }
    }
    else{ //Hash return -1
      //cout << "Invalid plate: " << plate << endl;
    }

    getline(infile, fine);
  }
}

int partition(vector<pair<string, int>> &values, int left, int right) {
    int pivotIndex = left + (right - left) / 2;
    string pivotValue = values[pivotIndex].first;
    int i = left, j = right;
    pair<string, int> temp;
    while(i <= j) {
        while(values[i].first < pivotValue) {
            i++;
        }
        while(values[j].first > pivotValue) {
            j--;
        }
        if(i <= j) {
            temp = values[i];
            values[i] = values[j];
            values[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}

void quicksort(vector<pair<string, int>> &values, int left, int right) {
    if(left < right) {
        int pivotIndex = partition(values, left, right);
        quicksort(values, left, pivotIndex - 1);
        quicksort(values, pivotIndex, right);
    }
}

int main()
{
  int    N;        // = 10000;
  string basename; // = "tickets1";

  cout << "Enter hashtable size> ";
  cin >> N;

  hashtable<string, int>  ht(N);
  ILplates                hashplates(ht);

  cout << "Enter base filename> ";
  cin >> basename;
  cout << endl;

  //
  // process input file of fines and license plates:
  //
  hashInput(basename, hashplates);

  //
  // debugging:
  //
  vector<string> plates = ht.Keys();
  vector<int> amounts = ht.Values();

  cout << "Sorting..." << endl;
  pair<string, int> p;
  vector<pair<string, int>> v;
  for (size_t i = 0; i < plates.size(); ++i)
  {
    p.first = plates[i];
    p.second = amounts[i];
    v.push_back(p);
  }
  quicksort(v, 0, v.size() - 1);

  string outfilename = basename + "-output.txt";
  cout << "Writing '" << outfilename << "'..." << endl;
  ofstream outfile(outfilename);
  for (size_t i = 0; i < v.size(); ++i)
  {
    //cout << "\"" << v[i].first << "\" $" << v[i].second << endl;
    outfile << "\"" << v[i].first << "\""
            << " $" << v[i].second << endl;
  }

  //
  // done:
  //
  return 0;
}
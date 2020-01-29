/*ILplates.cpp*/

//
// Hashing functions to store (license plate, amount) pairs
// using linear probing.
//
// << Hongcheng Wu >>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <string>
#include <math.h>

#include "ILplates.h"

using namespace std;

bool ifPersonalizedValid(string plateLetter, string plateNum){

  //plateLetter all upper case
  for(char a : plateLetter){
    if(a < 65 || a > 90){
      //cout << "fail here1" << endl;
      return false;
    }
  }

  //plateNum all digits
  int plateNumInt = 0;
  for (char a : plateNum)
  {
    if(a < 48 || a > 57){
      //cout << "fail here all digit" << endl;
      return false;
    }
    plateNumInt = stoi(plateNum);
  }

  //check plate letter and digit are in range
  if(plateLetter.length() > 0 && plateLetter.length() <= 6 && plateNumInt > 0 && plateNumInt <= 9){
    //cout << "AAAAAA 1" << endl;
    return true;
  }
  else if(plateLetter.length() > 0 && plateLetter.length() <= 5 && plateNumInt > 0 && plateNumInt <= 99){
    //cout << "ZZZZZ 99" << endl;
    return true;
  }
  else{
    //cout << "fail here2" << endl;
    return false;
  }
  //cout << "fail here3" << endl;
  return false;
}

bool ifVanityValid(string plate){

  if(plate.length() <= 7 && plate.length() > 0 && plate.at(0) >= 65 && plate.at(0) <= 90){ //plate contain upper case
    for(char a : plate){
      if(a < 65 || a > 90){
        //cout << "1: invalid char: " << a << endl;
        return false;
      }
    }
    return true;
  }
  else if(plate.length() <= 3 && plate.length() > 0 && plate.at(0) >= 48 && plate.at(0) <= 57){  ///plate contain digit
    for(char a : plate){
      if(a < 48 || a > 57){
        //cout << "2: invalid char: " << a << endl;
        return false;
      }
    }
    return true;
  }
  else{
    return false;
  }
  return false;
}

bool ifPlateValid(string plate){
  //Personalized plate
  string plateLetter, plateNum;

  for (unsigned int i = 0; i < plate.length(); i++)
  {
    if (plate.at(i) == ' ') //if space contain in plate
    {
      plateLetter = plate.substr(0, i);
      plateNum = plate.substr(i + 1, plate.length());
      break;
    }
  }

  if(ifPersonalizedValid(plateLetter, plateNum) || ifVanityValid(plate)){
    return true;
  }

  return false;
}

//
// Hash:
//
// Given a specialized Illinois license plate, returns an index into
// the underyling hash table.  If the given plate does not follow the
// formatting rules given below, -1 is returned.
//
// Personalized:
//   letters and numbers, with a space between the letters 
//   and numbers.  Format: 1-5 letters plus 1..99 *OR* 
//   6 letters plus 1..9
//
//   Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
//
// Vanity:
//   Format: 1-3 numbers *OR* 1-7 letters
// 
//   Examples: 007, 1, 42, X, AAA, ZZZEFGH
//
int ILplates::Hash(string plate)
{
  int index = 0;

  //
  // TODO:
  //
  if(ifPlateValid(plate)){
    for (unsigned int i = 0; i < plate.length(); i++)
    {
      index = index + plate.at(i) % 10 * pow(10, i);
      //cout << "After " << plate.at(i) << " index: " << index << endl;
    }
  }
  else{
    return -1;
  }
  index = index % HT.Size();
  //cout << "plate: " << plate << ", index: " << index << endl;
  return index;
}

//
// Search
// 
// Hashes and searches for the given license plate; returns the 
// associated value for this plate if found, or -1 if not found.
//
int ILplates::Search(string plate)
{
  //
  // TODO:
  //
  bool empty;
  string key;
  int value;
  int index = Hash(plate);

  HT.Get(index, empty, key, value);
  while(empty != true){
    if(key == plate)
    {
        return value;
    }
    index = (index + 1) % HT.Size();
    HT.Get(index, empty, key, value);
  }
  return -1;
}


//
// Insert
//
// Inserts the given (plate, newValue) into the hash table,
// overwriting an existing value if there.
//
void ILplates::Insert(string plate, int newValue)
{
  //
  // TODO:
  //
  bool empty;
  string key;
  int value;
  //cout << plate << ",";
  int index = Hash(plate);

  HT.Get(index, empty, key, value);
  while (index < HT.Size())
  {
    if (empty == true)
    {
      HT.Set(index, plate, newValue);
      //cout << index << "@;";
      return;
    }
    else if(key.compare(plate) == 0 && empty == false){
      HT.Set(index, plate, newValue);
      //cout << index << "!;";
      return;
    }
    index = (index + 1) % HT.Size();
    HT.Get(index, empty, key, value);
  }
}
